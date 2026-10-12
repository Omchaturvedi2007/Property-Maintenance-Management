#ifndef TENANT_H
#define TENANT_H

#include "Person.h"
#include <string>

class Tenant : public Person {
private:
    int propertyId;   // property being rented (0 = none)

public:
    Tenant();
    Tenant(int id, const std::string& name, const std::string& phone, int propertyId);
    ~Tenant();

    int getPropertyId() const;
    void setPropertyId(int propertyId);

    void display() const override;
    std::string getType() const override;
    std::string toFileString() const override;
};

#endif