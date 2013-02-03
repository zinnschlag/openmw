#include "endianess.hpp"

float reverseFloat(const float inFloat)
{
    float retVal;
    char *floatToConvert = (char*)&inFloat;
    char *returnFloat = (char*)&retVal;

    // swap the bytes into a temporary buffer
    returnFloat[0] = floatToConvert[3];
    returnFloat[1] = floatToConvert[2];
    returnFloat[2] = floatToConvert[1];
    returnFloat[3] = floatToConvert[0];

    return retVal;
}
