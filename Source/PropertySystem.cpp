#include "PropertySystem.h"
#include "Owner.h"
#include "Tenant.h"
#include "Input.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

const int START_CAPACITY = 5;

// =====================================================
//  Constructor / Destructor
// =====================================================
PropertySystem::PropertySystem() {
    peopleCapacity = START_CAPACITY;
    peopleCount = 0;
    people = new Person*[peopleCapacity];

    propertyCapacity = START_CAPACITY;
    propertyCount = 0;
    properties = new Property[propertyCapacity];

    requestCapacity = START_CAPACITY;
    requestCount = 0;
    requests = new Maintenance[requestCapacity];
}

PropertySystem::~PropertySystem() {
    clearAll();            // deletes each Owner/Tenant object
    delete[] people;       // free the dynamic arrays
    delete[] properties;
    delete[] requests;
}

// =====================================================
//  Memory helpers
// =====================================================
void PropertySystem::growPeople() {
    int newCapacity = peopleCapacity * 2;
    Person** bigger = new Person*[newCapacity];
    for (int i = 0; i < peopleCount; i++) {
        bigger[i] = people[i];
    }
    delete[] people;
    people = bigger;
    peopleCapacity = newCapacity;
}

void PropertySystem::growProperties() {
    int newCapacity = propertyCapacity * 2;
    Property* bigger = new Property[newCapacity];
    for (int i = 0; i < propertyCount; i++) {
        bigger[i] = properties[i];
    }
    delete[] properties;
    properties = bigger;
    propertyCapacity = newCapacity;
}

void PropertySystem::growRequests() {
    int newCapacity = requestCapacity * 2;
    Maintenance* bigger = new Maintenance[newCapacity];
    for (int i = 0; i < requestCount; i++) {
        bigger[i] = requests[i];
    }
    delete[] requests;
    requests = bigger;
    requestCapacity = newCapacity;
}

void PropertySystem::clearAll() {
    for (int i = 0; i < peopleCount; i++) {
        delete people[i];
    }
    peopleCount = 0;
    propertyCount = 0;
    requestCount = 0;
}

// =====================================================
//  Find helpers (return index, or -1 if not found)
// =====================================================
int PropertySystem::findPersonIndex(int id) const {
    for (int i = 0; i < peopleCount; i++) {
        if (people[i]->getId() == id) return i;
    }
    return -1;
}

int PropertySystem::findPersonIndexOfType(int id, const string& type) const {
    int index = findPersonIndex(id);
    if (index != -1 && people[index]->getType() == type) return index;
    return -1;
}

int PropertySystem::findPropertyIndex(int id) const {
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].getId() == id) return i;
    }
    return -1;
}

int PropertySystem::findRequestIndex(int id) const {
    for (int i = 0; i < requestCount; i++) {
        if (requests[i].getId() == id) return i;
    }
    return -1;
}

// =====================================================
//  Remove helpers
// =====================================================
void PropertySystem::removePersonAt(int index) {
    delete people[index];
    for (int i = index; i < peopleCount - 1; i++) {
        people[i] = people[i + 1];
    }
    peopleCount--;
}

void PropertySystem::removePropertyAt(int index) {
    for (int i = index; i < propertyCount - 1; i++) {
        properties[i] = properties[i + 1];
    }
    propertyCount--;
}

void PropertySystem::removeRequestAt(int index) {
    for (int i = index; i < requestCount - 1; i++) {
        requests[i] = requests[i + 1];
    }
    requestCount--;
}

// =====================================================
//  Functions used by FileManager
// =====================================================
void PropertySystem::storePerson(Person* person) {
    if (peopleCount == peopleCapacity) growPeople();
    people[peopleCount++] = person;
}

void PropertySystem::storeProperty(const Property& property) {
    if (propertyCount == propertyCapacity) growProperties();
    properties[propertyCount++] = property;
}

void PropertySystem::storeRequest(const Maintenance& request) {
    if (requestCount == requestCapacity) growRequests();
    requests[requestCount++] = request;
}

int PropertySystem::getPersonCount() const { return peopleCount; }
const Person* PropertySystem::getPerson(int index) const { return people[index]; }
int PropertySystem::getPropertyCount() const { return propertyCount; }
const Property& PropertySystem::getProperty(int index) const { return properties[index]; }
int PropertySystem::getRequestCount() const { return requestCount; }
const Maintenance& PropertySystem::getRequest(int index) const { return requests[index]; }

// =====================================================
//  1. ADD RECORD
// =====================================================
void PropertySystem::addOwnerInteractive() {
    int id = readInt("Owner ID: ");
    if (findPersonIndex(id) != -1) {
        throw invalid_argument("That ID is already used by another person.");
    }
    string name = readLine("Name: ");
    string phone = readLine("Phone (10 digits): ");
    string email = readLine("Email: ");

    storePerson(new Owner(id, name, phone, email));
    cout << "Owner added successfully.\n";
}

void PropertySystem::addTenantInteractive() {
    int id = readInt("Tenant ID: ");
    if (findPersonIndex(id) != -1) {
        throw invalid_argument("That ID is already used by another person.");
    }
    string name = readLine("Name: ");
    string phone = readLine("Phone (10 digits): ");
    int propertyId = readInt("Property ID to rent (0 for none): ");

    int pIndex = -1;
    if (propertyId != 0) {
        pIndex = findPropertyIndex(propertyId);
        if (pIndex == -1) {
            throw invalid_argument("Property not found.");
        }
        if (properties[pIndex].getTenantId() != 0) {
            throw invalid_argument("That property already has a tenant.");
        }
    }

    storePerson(new Tenant(id, name, phone, propertyId));
    if (pIndex != -1) {
        properties[pIndex].setTenantId(id);
    }
    cout << "Tenant added successfully.\n";
}

void PropertySystem::addPropertyInteractive() {
    int id = readInt("Property ID: ");
    if (findPropertyIndex(id) != -1) {
        throw invalid_argument("That property ID already exists.");
    }
    string address = readLine("Address: ");
    string type = readLine("Type (Flat/House/Shop): ");
    int ownerId = readInt("Owner ID: ");
    if (findPersonIndexOfType(ownerId, "Owner") == -1) {
        throw invalid_argument("Owner not found. Add the owner first.");
    }
    double rent = readDouble("Monthly rent: ");

    storeProperty(Property(id, address, type, ownerId, rent));
    cout << "Property added successfully.\n";
}

void PropertySystem::addRecord() {
    cout << "\n--- Add Record ---\n";
    cout << "1. Owner\n2. Tenant\n3. Property\n";
    int choice = readInt("Choose type: ");
    try {
        if (choice == 1) addOwnerInteractive();
        else if (choice == 2) addTenantInteractive();
        else if (choice == 3) addPropertyInteractive();
        else cout << "Invalid choice.\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

// =====================================================
//  2. DISPLAY RECORDS
// =====================================================
void PropertySystem::displayPeopleOfType(const string& type) const {
    int shown = 0;
    for (int i = 0; i < peopleCount; i++) {
        if (people[i]->getType() == type) {
            people[i]->display();     // runtime polymorphism
            shown++;
        }
    }
    if (shown == 0) cout << "No records found.\n";
}

void PropertySystem::displayRecords() {
    cout << "\n--- Display Records ---\n";
    cout << "1. Owners\n2. Tenants\n3. Properties\n4. Maintenance Requests\n";
    int choice = readInt("Choose type: ");
    cout << "\n";

    if (choice == 1) {
        displayPeopleOfType("Owner");
    } else if (choice == 2) {
        displayPeopleOfType("Tenant");
    } else if (choice == 3) {
        if (propertyCount == 0) cout << "No records found.\n";
        for (int i = 0; i < propertyCount; i++) properties[i].display();
    } else if (choice == 4) {
        if (requestCount == 0) cout << "No records found.\n";
        for (int i = 0; i < requestCount; i++) requests[i].display();
    } else {
        cout << "Invalid choice.\n";
    }
}

// =====================================================
//  3. SEARCH RECORD
// =====================================================
void PropertySystem::searchRecord() {
    cout << "\n--- Search Record (by ID) ---\n";
    cout << "1. Owner\n2. Tenant\n3. Property\n4. Maintenance Request\n";
    int choice = readInt("Choose type: ");
    if (choice < 1 || choice > 4) {
        cout << "Invalid choice.\n";
        return;
    }
    int id = readInt("Enter ID to search: ");
    cout << "\n";

    if (choice == 1 || choice == 2) {
        string type = (choice == 1) ? "Owner" : "Tenant";
        int index = findPersonIndexOfType(id, type);
        if (index == -1) cout << type << " not found.\n";
        else people[index]->display();
    } else if (choice == 3) {
        int index = findPropertyIndex(id);
        if (index == -1) cout << "Property not found.\n";
        else properties[index].display();
    } else {
        int index = findRequestIndex(id);
        if (index == -1) cout << "Request not found.\n";
        else requests[index].display();
    }
}

// =====================================================
//  4. UPDATE RECORD
// =====================================================
void PropertySystem::updateRecord() {
    cout << "\n--- Update Record ---\n";
    cout << "1. Owner\n2. Tenant\n3. Property\n";
    int choice = readInt("Choose type: ");
    if (choice < 1 || choice > 3) {
        cout << "Invalid choice.\n";
        return;
    }
    int id = readInt("Enter ID to update: ");

    try {
        if (choice == 1 || choice == 2) {
            string type = (choice == 1) ? "Owner" : "Tenant";
            int index = findPersonIndexOfType(id, type);
            if (index == -1) {
                cout << type << " not found.\n";
                return;
            }
            cout << "Current record:\n";
            people[index]->display();
            cout << "(Press Enter to keep the old value)\n";

            string name = readLine("New name: ");
            if (!name.empty()) people[index]->setName(name);

            string phone = readLine("New phone: ");
            if (!phone.empty()) people[index]->setPhone(phone);

            if (choice == 1) {
                Owner* owner = dynamic_cast<Owner*>(people[index]);
                string email = readLine("New email: ");
                if (owner != nullptr && !email.empty()) owner->setEmail(email);
            }
            cout << "Record updated.\n";
        } else {
            int index = findPropertyIndex(id);
            if (index == -1) {
                cout << "Property not found.\n";
                return;
            }
            cout << "Current record:\n";
            properties[index].display();
            cout << "(Press Enter to keep the old value)\n";

            string address = readLine("New address: ");
            if (!address.empty()) properties[index].setAddress(address);

            string type = readLine("New type: ");
            if (!type.empty()) properties[index].setPropertyType(type);

            double rent = readDouble("New monthly rent (0 to keep old): ");
            if (rent != 0) properties[index].setMonthlyRent(rent);

            cout << "Record updated.\n";
        }
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

// =====================================================
//  5. DELETE RECORD
// =====================================================
void PropertySystem::deleteRecord() {
    cout << "\n--- Delete Record ---\n";
    cout << "1. Owner\n2. Tenant\n3. Property\n4. Maintenance Request\n";
    int choice = readInt("Choose type: ");
    if (choice < 1 || choice > 4) {
        cout << "Invalid choice.\n";
        return;
    }
    int id = readInt("Enter ID to delete: ");

    try {
        if (choice == 1) {
            int index = findPersonIndexOfType(id, "Owner");
            if (index == -1) throw invalid_argument("Owner not found.");
            for (int i = 0; i < propertyCount; i++) {
                if (properties[i].getOwnerId() == id) {
                    throw logic_error("This owner still owns properties. Delete those first.");
                }
            }
            if (readLine("Are you sure? (y/n): ") != "y") {
                cout << "Cancelled.\n";
                return;
            }
            removePersonAt(index);

        } else if (choice == 2) {
            int index = findPersonIndexOfType(id, "Tenant");
            if (index == -1) throw invalid_argument("Tenant not found.");
            if (readLine("Are you sure? (y/n): ") != "y") {
                cout << "Cancelled.\n";
                return;
            }
            for (int i = 0; i < propertyCount; i++) {
                if (properties[i].getTenantId() == id) properties[i].setTenantId(0);
            }
            removePersonAt(index);

        } else if (choice == 3) {
            int index = findPropertyIndex(id);
            if (index == -1) throw invalid_argument("Property not found.");
            for (int i = 0; i < requestCount; i++) {
                if (requests[i].getPropertyId() == id) {
                    throw logic_error("This property has maintenance requests. Delete those first.");
                }
            }
            if (readLine("Are you sure? (y/n): ") != "y") {
                cout << "Cancelled.\n";
                return;
            }
            int tenantId = properties[index].getTenantId();
            if (tenantId != 0) {
                int tIndex = findPersonIndexOfType(tenantId, "Tenant");
                if (tIndex != -1) {
                    Tenant* tenant = dynamic_cast<Tenant*>(people[tIndex]);
                    if (tenant != nullptr) tenant->setPropertyId(0);
                }
            }
            removePropertyAt(index);

        } else {
            int index = findRequestIndex(id);
            if (index == -1) throw invalid_argument("Request not found.");
            if (readLine("Are you sure? (y/n): ") != "y") {
                cout << "Cancelled.\n";
                return;
            }
            removeRequestAt(index);
        }
        cout << "Record deleted.\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

// =====================================================
//  6. MAIN TRANSACTION: maintenance requests
// =====================================================
void PropertySystem::raiseRequest() {
    int id = readInt("New request ID: ");
    if (findRequestIndex(id) != -1) {
        throw invalid_argument("That request ID already exists.");
    }
    int propertyId = readInt("Property ID: ");
    if (findPropertyIndex(propertyId) == -1) {
        throw invalid_argument("Property not found.");
    }
    string description = readLine("Describe the problem: ");

    storeRequest(Maintenance(id, propertyId, description, "Pending", 0.0));
    cout << "Maintenance request created (status: Pending).\n";
}

void PropertySystem::completeRequest() {
    int id = readInt("Request ID to complete: ");
    int index = findRequestIndex(id);
    if (index == -1) {
        throw invalid_argument("Request not found.");
    }
    double cost = readDouble("Final repair cost: ");
    requests[index].completeRequest(cost);
    cout << "Request marked as Completed.\n";
}

void PropertySystem::mainTransaction() {
    cout << "\n--- Maintenance Process ---\n";
    cout << "1. Raise a new maintenance request\n";
    cout << "2. Complete a maintenance request\n";
    int choice = readInt("Choose: ");
    try {
        if (choice == 1) raiseRequest();
        else if (choice == 2) completeRequest();
        else cout << "Invalid choice.\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

// =====================================================
//  7. REPORT
// =====================================================
void PropertySystem::report() {
    int owners = 0, tenants = 0;
    for (int i = 0; i < peopleCount; i++) {
        if (people[i]->getType() == "Owner") owners++;
        else tenants++;
    }

    int occupied = 0;
    double rentIncome = 0;
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].getTenantId() != 0) {
            occupied++;
            rentIncome += properties[i].getMonthlyRent();
        }
    }

    int pending = 0, completed = 0;
    double totalCost = 0;
    for (int i = 0; i < requestCount; i++) {
        if (requests[i].isCompleted()) {
            completed++;
            totalCost += requests[i].getCost();
        } else {
            pending++;
        }
    }

    cout << fixed << setprecision(2);
    cout << "\n========== SUMMARY REPORT ==========\n";
    cout << "Owners                : " << owners << "\n";
    cout << "Tenants               : " << tenants << "\n";
    cout << "Properties            : " << propertyCount << "\n";
    cout << "  Occupied            : " << occupied << "\n";
    cout << "  Vacant              : " << (propertyCount - occupied) << "\n";
    cout << "Monthly rent income   : " << rentIncome << "\n";
    cout << "Pending requests      : " << pending << "\n";
    cout << "Completed requests    : " << completed << "\n";
    cout << "Total maintenance cost: " << totalCost << "\n";

    if (pending > 0) {
        cout << "\n--- Pending Requests ---\n";
        for (int i = 0; i < requestCount; i++) {
            if (!requests[i].isCompleted()) requests[i].display();
        }
    }
    cout << "====================================\n";
    cout.unsetf(ios::fixed);
}

// =====================================================
//  8. SAVE / LOAD
// =====================================================
void PropertySystem::saveData() {
    try {
        fileManager.saveAll(*this);
        cout << "Data saved successfully.\n";
    } catch (const exception& e) {
        cout << "Error while saving: " << e.what() << "\n";
    }
}

void PropertySystem::loadData() {
    clearAll();   // remove old data from memory first
    try {
        fileManager.loadAll(*this);
        cout << "Data loaded: " << peopleCount << " people, "
             << propertyCount << " properties, "
             << requestCount << " requests.\n";
    } catch (const exception& e) {
        cout << "Error while loading: " << e.what() << "\n";
    }
}