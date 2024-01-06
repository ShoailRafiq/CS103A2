
#ifndef CONSOLE
#define CONSOLE 1

#include <iostream>
#include <stdint.h>
#include <string>

using std::int32_t;
using std::string;

/// <summary>
/// Prints a divider line to the console
/// </summary>
void displayDivider();

/// <summary>
/// Reads an int value from user input. Handles invalid input
/// and validation of the min max range
/// </summary>
/// <param name="min">The minimum allowed value</param>
/// <param name="max">The maximum allowed value</param>
/// <returns>The value from user input</returns>
int32_t getInputInt(int32_t min, int32_t max);

/// <summary>
/// Reads a float value from user input, handles invalid
/// input and validation of the min max range
/// </summary>
/// <param name="min">The minimum allowed value</param>
/// <param name="max">The maximum allowed value</param>
/// <returns>The value from user input</returns>
float getInputFloat(float min, float max);

/// <summary>
/// Reads a boolean input from user input
/// </summary>
/// <returns>The boolean value</returns>
bool getInputBool();

/// <summary>
/// Reads a string from user input
/// </summary>
/// <returns></returns>
string getInputString();

#endif USER_INPUT