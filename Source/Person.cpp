#include "Person.h"
#include <iostream>
#include <stdexcept>
#include <cctype>
using namespace std;

Person::Person() : id(0), name(""), phone("") {
}

Person::Person(int id, const string& name, const string& phone) : id(0), name(""), phone("") {
    setId(id);
    setName(name);
    setPhone(phone);
}

Person::~Person() {
}

int Person::getId() const { return id; }
string Person::getName() const { return name; }
string Person::getPhone() const { return phone; }

void Person::setId(int id) {
    if (id <= 0) {
        throw invalid_argument("ID must be a positive number.");
    }
    this->id = id;
}

void Person::setName(const string& name) {
    if (name.empty() || name.find('|') != string::npos) {
        throw invalid_argument("Name cannot be empty or contain the '|' character.");
    }
    this->name = name;
}

void Person::setPhone(const string& phone) {
    if (phone.size() != 10) {
        throw invalid_argument("Phone number must be exactly 10 digits.");
    }
    for (size_t i = 0; i < phone.size(); i++) {
        if (!isdigit(static_cast<unsigned char>(phone[i]))) {
            throw invalid_argument("Phone number must contain digits only.");
        }
    }
    this->phone = phone;
}

void Person::display() const {
    cout << "ID: " << id << " | Type: " << getType()
         << " | Name: " << name << " | Phone: " << phone << "\n";
}