#include "Console.hpp"
#include "Stores.hpp"
#include "User.hpp"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

User::User() : id(0), type(UserType::CUSTOMER), name(""), password("") {}

uint32_t User::getId() const {
    return User::id;
}

UserType User::getType() const {
    return User::type;
}

void User::setType(UserType type) {
    User::type = type;
}

string User::getName() const {
    return User::name;
}

void User::setName(string name) {
    User::name = name;
}

void User::setPassword(string password) {
    User::password = password;
}

bool User::isMatchingPassword(string const& password) const {
    return User::password == password;
}

uint32_t User::getObjectId() const {
    return User::id;
}

void User::populateObject(DataObject* object) {
    object->setEntry("type", DataValue((int32_t)type));
    object->setEntry("name", DataValue(name));
    object->setEntry("password", DataValue(password));
}

void User::fromObject(DataObject* object) {
    id = object->getId();
    *reinterpret_cast<int32_t*>(&type) = *object->getEntry("type")->asInt();
    name = *object->getEntry("name")->asString();
    password = *object->getEntry("password")->asString();
}

User* getAdminUser() {
    DataObjectCollection* users = Stores::getUsers();

    User* user = new User();

    // Search through all the user objects
    for (size_t i = 0; i < users->getObjectCount(); i++) {
        DataObject* userObject = users->getObject(i);
        user->fromObject(userObject);

        // Find an object with the user type of admin
        if (user->getType() == UserType::ADMIN) {
            return user;
        }
    }

    // No user found, cleanup and return null
    delete user;
    return nullptr;
}

bool isAdminUserSet() {
    User* adminUser = getAdminUser();
    bool isSet = adminUser != nullptr;
    delete adminUser;
    return isSet;
}

User* getUserByName(string const& name) {
    DataObjectCollection* users = Stores::getUsers();

    User* user = new User();

    // Search through all the user objects
    for (size_t i = 0; i < users->getObjectCount(); i++) {
        DataObject* userObject = users->getObject(i);
        user->fromObject(userObject);

        // Find an object with the user type of admin
        if (user->getName() == name) {
            return user;
        }
    }

    // No user found, cleanup and return null
    delete user;
    return nullptr;
}

void displayLoginMenu() {
    while (true) {
        displayDivider();
        cout << "Login Menu" << endl;
        displayDivider();

        cout << "Please enter name: ";
        string name = getInputString();

        User* user = getUserByName(name);

        if (user == nullptr) {
            cerr << "No user with that username found, please try again"
                 << endl;
            continue;
        }

        cout << "Please enter password: ";
        string password = getInputString();

        if (!user->isMatchingPassword(password)) {
            // Delete failed user
            delete user;

            cerr << "Provided password doesn not match, please try again"
                 << endl;

            continue;
        }

        displayDivider();

        cout << "Login successful" << endl;
        Stores::setActiveUser(user);
        break;
    }
}

void displayInitAdminMenu() {
    while (true) {
        displayDivider();
        cout << "Create Admin Account" << endl;
        displayDivider();

        cout << "Please enter the credentials for the new admin account. This\n"
                "is a one-time process that happenes when the application is\n"
                "first started"
             << endl;

        displayDivider();

        string name;
        while (true) {
            cout << "Please enter name: ";
            name = getInputString();

            // Ensure name is not empty
            if (name.length() == 0) {
                cerr << "Name cannot be empty, please try again" << endl;
                continue;
            }

            // Prevent duplicate names
            User* existing = getUserByName(name);
            if (existing != nullptr) {
                delete existing;
                cerr << "That name is already in use. please choose another"
                     << endl;
                continue;
            }

            break;
        }

        string password;
        while (true) {
            cout << "Please enter password: ";
            password = getInputString();

            if (password.length() == 0) {
                cerr << "Password cannot be empty, please try again" << endl;
                continue;
            }

            break;
        }

        string confirmPassword;

        while (true) {
            cout << "Please confirm password: ";
            confirmPassword = getInputString();

            if (password != confirmPassword) {
                cerr << "Password confirmation does not match password, please "
                        "try again"
                     << endl;
                continue;
            }

            break;
        }

        cout << "Admin account creation complete, you are now logged in as "
                "admin"
             << endl;

        User* user = new User();
        user->setName(name);
        user->setPassword(password);
        user->setType(UserType::ADMIN);

        // Store the created user
        DataObjectCollection* users = Stores::getUsers();
        DataObject* userObject = users->storeStruct(user);

        // Update the user data
        user->fromObject(userObject);

        // Set the new admin user
        Stores::setActiveUser(user);

        break;
    }
}

void displayRegisterMenu() {
    while (true) {
        displayDivider();
        cout << "Create Account" << endl;
        displayDivider();

        cout << "Please enter the credentials for your new account" << endl;

        displayDivider();
        cout << "Account type" << endl;
        displayDivider();
        cout << "1) Customer" << endl;
        cout << "2) Driver" << endl;
        displayDivider();
        cout << "Please enter your desired account type: ";
        // Get the user menu choice
        int userType = getInputInt(1, 2);

        UserType type = UserType::CUSTOMER;
        switch (userType) {
            case 1: {
                type = UserType::CUSTOMER;
                break;
            }
            case 2: {
                type = UserType::DRIVER;
                break;
            }
        }

        string name;
        while (true) {
            cout << "Please enter name: ";
            name = getInputString();

            // Ensure name is not empty
            if (name.length() == 0) {
                cerr << "Name cannot be empty, please try again" << endl;
                continue;
            }

            // Prevent duplicate names
            User* existing = getUserByName(name);
            if (existing != nullptr) {
                delete existing;
                cerr << "That name is already in use. please choose another"
                     << endl;
                continue;
            }

            break;
        }

        string password;
        while (true) {
            cout << "Please enter password: ";
            password = getInputString();

            if (password.length() == 0) {
                cerr << "Password cannot be empty, please try again" << endl;
                continue;
            }

            break;
        }

        string confirmPassword;

        while (true) {
            cout << "Please confirm password: ";
            confirmPassword = getInputString();

            if (password != confirmPassword) {
                cerr << "Password confirmation does not match password, please "
                        "try again"
                     << endl;
                continue;
            }

            break;
        }

        cout << "Account creation complete, you are now logged in." << endl;

        User* user = new User();
        user->setName(name);
        user->setPassword(password);
        user->setType(type);

        // Store the created user
        DataObjectCollection* users = Stores::getUsers();
        DataObject* userObject = users->storeStruct(user);

        // Update the user data
        user->fromObject(userObject);

        // Set the new admin user
        Stores::setActiveUser(user);

        break;
    }
}

void displayAuthMenu() {
    displayDivider();
    cout << "Authentication Menu" << endl;
    displayDivider();
    cout << " 1) Login" << endl;
    cout << " 2) Register" << endl;
    cout << " 3) Exit" << endl;
    displayDivider();
    cout << "Enter your desired menu: ";

    // Get the user menu choice
    int choice = getInputInt(1, 3);

    switch (choice) {
        case 1: {
            displayLoginMenu();
            break;
        }
        case 2: {
            displayRegisterMenu();
            break;
        }
        case 3: {
            exit(0);
            break;
        }
    }
}