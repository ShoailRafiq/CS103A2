#include "Console.hpp"
#include "Stores.hpp"
#include "User.hpp"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

void displayCustomerMenu() {
    // Display the menu
    displayDivider();
    cout << "Customer Main Menu" << endl;
    displayDivider();
    cout << " 1) Trips" << endl;
    cout << " 2) Lost Items" << endl;
    cout << " 3) Complaints" << endl;
    cout << " 4) Logout" << endl;
    displayDivider();
    cout << "Enter your desired menu: ";

    // Get the user menu choice
    int choice = getInputInt(1, 4);

    switch (choice) {
        case 1: {
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;
        }
        case 4: {
            // Clear the active user
            Stores::setActiveUser(nullptr);
            break;
        }
    }
}

void displayAdminMenu() {
    // Display the menu
    displayDivider();
    cout << "Admin Main Menu" << endl;
    displayDivider();
    cout << " 1) Trips" << endl;
    cout << " 2) Lost Items" << endl;
    cout << " 3) Complaints" << endl;
    cout << " 4) Users" << endl;
    cout << " 5) Logout" << endl;
    displayDivider();
    cout << "Enter your desired menu: ";

    // Get the user menu choice
    int choice = getInputInt(1, 5);

    switch (choice) {
        case 1: {
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;
        }
        case 4: {
            break;
        }
        case 5: {
            // Clear the active user
            Stores::setActiveUser(nullptr);
            break;
        }
    }
}

void displayDriverMenu() {
    displayDivider();
    std::cout << "Driver Main Menu" << std::endl;
    displayDivider();
    cout << " 1) Trips" << endl;
    cout << " 2) Lost Items" << endl;
    cout << " 3) Complaints" << endl;
    cout << " 4) Logout" << endl;
    displayDivider();
    cout << "Enter your desired menu: ";

    // Get the user menu choice
    int choice = getInputInt(1, 4);

    switch (choice) {
        case 1: {
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;
        }
        case 4: {
            // Clear the active user
            Stores::setActiveUser(nullptr);
            break;
        }
    }
}

void displayMainMenu() {
    while (true) {
        // Handle setting up admin user for the first time
        if (!isAdminUserSet()) {
            displayInitAdminMenu();
            continue;
        }

        // Obtain the active authenticated user
        User* activeUser = Stores::getActiveUser();

        // Handle login menu when no active user
        if (activeUser == nullptr) {
            displayAuthMenu();
            continue;
        }

        switch (activeUser->getType()) {
            case UserType::ADMIN: {
                displayAdminMenu();
                break;
            }
            case UserType::CUSTOMER: {
                displayCustomerMenu();
                break;
            }
            case UserType::DRIVER: {
                displayDriverMenu();
                break;
            }
        }
    }
}
