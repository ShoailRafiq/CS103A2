#include "Complaint.hpp"
#include "Console.hpp"
#include "LostItem.hpp"
#include "Stores.hpp"
#include "TripTransaction.hpp"
#include "User.hpp"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

void displayTripsMenu() {
    DataObjectCollection* trips = Stores::getTripTransactions();
    User* activeUser = Stores::getActiveUser();
    while (true) {
        displayDivider();
        cout << "Trips Menu" << endl;
        displayDivider();
        cout << " 1) Create Trip" << endl;
        cout << " 2) Edit Trip" << endl;
        cout << " 3) View Trips" << endl;
        cout << " 4) Cancel Trip" << endl;
        cout << " 5) Go Back" << endl;

        displayDivider();
        cout << "Enter your desired menu: ";

        // Get the user menu choice
        int choice = getInputInt(1, 5);

        switch (choice) {
            case 1: {
                displayCreateTrip();
                break;
            }
            case 2: {
                displayEditTrip();
                break;
            }
            case 3: {
                displayViewTrips();
                break;
            }
            case 4: {
                displayCancelTrip();
                break;
            }
            case 5: {
                return;
            }
        }
    }
}

void displayLostItemsMenu() {
    DataObjectCollection* lostItems = Stores::getLostItems();
    User* activeUser = Stores::getActiveUser();

    while (true) {
        displayDivider();
        cout << "Lost Items Menu" << endl;
        displayDivider();
        cout << " 1) Create Lost Item" << endl;
        cout << " 2) Edit Lost Item" << endl;
        cout << " 3) View Lost Items" << endl;
        cout << " 4) Delete Lost Items" << endl;
        cout << " 5) Go Back" << endl;
        displayDivider();
        cout << "Enter your desired menu: ";

        // Get the user menu choice
        int choice = getInputInt(1, 5);

        switch (choice) {
            case 1: {
                displayCreateLostItem();
                break;
            }
            case 2: {
                displayEditLostItem();
                break;
            }
            case 3: {
                displayViewLostItems();
                break;
            }
            case 4: {
                displayDeleteLostItem();
                break;
            }
            case 5: {
                return;
            }
        }
    }
}

void displayComplaintsMenu() {
    DataObjectCollection* complaints = Stores::getComplaints();
    User* activeUser = Stores::getActiveUser();
    while (true) {
        displayDivider();
        cout << "Complaints Menu" << endl;
        displayDivider();
        cout << " 1) Create Complaint" << endl;
        cout << " 2) Edit Complaint" << endl;
        cout << " 3) View Complaints" << endl;
        cout << " 4) Delete Complaint" << endl;
        cout << " 5) Go Back" << endl;
        displayDivider();
        cout << "Enter your desired menu: ";

        // Get the user menu choice
        int choice = getInputInt(1, 5);

        switch (choice) {
            case 1: {
                displayCreateComplaint();
                break;
            }
            case 2: {
                displayEditComplaint();
                break;
            }
            case 3: {
                displayViewComplaints();
                break;
            }
            case 4: {
                displayDeleteComplaint();
                break;
            }
            case 5: {
                return;
            }
        }
    }
}

void displayUsersMenu() {
    DataObjectCollection* users = Stores::getUsers();
    User* activeUser = Stores::getActiveUser();
    while (true) {
        displayDivider();
        cout << "Users Menu" << endl;
        displayDivider();
        cout << " 1) View Users" << endl;
        cout << " 2) Edit User" << endl;
        cout << " 3) Delete User" << endl;
        cout << " 4) Go Back" << endl;
        displayDivider();
        cout << "Enter your desired menu: ";

        // Get the user menu choice
        int choice = getInputInt(1, 4);

        switch (choice) {
            case 1: {
                displayViewUsers();
                break;
            }
            case 2: {
                displayEditUser();
                break;
            }
            case 3: {
                displayDeleteUser();
                break;
            }
            case 4: {
                return;
            }
        }
    }
}

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
            displayTripsMenu();
            break;
        }
        case 2: {
            displayLostItemsMenu();
            break;
        }
        case 3: {
            displayComplaintsMenu();
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
            displayTripsMenu();
            break;
        }
        case 2: {
            displayLostItemsMenu();
            break;
        }
        case 3: {
            displayComplaintsMenu();
            break;
        }
        case 4: {
            displayUsersMenu();
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
            displayTripsMenu();
            break;
        }
        case 2: {
            displayLostItemsMenu();
            break;
        }
        case 3: {
            displayComplaintsMenu();
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
