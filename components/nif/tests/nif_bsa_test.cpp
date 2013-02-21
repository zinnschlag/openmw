/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

/*
  Runs NIFFile through all the NIFs in Morrowind.bsa.
 */

#include "../nif_file.hpp"
#include "../../bsa/bsa_file.hpp"
#include "../../tools/stringops.hpp"
#include <iostream>

using namespace Mangle::Stream;
using namespace std;
using namespace Nif;

int main(int argc, char **args)
{
  BSAFile bsa;
  cout << "Reading Morrowind.bsa\n";
  bsa.open("../../data/Morrowind.bsa");

  const BSAFile::FileList &files = bsa.getList();

  for(int i=0; i<files.size(); i++)
    {
      const char *n = files[i].name;
      if(!ends(n, ".nif")) continue;

      cout << "Decoding " << n << endl;
      NIFFile nif(bsa.getFile(n), n);
    }
}
