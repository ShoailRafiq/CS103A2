#ifndef USER
#define USER 1

#include "DataObject.hpp"
#include <stdint.h>

using std::int32_t;

/// <summary>
/// Enumeration of the various user types
/// </summary>
enum UserType : int32_t {
    /// <summary>
    /// Customer general user
    /// </summary>
    CUSTOMER = 0x0,
    /// <summary>
    /// Taxi driver user
    /// </summary>
    DRIVER = 0x1,
    /// <summary>
    /// Admin user
    /// </summary>
    ADMIN = 0x2,
};

/// <summary>
/// Represents a user of the application
/// </summary>
class User : public DataObjectStructure {
   private:
    /// <summary>
    /// Unique ID of the user object
    /// </summary>
    uint32_t id;
    /// <summary>
    /// The type of user
    /// </summary>
    UserType type;
    /// <summary>
    /// The name of the user
    /// </summary>
    string name;
    /// <summary>
    /// The password of the user
    /// </summary>
    string password;

   public:
    User();

    uint32_t getId() const;

    UserType getType() const;

    void setType(UserType type);

    string getName() const;

    void setName(string name);

    void setPassword(string password);

    /// <summary>
    /// Checks if the password for this user matches the provided password
    /// </summary>
    /// <param name="password">The password to compare against</param>
    /// <returns>Whether the passwords match</returns>
    bool isMatchingPassword(string const& password) const;

    void populateObject(DataObject* object) override;
    void fromObject(DataObject* object) override;
    uint32_t getObjectId() const override;
};

/// <summary>
/// Finds the admin user from the users data collection if one exists,
/// if none exists a nullptr is returned instead
/// </summary>
/// <returns>The admin user or a nullptr</returns>
User* getAdminUser();

/// <summary>
/// Checks if an admin user has been created
/// </summary>
/// <returns>Whether the admin user has been created</returns>
bool isAdminUserSet();

/// <summary>
/// Finds a user with a name that matches the provided name
/// </summary>
/// <param name="name">The name to search for</param>
/// <returns>The pointer to the found user or null</returns>
User* getUserByName(string const& name);

/// <summary>
/// Finds and collections all the customer type users
/// </summary>
/// <returns></returns>
vector<User*> getCustomers();

/// <summary>
/// Display a menu showing the login and registration options
/// </summary>
void displayAuthMenu();

/// <summary>
/// Displays the login menu
/// </summary>
void displayLoginMenu();

/// <summary>
/// Displays the registration menu
/// </summary>
void displayRegisterMenu();

/// <summary>
/// Displays the admin initialization menu
/// </summary>
void displayInitAdminMenu();

/// <summary>
/// Displays a list of all users
/// </summary>
void displayUsersList();

/// <summary>
/// Prompts the user to select a user from a list of
/// users
/// </summary>
/// <returns>The selected user or nullptr if no user was
/// selected</returns>
User* promptSelectUser();

/// <summary>
/// Displays a edit user menu
/// </summary>
void displayEditUser();

/// <summary>
/// Displays a view users menu
/// </summary>
void displayViewUsers();

/// <summary>
/// Displays a delete user menu
/// </summary>
void displayDeleteUser();

#endif