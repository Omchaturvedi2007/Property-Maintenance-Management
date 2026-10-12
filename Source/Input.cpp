#include "Input.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
using namespace std;

string readLine(const string& prompt) {
    string text;
    cout << prompt;
    if (!getline(cin, text)) {
        cout << "\nInput ended. Closing program.\n";
        exit(0);
    }
    return text;
}

int readInt(const string& prompt) {
    while (true) {
        string text = readLine(prompt);
        try {
            size_t used = 0;
            int value = stoi(text, &used);
            if (used != text.size()) {
                throw invalid_argument("extra characters");
            }
            return value;
        } catch (...) {
            cout << "Please enter a valid whole number.\n";
        }
    }
}

double readDouble(const string& prompt) {
    while (true) {
        string text = readLine(prompt);
        try {
            size_t used = 0;
            double value = stod(text, &used);
            if (used != text.size()) {
                throw invalid_argument("extra characters");
            }
            return value;
        } catch (...) {
            cout << "Please enter a valid number.\n";
        }
    }
}