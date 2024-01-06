#include "TripTransaction.hpp"

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

void TripTransaction::setDriver(User const& user) {
    TripTransaction::driver = user.getId();
}

void TripTransaction::setCustomer(User const& user) {
    TripTransaction::customer = user.getId();
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
    driver = (uint32_t)*object->getEntry("driver")->asInt();
    customer = (uint32_t)*object->getEntry("customer")->asInt();
    cost = Cost(*object->getEntry("cost")->asInt());
    startLocation = *object->getEntry("startLocation")->asString();
    endLocation = *object->getEntry("endLocation")->asString();
}

void displayTripsList() {}

void displayCreateTrip() {}

void displayEditTrip() {}

void displayViewTrips() {}

void displayCancelTrip() {}