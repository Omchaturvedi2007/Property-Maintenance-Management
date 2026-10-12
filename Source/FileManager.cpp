#include "FileManager.h"
#include "PropertySystem.h"
#include "Owner.h"
#include "Tenant.h"
#include "Property.h"
#include "Maintenance.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
using namespace std;

// Splits a line like "a|b|c" into pieces
static vector<string> splitLine(const string& line) {
    vector<string> parts;
    string piece;
    stringstream ss(line);
    while (getline(ss, piece, '|')) {
        parts.push_back(piece);
    }
    return parts;
}

FileManager::FileManager()
    : peopleFile("Data/people.txt"),
      propertyFile("Data/properties.txt"),
      requestFile("Data/requests.txt") {
}

FileManager::~FileManager() {
}

void FileManager::saveAll(const PropertySystem& system) const {
    ofstream pf(peopleFile.c_str());
    if (!pf) {
        throw runtime_error("Cannot write " + peopleFile + ". Does the Data folder exist?");
    }
    for (int i = 0; i < system.getPersonCount(); i++) {
        pf << system.getPerson(i)->toFileString() << "\n";   // polymorphic call
    }
    pf.close();

    ofstream prf(propertyFile.c_str());
    if (!prf) {
        throw runtime_error("Cannot write " + propertyFile + ".");
    }
    for (int i = 0; i < system.getPropertyCount(); i++) {
        prf << system.getProperty(i).toFileString() << "\n";
    }
    prf.close();

    ofstream rf(requestFile.c_str());
    if (!rf) {
        throw runtime_error("Cannot write " + requestFile + ".");
    }
    for (int i = 0; i < system.getRequestCount(); i++) {
        rf << system.getRequest(i).toFileString() << "\n";
    }
    rf.close();
}

void FileManager::loadAll(PropertySystem& system) const {
    string line;

    // ----- people (owners and tenants) -----
    ifstream pf(peopleFile.c_str());
    if (pf) {
        while (getline(pf, line)) {
            if (line.empty()) continue;
            vector<string> p = splitLine(line);
            try {
                if (p[0] == "O" && p.size() == 5) {
                    system.storePerson(new Owner(stoi(p[1]), p[2], p[3], p[4]));
                } else if (p[0] == "T" && p.size() == 5) {
                    system.storePerson(new Tenant(stoi(p[1]), p[2], p[3], stoi(p[4])));
                } else {
                    cout << "Skipping bad line: " << line << "\n";
                }
            } catch (const exception& e) {
                cout << "Skipping bad line (" << e.what() << "): " << line << "\n";
            }
        }
        pf.close();
    }

    // ----- properties -----
    ifstream prf(propertyFile.c_str());
    if (prf) {
        while (getline(prf, line)) {
            if (line.empty()) continue;
            vector<string> p = splitLine(line);
            try {
                if (p.size() == 6) {
                    Property prop(stoi(p[0]), p[1], p[2], stoi(p[3]), stod(p[5]));
                    prop.setTenantId(stoi(p[4]));
                    system.storeProperty(prop);
                } else {
                    cout << "Skipping bad line: " << line << "\n";
                }
            } catch (const exception& e) {
                cout << "Skipping bad line (" << e.what() << "): " << line << "\n";
            }
        }
        prf.close();
    }

    // ----- maintenance requests -----
    ifstream rf(requestFile.c_str());
    if (rf) {
        while (getline(rf, line)) {
            if (line.empty()) continue;
            vector<string> p = splitLine(line);
            try {
                if (p.size() == 5) {
                    Maintenance m(stoi(p[0]), stoi(p[1]), p[2], p[3], stod(p[4]));
                    system.storeRequest(m);
                } else {
                    cout << "Skipping bad line: " << line << "\n";
                }
            } catch (const exception& e) {
                cout << "Skipping bad line (" << e.what() << "): " << line << "\n";
            }
        }
        rf.close();
    }
}