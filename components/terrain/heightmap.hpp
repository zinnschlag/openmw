/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TERRAIN_HEIGHTMAP_H
#define TERRAIN_HEIGHTMAP_H

/*
  Generic interface for a structure holding heightmap data.

  A HeightMap returns information about landscape data in the form of
  a regular grid of float heights.
 */

namespace Terrain
{
  struct HeightMap
  {
    // Get height from grid position, counted from 0 to getNumX/Y().
    virtual float getHeight(int x, int y) = 0;

    // Get heigth from vertex index, assumed to be y*getNumX() + x.
    virtual float getHeight(int index) = 0;

    virtual float getMinX() = 0;
    virtual float getMaxX() = 0;
    virtual float getMinY() = 0;
    virtual float getMaxY() = 0;

    virtual int getNumX() = 0;
    virtual int getNumY() = 0;

    // True if the given coordinate is within the grid
    bool isWithin(float x, float y)
    {
      return
        x >= getMinX() && x < getMaxX() &&
        y >= getMinY() && y < getMaxY();
    }
  };
}
#endif
