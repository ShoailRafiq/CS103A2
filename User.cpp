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

bool User::isMatchingPassword(string password) const {
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
            cerr << "No user with that username found, do you want to try "
                    "again? [Y/N]: ";

            bool tryAgain = getInputBool();
            if (tryAgain) {
                continue;
            } else {
                break;
            }
        }

        cout << "Please enter password: ";
        string password = getInputString();

        if (!user->isMatchingPassword(password)) {
            // Delete failed user
            delete user;

            cerr << "Provided password doesn not match, do you want to try "
                    "again?, [Y/N]: ";

            bool tryAgain = getInputBool();
            if (tryAgain) {
                continue;
            } else {
                break;
            }
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

            if (name.length() == 0) {
                cerr << "Name cannot be empty, please try again" << endl;
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
        cout << "Login Menu" << endl;
        displayDivider();
    }
}

void displayAuthMenu() {}