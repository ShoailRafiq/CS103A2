#include "LostItem.hpp"

LostItem::LostItem() : id(0), trip(0), reporter(0), description("") {}

uint32_t LostItem::getId() const {
    return LostItem::id;
}

uint32_t LostItem::getTrip() const {
    return LostItem::trip;
}

uint32_t LostItem::getReporter() const {
    return LostItem::reporter;
}

string LostItem::getDescription() const {
    return LostItem::description;
}

void LostItem::setTrip(TripTransaction const& trip) {
    LostItem::trip = trip.getId();
}

void LostItem::setReporter(User const& user) {
    LostItem::reporter = user.getId();
}

void LostItem::setDescription(string description) {
    LostItem::description = description;
}

uint32_t LostItem::getObjectId() const {
    return LostItem::id;
}

void LostItem::populateObject(DataObject* object) {
    object->setEntry("trip", DataValue((int32_t)trip));
    object->setEntry("reporter", DataValue((int32_t)reporter));
    object->setEntry("description", DataValue(description));
}

void LostItem::fromObject(DataObject* object) {
    id = object->getId();
    trip = (uint32_t)object->getEntry("trip").asInt();
    reporter = (uint32_t)object->getEntry("reporter").asInt();
    description = object->getEntry("description").asString();
}

void displayLostItemsList() {}

LostItem* promptSelectLostItem() {}

void displayCreateLostItem() {}

void displayEditLostItem() {}

void displayViewLostItems() {}

void displayDeleteLostItem() {}