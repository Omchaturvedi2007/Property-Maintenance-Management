#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

class Property {
private:
    int id;
    std::string address;
    std::string propertyType;   // Flat, House, Shop...
    int ownerId;
    int tenantId;               // 0 = vacant
    double monthlyRent;

public:
    Property();
    Property(int id, const std::string& address, const std::string& propertyType,
             int ownerId, double monthlyRent);
    ~Property();

    int getId() const;
    std::string getAddress() const;
    std::string getPropertyType() const;
    int getOwnerId() const;
    int getTenantId() const;
    double getMonthlyRent() const;

    void setId(int id);
    void setAddress(const std::string& address);
    void setPropertyType(const std::string& propertyType);
    void setOwnerId(int ownerId);
    void setTenantId(int tenantId);
    void setMonthlyRent(double monthlyRent);

    void display() const;
    std::string toFileString() const;
};

#endif