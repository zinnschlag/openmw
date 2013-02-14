#ifndef OPENMW_ENDIANESS_H
#define OPENMW_ENDIANESS_H

#include <libs/platform/stdint.h>
#include <endian.h>
#include <OgrePlatform.h>

#define FOURCHAR(a,b,c,d) ((uint32_t)(((a)<<24) | ((b)<<16) | ((c)<<8) | (d)))

float reverseFloat(const float inFloat);

#if OGRE_ENDIAN == OGRE_ENDIAN_BIG
#  define letoh_float(f) reverseFloat(f)
#  define htole_float(f) reverseFloat(f)
#  define betoh_float(f) (f)
#  define htobe_float(f) (f)
#elif OGRE_ENDIAN == OGRE_ENDIAN_LITTLE
#  define letoh_float(f) (f)
#  define htole_float(f) (f)
#  define betoh_float(f) reverseFloat(f)
#  define htobe_float(f) reverseFloat(f)
#endif

#endif
