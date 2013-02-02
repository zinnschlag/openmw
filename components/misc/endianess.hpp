#ifndef OPENMW_ENDIANESS_H
#define OPENMW_ENDIANESS_H

#include <libs/platform/stdint.h>
#include <endian.h>

#define FOURCHAR(a,b,c,d) ((uint32_t)(((a)<<24) | ((b)<<16) | ((c)<<8) | (d)))

float reverseFloat(const float inFloat);
float letoh_float(const float f);
float htole_float(const float f);
float betoh_float(const float f);
float htobe_float(const float f);

#endif
