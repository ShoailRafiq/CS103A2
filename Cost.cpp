#include "Cost.hpp"
#include <iostream>

Cost::Cost(int32_t dollars, int32_t cents) : dollars(dollars), cents(cents) {}
Cost::Cost(int32_t cents) {
    Cost::dollars = (cents / 100);
    Cost::cents = (cents % 100);
}

Cost::Cost() : dollars(0), cents(0) {}

int32_t Cost::getDollars() const {
    return Cost::dollars;
}

int32_t Cost::getCents() const {
    return Cost::cents;
}

void Cost::setDollars(int32_t dollars) {
    Cost::dollars = dollars;
}

void Cost::setCents(int32_t cents) {
    Cost::cents = cents;
}

int32_t Cost::getTotalCents() const {
    return Cost::cents + (Cost::dollars * 100);
}

void Cost::display() const {
    printf_s("$%i.%.2i", Cost::dollars, Cost::cents);
}
