
#ifndef USER_INPUT
#define USER_INPUT 1

#include <stdint.h>
#include <string>

using std::int32_t;
using std::string;

/// <summary>
/// Reads an int value from user input
/// </summary>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns></returns>
int32_t getInputInt(int32_t min, int32_t max);

/// <summary>
/// Reads a float value from user input
/// </summary>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns></returns>
float getInputFloat(float min, float max);

/// <summary>
/// Reads a string from user input
/// </summary>
/// <returns></returns>
string getInputString();

#endif USER_INPUT