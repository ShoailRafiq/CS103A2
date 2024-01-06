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

void displayTripsList() {
    DataObjectCollection* users = Stores::getUsers();
    DataObjectCollection* trips = Stores::getTripTransactions();

    TripTransaction* trip = new TripTransaction();
    User* driver = new User();
    User* customer = new User();

    cout << "Trip List" << endl;
    displayDivider();
    cout << "ID, Driver, Customer, Cost, Start Loc, End Loc" << endl;
    displayDivider();

    int32_t totalCostCents = 0;

    for (size_t i = 0; i < trips->getObjectCount(); i++) {
        DataObject* tripObject = trips->getObject(i);
        trip->fromObject(tripObject);

        DataObject* driverObject = users->getObjectById(trip->getDriver());
        driver->fromObject(driverObject);

        DataObject* customerObject = users->getObjectById(trip->getCustomer());
        customer->fromObject(customerObject);

        Cost cost = trip->getCost();

        cout << trip->getId() << ", " << driver->getName() << ", "
             << customer->getName() << ", ";
        cost.display();

        cout << ", " << trip->getStartLocation() << ", "
             << trip->getEndLocation() << endl;

        totalCostCents += cost.getTotalCents();
    }

    delete trip;
    delete driver;
    delete customer;

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
}

void displayEditTrip() {}

void displayViewTrips() {
    displayTripsList();
}

void displayCancelTrip() {}