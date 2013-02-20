/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OENGINE_INPUT_POLLER_H
#define OENGINE_INPUT_POLLER_H

#include "dispatch_map.hpp"
#include <mangle/input/driver.hpp>

namespace OEngine {
namespace Input {

/** The poller is used to check (poll) for keys rather than waiting
    for events. */
struct Poller
{
  DispatchMap map;
  Mangle::Input::Driver &input;

  Poller(Mangle::Input::Driver &drv)
    : input(drv) {}

  /** Bind or unbind a given action with a key. The action is the first
      parameter, the key is the second.
  */
  void bind(int in, int out) { map.bind(in, out); }
  void unbind(int in, int out) { map.unbind(in, out); }
  bool isBound(int in) const { return map.isBound(in); }

  /// Check whether a given action button is currently pressed.
  typedef DispatchMap::OutList _O;
  bool isDown(int index) const
  {
    // No bindings, no action
    if(!isBound(index))
      return false;

    // Get all the keys bound to this action, and check them.
    const _O &list = map.getList(index);
    _O::const_iterator it;
    for(it = list.begin(); it != list.end(); it++)
      // If there's any match, we're good to go.
      if(input.isDown(*it)) return true;

    return false;
  }
};
}}
#endif
