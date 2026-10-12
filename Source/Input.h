#ifndef INPUT_H
#define INPUT_H

#include <string>

// Small helper functions for safe keyboard input
std::string readLine(const std::string& prompt);
int readInt(const std::string& prompt);
double readDouble(const std::string& prompt);

#endif