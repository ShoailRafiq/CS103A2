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

void displayComplaintsList() {
    // TODO: Display list of complaints, only show complaints involving the user
    // or all complaints if admin
}

Complaint* promptSelectComplaint() {
    displayComplaintsList();

    while (true) {
        // TODO: Prompt user for the ID from the complaint list,
        // find the matching complaint, check complaint author,
        // return complaint
    }
}

void displayCreateComplaint() {
    // TODO: Prompt user for the complaint message and create with author using
    // activeUser
}

void displayEditComplaint() {
    // TODO: Display complaint list, choose complaint, prompt for new complaint
    // message, save complaint
}

void displayViewComplaints() {
    displayComplaintsList();
}

void displayDeleteComplaint() {
    // TODO: Display complaint list, choose complaint, delete complaint
}