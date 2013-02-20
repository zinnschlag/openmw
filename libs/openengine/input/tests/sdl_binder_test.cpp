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
#include "../dispatcher.hpp"
#include "../poller.hpp"

using namespace std;
using namespace Mangle::Input;
using namespace OEngine::Input;

enum Actions
  {
    A_Quit,
    A_Left,
    A_Right,

    A_LAST
  };

bool quit=false;

void doExit(int,const void*)
{
  quit = true;
}

void goLeft(int,const void*)
{
  cout << "Going left\n";
}

int main(int argc, char** argv)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetVideoMode(640, 480, 0, SDL_SWSURFACE);
  SDLDriver input;
  Dispatcher *disp = new Dispatcher(A_LAST);
  Poller poll(input);

  input.setEvent(EventPtr(disp));

  disp->funcs.bind(A_Quit, &doExit);
  disp->funcs.bind(A_Left, &goLeft);

  disp->bind(A_Quit, SDLK_q);
  disp->bind(A_Left, SDLK_a);
  disp->bind(A_Left, SDLK_LEFT);

  poll.bind(A_Right, SDLK_d);
  poll.bind(A_Right, SDLK_RIGHT);

  cout << "Hold the Q key to quit:\n";
  //input->setEvent(&mycb);
  while(!quit)
    {
      input.capture();
      if(poll.isDown(A_Right))
        cout << "We're going right!\n";
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
