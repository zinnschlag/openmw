#ifndef OPENMW_ESM_DEFS_H
#define OPENMW_ESM_DEFS_H

#include <libs/platform/stdint.h>

#include "components/misc/endianess.hpp"

namespace ESM
{

// Pixel color value. Standard four-byte rr,gg,bb,aa format.
typedef int32_t Color;

enum VarType
{
    VT_Unknown,
    VT_None,
    VT_Short,
    VT_Int,
    VT_Long,
    VT_Float,
    VT_String,
    VT_Ignored
};

enum Specialization
{
    SPC_Combat = 0,
    SPC_Magic = 1,
    SPC_Stealth = 2
};

enum RangeType
{
    RT_Self = 0,
    RT_Touch = 1,
    RT_Target = 2
};

#pragma pack(push)
#pragma pack(1)

// Position and rotation
struct Position
{
    float pos[3];
    float rot[3];
};
#pragma pack(pop)

// Hexadecimal versions of record names (in big-endian order).
enum RecNames
{
    REC_ACTI = FOURCHAR('A','C','T','I'),
    REC_ALCH = FOURCHAR('A','L','C','H'),
    REC_APPA = FOURCHAR('A','P','P','A'),
    REC_ARMO = FOURCHAR('A','R','M','O'),
    REC_BODY = FOURCHAR('B','O','D','Y'),
    REC_BOOK = FOURCHAR('B','O','O','K'),
    REC_BSGN = FOURCHAR('B','S','G','N'),
    REC_CELL = FOURCHAR('C','E','L','L'),
    REC_CLAS = FOURCHAR('C','L','A','S'),
    REC_CLOT = FOURCHAR('C','L','O','T'),
    REC_CNTC = FOURCHAR('C','N','T','C'),
    REC_CONT = FOURCHAR('C','O','N','T'),
    REC_CREA = FOURCHAR('C','R','E','A'),
    REC_CREC = FOURCHAR('C','R','E','C'),
    REC_DIAL = FOURCHAR('D','I','A','L'),
    REC_DOOR = FOURCHAR('D','O','O','R'),
    REC_ENCH = FOURCHAR('E','N','C','H'),
    REC_FACT = FOURCHAR('F','A','C','T'),
    REC_GLOB = FOURCHAR('G','L','O','B'),
    REC_GMST = FOURCHAR('G','M','S','T'),
    REC_INFO = FOURCHAR('I','N','F','O'),
    REC_INGR = FOURCHAR('I','N','G','R'),
    REC_LAND = FOURCHAR('L','A','N','D'),
    REC_LEVC = FOURCHAR('L','E','V','C'),
    REC_LEVI = FOURCHAR('L','E','V','I'),
    REC_LIGH = FOURCHAR('L','I','G','H'),
    REC_LOCK = FOURCHAR('L','O','C','K'),
    REC_LTEX = FOURCHAR('L','T','E','X'),
    REC_MGEF = FOURCHAR('M','G','E','F'),
    REC_MISC = FOURCHAR('M','I','S','C'),
    REC_NPC_ = FOURCHAR('N','P','C','_'),
    REC_NPCC = FOURCHAR('N','P','C','C'),
    REC_PGRD = FOURCHAR('P','G','R','D'),
    REC_PROB = FOURCHAR('P','R','O','B'),
    REC_RACE = FOURCHAR('R','A','C','E'),
    REC_REGN = FOURCHAR('R','E','G','N'),
    REC_REPA = FOURCHAR('R','E','P','A'),
    REC_SCPT = FOURCHAR('S','C','P','T'),
    REC_SKIL = FOURCHAR('S','K','I','L'),
    REC_SNDG = FOURCHAR('S','N','D','G'),
    REC_SOUN = FOURCHAR('S','O','U','N'),
    REC_SPEL = FOURCHAR('S','P','E','L'),
    REC_SSCR = FOURCHAR('S','S','C','R'),
    REC_STAT = FOURCHAR('S','T','A','T'),
    REC_WEAP = FOURCHAR('W','E','A','P')
};

// Hexadecimal versions of the various subrecord names (in big-endian order).
enum SubNames
{
    REC_ANAM = FOURCHAR('A','N','A','M'),
    REC_BNAM = FOURCHAR('B','N','A','M'),
    REC_CNAM = FOURCHAR('C','N','A','M'),
    REC_DELE = FOURCHAR('D','E','L','E'),
    REC_DNAM = FOURCHAR('D','N','A','M'),
    REC_DODT = FOURCHAR('D','O','D','T'),
    REC_FLTV = FOURCHAR('F','L','T','V'),
    REC_FNAM = FOURCHAR('F','N','A','M'),
    REC_INTV = FOURCHAR('I','N','T','V'),
    REC_NAME = FOURCHAR('N','A','M','E'),
    REC_ONAM = FOURCHAR('O','N','A','M'),
    REC_QSTN = FOURCHAR('Q','S','T','N'),
    REC_QSTF = FOURCHAR('Q','S','T','F'),
    REC_QSTR = FOURCHAR('Q','S','T','R'),
    REC_RNAM = FOURCHAR('R','N','A','M'),
    REC_SCVR = FOURCHAR('S','C','V','R'),
    REC_SNAM = FOURCHAR('S','N','A','M')
};

}
#endif
