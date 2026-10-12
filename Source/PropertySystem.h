#ifndef PROPERTYSYSTEM_H
#define PROPERTYSYSTEM_H

#include <string>
#include "Person.h"
#include "Property.h"
#include "Maintenance.h"
#include "FileManager.h"

class PropertySystem {
private:
    // Dynamic arrays (they grow automatically when full)
    Person** people;            // array of pointers -> Owner or Tenant objects
    int peopleCount;
    int peopleCapacity;

    Property* properties;       // dynamic array of Property
    int propertyCount;
    int propertyCapacity;

    Maintenance* requests;      // dynamic array of Maintenance
    int requestCount;
    int requestCapacity;

    FileManager fileManager;

    // helpers for memory
    void growPeople();
    void growProperties();
    void growRequests();
    void clearAll();

    // helpers for searching
    int findPersonIndex(int id) const;
    int findPersonIndexOfType(int id, const std::string& type) const;
    int findPropertyIndex(int id) const;
    int findRequestIndex(int id) const;

    // helpers for removing
    void removePersonAt(int index);
    void removePropertyAt(int index);
    void removeRequestAt(int index);

    // helpers for menu actions
    void addOwnerInteractive();
    void addTenantInteractive();
    void addPropertyInteractive();
    void displayPeopleOfType(const std::string& type) const;
    void raiseRequest();
    void completeRequest();

public:
    PropertySystem();
    ~PropertySystem();

    // copying this class would break the dynamic arrays, so we forbid it
    PropertySystem(const PropertySystem&) = delete;
    PropertySystem& operator=(const PropertySystem&) = delete;

    // ----- main menu actions -----
    void addRecord();
    void displayRecords();
    void searchRecord();
    void updateRecord();
    void deleteRecord();
    void mainTransaction();
    void report();
    void saveData();
    void loadData();

    // ----- used by FileManager -----
    void storePerson(Person* person);
    void storeProperty(const Property& property);
    void storeRequest(const Maintenance& request);

    int getPersonCount() const;
    const Person* getPerson(int index) const;
    int getPropertyCount() const;
    const Property& getProperty(int index) const;
    int getRequestCount() const;
    const Maintenance& getRequest(int index) const;
};

#endif