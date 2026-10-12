#ifndef OWNER_H
#define OWNER_H

#include "Person.h"
#include <string>

class Owner : public Person {
private:
    std::string email;

public:
    Owner();
    Owner(int id, const std::string& name, const std::string& phone, const std::string& email);
    ~Owner();

    std::string getEmail() const;
    void setEmail(const std::string& email);

    void display() const override;
    std::string getType() const override;
    std::string toFileString() const override;
};

#endif