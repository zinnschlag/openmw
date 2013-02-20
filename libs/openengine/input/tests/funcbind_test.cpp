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

#include "../func_binder.hpp"

void f1(int i, const void *p)
{
  cout << "  F1 i=" << i << endl;

  if(p)
    cout << "  Got a nice gift: "
         << *((const float*)p) << endl;
}

void f2(int i, const void *p)
{
  cout << "  F2 i=" << i << endl;
}

using namespace OEngine::Input;

int main()
{
  cout << "This will test the function binding system\n";

  FuncBinder bnd(5);

  bnd.bind(0, &f1, "This is action 1");
  bnd.bind(1, &f2);
  bnd.bind(2, &f1, "This is action 3");
  bnd.bind(3, &f2, "This is action 4");

  bnd.unbind(2);

  for(int i=0; i<5; i++)
    {
      cout << "Calling " << i << ": '" << bnd.getName(i) << "'\n";
      bnd.call(i);
      if(!bnd.isBound(i)) cout << "  (not bound)\n";
    }

  cout << "\nCalling with parameter:\n";
  float f = 3.1415;
  bnd.call(0, &f);

  return 0;
}
