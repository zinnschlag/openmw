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

float letoh_float(const float f)
{
    uint8_t swapTest[2] = { 0, 1 };
    if(*(uint16_t*)swapTest == 1)
    {
        // big endian
        return reverseFloat(f);
    }
    else
    {
        // little endian
        return f;
    }
}

float htole_float(const float f)
{
    uint8_t swapTest[2] = { 0, 1 };
    if(*(uint16_t*)swapTest == 1)
    {
        // big endian
        return reverseFloat(f);
    }
    else
    {
        // little endian
        return f;
    }
}

float betoh_float(const float f)
{
    uint8_t swapTest[2] = { 0, 1 };
    if(*(uint16_t*)swapTest == 1)
    {
        // big endian
        return f;
    }
    else
    {
        // little endian
        return reverseFloat(f);
    }
}

float htobe_float(const float f)
{
    uint8_t swapTest[2] = { 0, 1 };
    if(*(uint16_t*)swapTest == 1)
    {
        // big endian
        return f;
    }
    else
    {
        // little endian
        return reverseFloat(f);
    }
}
