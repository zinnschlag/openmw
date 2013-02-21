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
#include <mangle/input/servers/sdl_driver.hpp>
#include <SDL.h>

using namespace std;
using namespace Mangle::Input;

int main(int argc, char** argv)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetVideoMode(640, 480, 0, SDL_SWSURFACE);
  SDLDriver input;

  cout << "Hold the Q key to quit:\n";
  //input->setEvent(&mycb);
  while(!input.isDown(SDLK_q))
    {
      input.capture();
      SDL_Delay(20);

      if(argc == 1)
        {
          cout << "You are running in script mode, aborting. Run this test with a parameter (any at all) to test the input loop properly\n";
          break;
        }
    }
  cout << "\nBye bye!\n";

  SDL_Quit();
  return 0;
}
