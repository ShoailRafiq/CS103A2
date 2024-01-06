#include "Complaint.hpp"

Complaint::Complaint() : id(0), author(0), message("") {}

uint32_t Complaint::getId() const {
    return Complaint::id;
}

uint32_t Complaint::getAuthor() const {
    return Complaint::author;
}

string Complaint::getMessage() const {
    return Complaint::message;
}

void Complaint::setAuthor(User const& user) {
    Complaint::author = user.getId();
}

void Complaint::setMessage(string message) {
    Complaint::message = message;
}

uint32_t Complaint::getObjectId() const {
    return Complaint::id;
}

void Complaint::populateObject(DataObject* object) {
    object->setEntry("author", DataValue((int32_t)author));
    object->setEntry("message", DataValue(message));
}

void Complaint::fromObject(DataObject* object) {
    id = object->getId();
    author = (uint32_t)object->getEntry("author").asInt();
    message = object->getEntry("message").asString();
}

void displayComplaintsList() {}

void displayCreateComplaint() {}

void displayEditComplaint() {}

void displayViewComplaints() {}

void displayDeleteComplaint() {}