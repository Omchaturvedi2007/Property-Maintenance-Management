#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <string>

class Maintenance {
private:
    int id;
    int propertyId;
    std::string description;
    std::string status;   // "Pending" or "Completed"
    double cost;

public:
    Maintenance();
    Maintenance(int id, int propertyId, const std::string& description,
                const std::string& status, double cost);
    ~Maintenance();

    int getId() const;
    int getPropertyId() const;
    std::string getDescription() const;
    std::string getStatus() const;
    double getCost() const;

    void setId(int id);
    void setPropertyId(int propertyId);
    void setDescription(const std::string& description);
    void setStatus(const std::string& status);
    void setCost(double cost);

    bool isCompleted() const;
    void completeRequest(double finalCost);

    void display() const;
    std::string toFileString() const;
};

#endif