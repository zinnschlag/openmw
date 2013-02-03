#ifndef OPENMW_ESM_COMMON_H
#define OPENMW_ESM_COMMON_H

#include <string>

#include <libs/platform/stdint.h>
#include <libs/platform/string.h>

#include "components/misc/endianess.hpp"

namespace ESM
{
enum Version  // in little endian
  {
    VER_12 = 0x3f99999a,
    VER_13 = 0x3fa66666
  };

enum FileType
  {
    FT_ESP = 0,       // Plugin
    FT_ESM = 1,       // Master
    FT_ESS = 32       // Savegame
  };

// Used to mark special files. The original ESM files are given
// special treatment in a few places, most noticably in loading and
// filtering out "dirtly" GMST entries correctly.
enum SpecialFile
  {
    SF_Other,
    SF_Morrowind,
    SF_Tribunal,
    SF_Bloodmoon
  };

/* A class used for holding fixed-length strings. */
/* In the case of LEN=4, it can be more efficient to match the string
   as a 32 bit number. */
template <int LEN>
union NAME_T
{
  char name[LEN];
  uint32_t val32h;  // in host byte order

  bool operator==(const char *str) const
  {
    for(int i=0; i<LEN; i++)
      if(name[i] != str[i]) return false;
      else if(name[i] == 0) return true;
    return str[LEN] == 0;
  }
  bool operator!=(const char *str) const { return !((*this)==str); }

  bool operator==(const std::string &str) const
  {
    return (*this) == str.c_str();
  }
  bool operator!=(const std::string &str) const { return !((*this)==str); }

  bool operator==(uint32_t v32be) const { return val32h == be32toh(v32be); }
  bool operator!=(uint32_t v32be) const { return val32h != be32toh(v32be); }

  std::string toString() const { return std::string(name, strnlen(name, LEN)); }

  uint32_t toInt32BE() const { return htobe32(val32h); }
  void setAs32BE(uint32_t v32be) { val32h = be32toh(v32be); }
};

typedef NAME_T<4> NAME;
typedef NAME_T<32> NAME32;
typedef NAME_T<64> NAME64;
typedef NAME_T<256> NAME256;

#pragma pack(push)
#pragma pack(1)
/// File header data for all ES files
struct HEDRstruct
{
  /* File format version. This is actually a float, the supported
     versions are 1.2 (0x9a99993f) and 1.3 (0x66666a3f).
  */
  uint32_t version;
  uint32_t type;      // 0=esp, 1=esm, 32=ess
  NAME32 author;      // Author's name
  NAME256 desc;       // File description
  int records;        // Number of records? Not used.
};

// Defines another files (esm or esp) that this file depends upon.
struct MasterData
{
  std::string name;
  uint64_t size;
};

// Data that is only present in save game files
struct SaveData
{
  float pos[6];     // Player position and rotation
  NAME64 cell;      // Cell name
  float unk2;       // Unknown value - possibly game time?
  NAME32 player;    // Player name
};
#pragma pack(pop)

/* This struct defines a file 'context' which can be saved and later
   restored by an ESMReader instance. It will save the position within
   a file, and when restored will let you read from that position as
   if you never left it.
 */
struct ESM_Context
{
  std::string filename;
  uint32_t leftRec, leftSub;
  size_t leftFile;
  NAME recName, subName;
  HEDRstruct header;

  // True if subName has been read but not used.
  bool subCached;

  // File position. Only used for stored contexts, not regularly
  // updated within the reader itself.
  size_t filePos;
};

}

#endif
