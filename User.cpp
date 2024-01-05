#include "User.hpp"

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