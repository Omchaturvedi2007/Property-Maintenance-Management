#ifndef PERSON_H
#define PERSON_H

#include <string>

// Base class for Owner and Tenant.
// It is abstract: it has pure virtual functions, so you cannot create a Person directly.
class Person {
protected:
    int id;
    std::string name;
    std::string phone;

public:
    Person();                                                        // default constructor
    Person(int id, const std::string& name, const std::string& phone); // parameterized constructor
    virtual ~Person();                                               // virtual destructor

    int getId() const;
    std::string getName() const;
    std::string getPhone() const;

    void setId(int id);
    void setName(const std::string& name);
    void setPhone(const std::string& phone);

    virtual void display() const;                  // runtime polymorphism
    virtual std::string getType() const = 0;       // "Owner" or "Tenant"
    virtual std::string toFileString() const = 0;  // one line for the data file
};

#endif