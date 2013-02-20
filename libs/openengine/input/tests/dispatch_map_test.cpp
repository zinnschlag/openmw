/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
using namespace std;

#include "../dispatch_map.hpp"

using namespace OEngine::Input;

typedef DispatchMap::OutList OutList;
typedef OutList::const_iterator Cit;

void showList(const DispatchMap::OutList &out)
{
  for(Cit it = out.begin();
      it != out.end(); it++)
    {
      cout << "  " << *it << endl;
    }
}

void showAll(DispatchMap &map)
{
  cout << "\nPrinting everything:\n";
  for(DispatchMap::Iit it = map.map.begin();
      it != map.map.end(); it++)
    {
      cout << it->first << ":\n";
      showList(map.getList(it->first));
    }
}

int main()
{
  cout << "Testing the dispatch map\n";

  DispatchMap dsp;

  dsp.bind(1,9);
  dsp.bind(2,-5);
  dsp.bind(2,9);
  dsp.bind(3,10);
  dsp.bind(3,12);
  dsp.bind(3,10);

  showAll(dsp);

  dsp.unbind(1,9);
  dsp.unbind(5,8);
  dsp.unbind(3,11);
  dsp.unbind(3,12);
  dsp.unbind(3,12);

  showAll(dsp);
  return 0;
}
