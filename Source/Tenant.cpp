#include "Tenant.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Tenant::Tenant() : Person(), propertyId(0) {
}

Tenant::Tenant(int id, const string& name, const string& phone, int propertyId)
    : Person(id, name, phone), propertyId(0) {
    setPropertyId(propertyId);
}

Tenant::~Tenant() {
}

int Tenant::getPropertyId() const { return propertyId; }

void Tenant::setPropertyId(int propertyId) {
    if (propertyId < 0) {
        throw invalid_argument("Property ID cannot be negative.");
    }
    this->propertyId = propertyId;
}

void Tenant::display() const {
    Person::display();
    if (propertyId == 0) {
        cout << "    Renting: no property\n";
    } else {
        cout << "    Renting property ID: " << propertyId << "\n";
    }
}

string Tenant::getType() const {
    return "Tenant";
}

string Tenant::toFileString() const {
    return "T|" + to_string(id) + "|" + name + "|" + phone + "|" + to_string(propertyId);
}