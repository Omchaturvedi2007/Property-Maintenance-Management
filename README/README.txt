PROPERTY MAINTENANCE MANAGEMENT SYSTEM (C++)
Enrollment Number : IU2541230535
Project Code      : CPP60
==========================================

FOLDER STRUCTURE
  Source/         main.cpp and all .h/.cpp files
  Data/           people.txt, properties.txt, requests.txt
  Diagrams/       UseCase, ClassDiagram, Sequence1_MainTransaction, Sequence2_Persistence (.puml / .png)
  Executable/     Project.exe
  Screenshots/    screenshot1.png through screenshot7.png
  README.txt      project overview and execution guide
  ProjectReport.pdf report documentation

HOW TO BUILD (needs g++ with C++17 support, e.g. MinGW-w64)
  Windows : g++ -std=c++17 Source/*.cpp -o Executable/Project.exe
  Linux/Mac: g++ -std=c++17 Source/*.cpp -o Executable/Project

HOW TO RUN
  Run from the project root:   Executable\Project.exe
  (The program finds and manages data files in "Data/".)

MENU
  1 Add Record        (Owner / Tenant / Property)
  2 Display Records   (Owners, Tenants, Properties, Maintenance Requests)
  3 Search Record     (by ID for Owner, Tenant, Property, or Maintenance Request)
  4 Update Record     (Owner email/phone, Tenant details, Property rent/address)
  5 Delete Record     (Owner, Tenant, Property, Maintenance Request - with safety checks)
  6 Main Transaction  (Maintenance Requests: Raise Request / Complete Request & Cost)
  7 Report            (Occupancy, rent income, pending/completed requests, total repair costs)
  8 Save/Load         (Manual file persistence control)
  9 Exit              (Auto-saves data before exit)

TEST PERSISTENCE
  1. Run the program, add an owner, add a property, and register a tenant.
  2. Choose 9 (Exit). Data/*.txt files are automatically updated.
  3. Run again: all records are restored automatically at START.

SAMPLE FLOW
  Add Owner -> Add Property -> Add Tenant -> 6/1 Raise Maintenance Request -> 6/2 Complete Request (Cost) -> 7 Report

DESIGN NOTES
  Person is an abstract base class; Owner and Tenant override getType() and toFileString()
  (runtime polymorphism managed via Person** array).
  Dynamic memory: Person** people = new Person*[cap]; Property* properties = new Property[cap];
  Maintenance* requests = new Maintenance[cap].
  Arrays double in size automatically when full (growPeople, growProperties, growRequests)
  and are safely deallocated with delete[] in ~PropertySystem().
  Robust input handling in Input.cpp prevents infinite loops and handles invalid input errors cleanly.