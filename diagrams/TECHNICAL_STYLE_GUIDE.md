# Technical style guide

Below is the technical style guide for this project

## Source and header files

All c++ code should be divided and grouped into separate .cpp files based on its function, every .cpp file should have an associated .hpp file with the same name (Excluding the entry point file).

The entry point file that contains the main function should not define any structures or additional functions, it should only define the main function and include libraries 

The .hpp file should contain the type and structure definitions for classes, functions, macros, etc. The header file should not contain any implementation logic, all implementation logic should only be included in the .cpp file.

Header files should use a #ifndef and #define macro in order to prevent accidental duplicated loading of the same header

## Code standard:

The C++ 14 code standard is used as it is the default Visual Studio implementation for VS2022

## Imports

Any included modules or functions must #include the required file directly unless they already include a header file that includes the desired header. Using “using namespace std” is forbidden, instead required modules can use the using syntax to include the specific item (using string) or can access the item through its namespace (std::string), this is only required when the item is within a namespace

## Formatting

Source and header files are formatted using the Chromium formatting style with 4 character space indentation, this is enforced by the .clang-format configuration file.

## Naming

Class, structure and enum naming should be done in PascalCase. (e.g. MyClass, ExampleEnum, TestClassName).

All functions and variables should  be named in camelCase (e.g. myExampleFunction, getId, setName)

Constants, statics and macros should be named in SCREAMING_SNAKE_CASE (e.g. MY_CONSTANTS, EXAMPLE_VALUE, TEST_MACRO)

## Data structures


All structures should have their definitions placed in .hpp files and any implementation logic placed in .cpp files. 

The members of structures and classes should all be private by default, if any external code is required to access the data structure members it should do so through  relevant getters and setters.

## File management:

All persisted files should be stored using “Data Collections”; these are binary files named with a .db extension.

The following table shows what files store what information:

| File                 | Description                                                                                  |
| -------------------- | -------------------------------------------------------------------------------------------- |
| users.db             | Stores user data for admins, customers, and drivers this includes usernames, passwords.. etc |
| trip_transactions.db | Stores trip transaction history                                                              |
| lost_items.db        | Stores lost item data                                                                        |
| complaints.db        | Stores complaint messages                                                                    |


### Data Collection

Represents a collection of objects

| Field                           | Type                        | Length                      |
| ------------------------------- | --------------------------- | --------------------------- |
| Next ID                         | uint32_t                    | 4 bytes                     |
| Total Objects                   | uint32_t                    | 4 bytes                     |
| ...Data Object (x Total Object) | [Data Object](#data-object) | Data Object x Total Objects |

- The `Next ID` field denotes the next ID that should be given to the next created Data Object
- The `Total Objects` field denotes the number of data objects contained in the collection

### Data Object

Represents an individual data object

| Field                       | Type                     | Length                     |
| --------------------------- | ------------------------ | -------------------------- |
| Object ID                   | uint32_t                 | 4 bytes                    |
| Total Entries               | uint32_t                 | 4 bytes                    |
| ..Entries (x Total Entries) | [DataEntry](#data-entry) | Data Entry x Total Entries |

- The `Object ID` field denotes the unique ID for the given data object
- The `Total Entries` field denotes the number of data entries that follows this object


### Data Entry

Represents a named entry within a data obejct, entry names are unique and any duplicate names will 
be replaced by new names. 

> The file format should not include any duplicates but if any are present they
> will replace the existing value.

Data entries are represented by by a string key and then a [Data Value](#data-value-encoding)

| Field | Type      | Reference                                   |
| ----- | --------- | ------------------------------------------- |
| Key   | string    | [Strings encoding](#strings-encoding)       |
| Value | DataValue | [Data value encoding](#data-value-encoding) |

### Strings encoding

Strings are represented by an integer value for the length of the string
characters, then the character bytes layed out following it.

| Field         | C++ Type | Length           |
| ------------- | -------- | ---------------- |
| String Length | uint32_t | 4 bytes          |
| String Bytes  | char[]   | { String Length} |

### Data value encoding

Below is the encoding for data values:

| Field | Type                                           | Encoding                                    |
| ----- | ---------------------------------------------- | ------------------------------------------- |
| Type  | uint8_t ([Value types](#value-types))          | [Strings encoding](#strings-encoding)       |
| Value | string, int32_t, float ([Variants](#variants)) | [Data value encoding](#data-value-encoding) |

#### Value types

Below are the different types of values (Enum), this enum is represented
by a Value which is a uint8_t

| Name    | C++ Type | Value |
| ------- | -------- | ----- |
| STRING  | string   | 0x0   |
| INTEGER | int32_t  | 0x1   |
| FLOAT   | float    | 0x2   |

#### Variants

| Name    | C++ type | Encoding                               |
| ------- | -------- | -------------------------------------- |
| STRING  | string   | [Strings encoding](#strings-encoding)  |
| INTEGER | int32_t  | 4 bytes (Platform default byte values) |
| FLOAT   | float    | 4 bytes (Platform default byte values) |

