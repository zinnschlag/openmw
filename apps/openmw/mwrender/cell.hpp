/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_RENDER_CELL_H
#define GAME_RENDER_CELL_H

#include <string>

namespace MWRender
{
    class CellRender
    {
        public:

            virtual ~CellRender() {};

            /// Make the cell visible. Load the cell if necessary.
            virtual void show() = 0;

            /// Remove the cell from rendering, but don't remove it from
            /// memory.
            virtual void hide() = 0;

            /// Destroy all rendering objects connected with this cell.
            virtual void destroy() = 0;

            /// Make the reference with the given handle visible.
            virtual void enable (const std::string& handle) = 0;

            /// Make the reference with the given handle invisible.
            virtual void disable (const std::string& handle) = 0;

            /// Remove the reference with the given handle permanently from the scene.
            virtual void deleteObject (const std::string& handle) = 0;
    };
}

#endif
