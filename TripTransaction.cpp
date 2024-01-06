#include "Console.hpp"
#include "Cost.hpp"
#include "Stores.hpp"
#include "TripTransaction.hpp"
#include <iostream>
#include <string>

using std::cerr;
using std::cout;
using std::endl;

TripTransaction::TripTransaction()
    : id(0),
      driver(0),
      customer(0),
      cost(Cost()),
      startLocation(""),
      endLocation("") {}

uint32_t TripTransaction::getId() const {
    return TripTransaction::id;
}

uint32_t TripTransaction::getDriver() const {
    return TripTransaction::driver;
}

uint32_t TripTransaction::getCustomer() const {
    return TripTransaction::customer;
}

void TripTransaction::setDriver(User* user) {
    TripTransaction::driver = user->getId();
}

void TripTransaction::setCustomer(User* user) {
    TripTransaction::customer = user->getId();
}

Cost TripTransaction::getCost() const {
    return TripTransaction::cost;
}

void TripTransaction::setCost(Cost cost) {
    TripTransaction::cost = cost;
}

uint32_t TripTransaction::getObjectId() const {
    return TripTransaction::id;
}

string TripTransaction::getStartLocation() const {
    return TripTransaction::startLocation;
}

void TripTransaction::setStartLocation(string startLocation) {
    TripTransaction::startLocation = startLocation;
}

string TripTransaction::getEndLocation() const {
    return TripTransaction::endLocation;
}

void TripTransaction::setEndLocation(string endLocation) {
    TripTransaction::endLocation = endLocation;
}

void TripTransaction::populateObject(DataObject* object) {
    object->setEntry("driver", DataValue((int32_t)driver));
    object->setEntry("customer", DataValue((int32_t)customer));
    object->setEntry("cost", DataValue((int32_t)cost.getTotalCents()));
    object->setEntry("startLocation", DataValue(startLocation));
    object->setEntry("endLocation", DataValue(endLocation));
}

void TripTransaction::fromObject(DataObject* object) {
    id = object->getId();
    driver = (uint32_t)object->getEntry("driver").asInt();
    customer = (uint32_t)object->getEntry("customer").asInt();
    cost = Cost(object->getEntry("cost").asInt());
    startLocation = object->getEntry("startLocation").asString();
    endLocation = object->getEntry("endLocation").asString();
}

User* promptSelectCustomer(vector<User*> const& customers) {
    DataObjectCollection* users = Stores::getUsers();
    cout << "Customer List" << endl;
    displayDivider();

    for (size_t i = 0; i < customers.size(); i++) {
        User* customer = customers[i];
        cout << (i + 1) << ") " << customer->getName() << endl;
    }

    cout << "Please enter the number for the customer you are driving: ";
    int choice = getInputInt(1, customers.size() + 1);

    User* customer = customers[choice - 1];

    return customer;
}

TripTransaction* promptSelectTrip() {
    DataObjectCollection* trips = Stores::getTripTransactions();
    User* activeUser = Stores::getActiveUser();

    displayTripsList();

    while (true) {
        cout << "Enter the ID of the trip (Enter -1 to go back): ";
        int32_t tripId = getInputInt(-1, INT32_MAX);

        if (tripId == -1) {
            return nullptr;
        }

        // Load the trip object
        DataObject* tripObject = trips->getObjectById(tripId);

        if (tripObject == nullptr) {
            cerr << "Unknown trip ID entered, please try again" << endl;
            continue;
        }

        // Create temporary object to load the values into
        TripTransaction* trip = new TripTransaction();
        trip->fromObject(tripObject);

        // Ensure the user is apart of the trip or are an admin
        if (trip->getCustomer() != activeUser->getId() &&
            trip->getDriver() != activeUser->getId() &&
            activeUser->getType() != UserType::ADMIN) {
            delete trip;
            cerr << "Unknown trip entered, please try again" << endl;
            continue;
        }

        return trip;
    }
}

void displayTripsList() {
    DataObjectCollection* users = Stores::getUsers();
    DataObjectCollection* trips = Stores::getTripTransactions();
    User* activeUser = Stores::getActiveUser();

    // Create temporary objects to load the values into
    TripTransaction* trip = new TripTransaction();
    User* driver = new User();
    User* customer = new User();

    // Display the list header
    displayDivider();
    cout << "ID, Driver, Customer, Cost, Start Loc, End Loc" << endl;
    displayDivider();

    int32_t totalCostCents = 0;

    for (size_t i = 0; i < trips->getObjectCount(); i++) {
        // Load the trip object
        DataObject* tripObject = trips->getObject(i);
        trip->fromObject(tripObject);

        // Load the associated driver user
        DataObject* driverObject = users->getObjectById(trip->getDriver());
        driver->fromObject(driverObject);

        // Load the associated customer user
        DataObject* customerObject = users->getObjectById(trip->getCustomer());
        customer->fromObject(customerObject);

        // Ensure the user is apart of the trip or are an admin before including
        // in list
        if (trip->getCustomer() != activeUser->getId() &&
            trip->getDriver() != activeUser->getId() &&
            activeUser->getType() != UserType::ADMIN) {
            continue;
        }

        Cost cost = trip->getCost();

        // Display the trip, driver, and customer details
        cout << trip->getId() << ", " << driver->getName() << ", "
             << customer->getName() << ", ";
        cost.display();
        cout << ", " << trip->getStartLocation() << ", "
             << trip->getEndLocation() << endl;

        // Add to the total cost
        totalCostCents += cost.getTotalCents();
    }

    // Free the temp objects
    delete trip;
    delete driver;
    delete customer;

    // Create and dislpay the total cost
    Cost totalCost = Cost(totalCostCents);
    displayDivider();
    cout << "Total Cost: ";
    totalCost.display();
    cout << endl;
}

void displayCreateTrip() {
    DataObjectCollection* trips = Stores::getTripTransactions();
    User* activeUser = Stores::getActiveUser();

    displayDivider();
    cout << "Trip Creator" << endl;
    displayDivider();

    vector<User*> customers = getCustomers();
    if (customers.empty()) {
        cerr << "There are no customers registered in the system, a trip\n"
                " cannot be created without one, please ensure your\n"
                " customer creates an account first";

        return;
    }

    User* customer = promptSelectCustomer(customers);

    Cost cost;

    while (true) {
        // Prompt the user for the cost
        cout << "Please enter trip dollar cost: ";
        int32_t dollarCost = getInputInt(0, INT32_MAX);
        cout << "Please enter trip cents cost: ";
        int32_t centsCost = getInputInt(0, 99);

        cost = Cost(dollarCost, centsCost);

        // Ensure the cost is not zero
        if (cost.getTotalCents() == 0) {
            cerr << "Cost cannot be zero, please try again" << endl;
            continue;
        }

        break;
    }

    cout << "Enter starting location: ";
    string startLocation = getInputString();

    cout << "Enter end location: ";
    string endLocation = getInputString();

    // Create the trip
    TripTransaction* trip = new TripTransaction();
    trip->setDriver(activeUser);
    trip->setCustomer(customer);
    trip->setCost(cost);
    trip->setStartLocation(startLocation);
    trip->setEndLocation(endLocation);

    // Store the created trip
    DataObject* tripObject = trips->storeStruct(trip);

    // Update the trip
    trip->fromObject(tripObject);

    // Show the created trip information
    displayDivider();
    cout << "New trip created" << endl;
    displayDivider();

    cout << "Driver: " << activeUser->getName() << endl;
    cout << "Customer: " << customer->getName() << endl;
    cout << "Cost: ";
    cost.display();
    cout << endl;
    cout << "Start Location: " << trip->getStartLocation() << endl;
    cout << "End Location: " << trip->getEndLocation() << endl;
    displayDivider();

    // Free customers collection
    for (User* customer : customers)
        delete customer;
    customers.clear();
}

void displayEditTrip() {
    DataObjectCollection* trips = Stores::getTripTransactions();

    // Display the title
    displayDivider();
    cout << "Edit Trip" << endl;

    // Ensure there is actually trips available
    if (trips->getObjectCount() == 0) {
        cerr << "You have no trips to edit" << endl;
        return;
    }

    // Prompt the user to pick the trip to edit
    TripTransaction* trip = promptSelectTrip();

    // Handle user cancelling picking a trip
    if (trip == nullptr) {
        return;
    }

    while (true) {
        // Display editing sub menu
        displayDivider();
        cout << "Editing Trip (" << trip->getId() << ")" << endl;
        displayDivider();
        cout << " 1) Change Customer" << endl;
        cout << " 2) Change Cost" << endl;
        cout << " 3) Change Start Location" << endl;
        cout << " 4) Change End Location" << endl;
        cout << " 5) Go Back" << endl;

        // Get the user menu choice
        int choice = getInputInt(1, 5);

        switch (choice) {
            // Change customer
            case 1: {
                vector<User*> customers = getCustomers();
                if (customers.empty()) {
                    cerr << "There are no customers registered in the system, "
                            "a trip\n"
                            " cannot be created without one, please ensure "
                            "your\n"
                            " customer creates an account first";

                    return;
                }

                // Pick the new customer
                User* customer = promptSelectCustomer(customers);
                trip->setCustomer(customer);

                // Save the changes
                trips->saveStruct(trip);

                cout << "Trip customer updated and saved." << endl;

                // Free customers collection
                for (User* customer : customers)
                    delete customer;
                customers.clear();

                break;
            }
            // Change cost
            case 2: {
                Cost cost;

                while (true) {
                    // Prompt the user for the cost
                    cout << "Please enter trip dollar cost: ";
                    int32_t dollarCost = getInputInt(0, INT32_MAX);
                    cout << "Please enter trip cents cost: ";
                    int32_t centsCost = getInputInt(0, 99);

                    cost = Cost(dollarCost, centsCost);

                    // Ensure the cost is not zero
                    if (cost.getTotalCents() == 0) {
                        cerr << "Cost cannot be zero, please try again" << endl;
                        continue;
                    }

                    break;
                }

                // Update the cost
                trip->setCost(cost);

                // Save the changes
                trips->saveStruct(trip);

                cout << "Trip cost updated and saved." << endl;

                break;
            }
            // Change start location
            case 3: {
                cout << "Enter new starting location: ";
                string startLocation = getInputString();

                // Update the start location
                trip->setStartLocation(startLocation);

                // Save the changes
                trips->saveStruct(trip);

                cout << "Trip start location updated and saved." << endl;

                break;
            }
            // Change end location
            case 4: {
                cout << "Enter new end location: ";
                string endLocation = getInputString();

                // Update the end location
                trip->setEndLocation(endLocation);

                // Save the changes
                trips->saveStruct(trip);

                cout << "Trip end location updated and saved." << endl;

                break;
            }
            // Go back a menu
            case 5: {
                delete trip;
                return;
            }
        }
    }
}

void displayViewTrips() {
    displayDivider();
    cout << "Trip List" << endl;

    displayTripsList();
}

void displayCancelTrip() {
    DataObjectCollection* trips = Stores::getTripTransactions();

    // Display the title
    displayDivider();
    cout << "Cancel Trip" << endl;

    // Ensure there is actually trips available
    if (trips->getObjectCount() == 0) {
        cerr << "You have no trips to cancel" << endl;
        return;
    }

    // Prompt the user to pick the trip to cancel
    TripTransaction* trip = promptSelectTrip();

    // Handle user cancelling picking a trip
    if (trip == nullptr) {
        return;
    }

    // Cancel the trip
    trips->deleteObject(trip->getObjectId());

    // Delete the trip object
    delete trip;
}