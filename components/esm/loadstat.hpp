/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENMW_ESM_STAT_H
#define OPENMW_ESM_STAT_H

#include <string>

namespace ESM {

class ESMReader;
class ESMWriter;

/*
 * Definition of static object.
 *
 * A stat record is basically just a reference to a nif file. Some
 * esps seem to contain copies of the STAT entries from the esms, and
 * the esms themselves contain several identical entries. Perhaps all
 * statics referenced in a file is also put in the file? Since we are
 * only reading files it doesn't much matter to us, but it would if we
 * were writing our own ESM/ESPs. You can check some files later when
 * you decode the CELL blocks, if you want to test this hypothesis.
 */

struct Static
{
  std::string mId, mModel;

  void load(ESMReader &esm);
  void save(ESMWriter &esm);
};
}
#endif
