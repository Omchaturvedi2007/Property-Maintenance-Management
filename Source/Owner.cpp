#include "Owner.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Owner::Owner() : Person(), email("") {
}

Owner::Owner(int id, const string& name, const string& phone, const string& email)
    : Person(id, name, phone), email("") {
    setEmail(email);
}

Owner::~Owner() {
}

string Owner::getEmail() const { return email; }

void Owner::setEmail(const string& email) {
    if (email.find('@') == string::npos || email.find('|') != string::npos) {
        throw invalid_argument("Email must contain '@' and cannot contain '|'.");
    }
    this->email = email;
}

void Owner::display() const {
    Person::display();
    cout << "    Email: " << email << "\n";
}

string Owner::getType() const {
    return "Owner";
}

string Owner::toFileString() const {
    return "O|" + to_string(id) + "|" + name + "|" + phone + "|" + email;
}