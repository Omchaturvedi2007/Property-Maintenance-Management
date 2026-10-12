#include "Property.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Property::Property()
    : id(0), address(""), propertyType(""), ownerId(0), tenantId(0), monthlyRent(0.0) {
}

Property::Property(int id, const string& address, const string& propertyType,
                   int ownerId, double monthlyRent)
    : id(0), address(""), propertyType(""), ownerId(0), tenantId(0), monthlyRent(0.0) {
    setId(id);
    setAddress(address);
    setPropertyType(propertyType);
    setOwnerId(ownerId);
    setMonthlyRent(monthlyRent);
}

Property::~Property() {
}

int Property::getId() const { return id; }
string Property::getAddress() const { return address; }
string Property::getPropertyType() const { return propertyType; }
int Property::getOwnerId() const { return ownerId; }
int Property::getTenantId() const { return tenantId; }
double Property::getMonthlyRent() const { return monthlyRent; }

void Property::setId(int id) {
    if (id <= 0) {
        throw invalid_argument("Property ID must be a positive number.");
    }
    this->id = id;
}

void Property::setAddress(const string& address) {
    if (address.empty() || address.find('|') != string::npos) {
        throw invalid_argument("Address cannot be empty or contain the '|' character.");
    }
    this->address = address;
}

void Property::setPropertyType(const string& propertyType) {
    if (propertyType.empty() || propertyType.find('|') != string::npos) {
        throw invalid_argument("Property type cannot be empty or contain the '|' character.");
    }
    this->propertyType = propertyType;
}

void Property::setOwnerId(int ownerId) {
    if (ownerId <= 0) {
        throw invalid_argument("Owner ID must be a positive number.");
    }
    this->ownerId = ownerId;
}

void Property::setTenantId(int tenantId) {
    if (tenantId < 0) {
        throw invalid_argument("Tenant ID cannot be negative.");
    }
    this->tenantId = tenantId;
}

void Property::setMonthlyRent(double monthlyRent) {
    if (monthlyRent <= 0) {
        throw invalid_argument("Monthly rent must be greater than 0.");
    }
    this->monthlyRent = monthlyRent;
}

void Property::display() const {
    cout << "ID: " << id << " | Type: " << propertyType
         << " | Address: " << address << "\n";
    cout << "    Owner ID: " << ownerId << " | Rent: " << monthlyRent << " | ";
    if (tenantId == 0) {
        cout << "Status: Vacant\n";
    } else {
        cout << "Status: Occupied by tenant ID " << tenantId << "\n";
    }
}

string Property::toFileString() const {
    return to_string(id) + "|" + address + "|" + propertyType + "|" +
           to_string(ownerId) + "|" + to_string(tenantId) + "|" + to_string(monthlyRent);
}