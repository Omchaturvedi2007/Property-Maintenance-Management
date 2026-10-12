#include "Maintenance.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Maintenance::Maintenance()
    : id(0), propertyId(0), description(""), status("Pending"), cost(0.0) {
}

Maintenance::Maintenance(int id, int propertyId, const string& description,
                         const string& status, double cost)
    : id(0), propertyId(0), description(""), status("Pending"), cost(0.0) {
    setId(id);
    setPropertyId(propertyId);
    setDescription(description);
    setStatus(status);
    setCost(cost);
}

Maintenance::~Maintenance() {
}

int Maintenance::getId() const { return id; }
int Maintenance::getPropertyId() const { return propertyId; }
string Maintenance::getDescription() const { return description; }
string Maintenance::getStatus() const { return status; }
double Maintenance::getCost() const { return cost; }

void Maintenance::setId(int id) {
    if (id <= 0) {
        throw invalid_argument("Request ID must be a positive number.");
    }
    this->id = id;
}

void Maintenance::setPropertyId(int propertyId) {
    if (propertyId <= 0) {
        throw invalid_argument("Property ID must be a positive number.");
    }
    this->propertyId = propertyId;
}

void Maintenance::setDescription(const string& description) {
    if (description.empty() || description.find('|') != string::npos) {
        throw invalid_argument("Description cannot be empty or contain the '|' character.");
    }
    this->description = description;
}

void Maintenance::setStatus(const string& status) {
    if (status != "Pending" && status != "Completed") {
        throw invalid_argument("Status must be Pending or Completed.");
    }
    this->status = status;
}

void Maintenance::setCost(double cost) {
    if (cost < 0) {
        throw invalid_argument("Cost cannot be negative.");
    }
    this->cost = cost;
}

bool Maintenance::isCompleted() const {
    return status == "Completed";
}

void Maintenance::completeRequest(double finalCost) {
    if (isCompleted()) {
        throw logic_error("This request is already completed.");
    }
    setCost(finalCost);
    status = "Completed";
}

void Maintenance::display() const {
    cout << "Request ID: " << id << " | Property ID: " << propertyId
         << " | Status: " << status << " | Cost: " << cost << "\n";
    cout << "    Problem: " << description << "\n";
}

string Maintenance::toFileString() const {
    return to_string(id) + "|" + to_string(propertyId) + "|" + description + "|" +
           status + "|" + to_string(cost);
}