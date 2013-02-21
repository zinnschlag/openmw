/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OENGINE_SELECTIONBUFFER_H
#define OENGINE_SELECTIONBUFFER_H


#include <OgreTexture.h>
#include <OgreRenderTarget.h>
#include <OgreMaterialManager.h>

namespace OEngine
{
namespace Render
{

    struct cmp_ColourValue
    {
        bool operator()(const Ogre::ColourValue &a, const Ogre::ColourValue &b) const
        {
        return a.getAsBGRA() < b.getAsBGRA();
        }
    };

    class SelectionBuffer : public Ogre::MaterialManager::Listener
    {
    public:
        SelectionBuffer(Ogre::Camera* camera, int sizeX, int sizeY, int visibilityFlags);
        virtual ~SelectionBuffer();

        int getSelected(int xPos, int yPos);
        ///< @return ID of the selected object

        void update();

        virtual Ogre::Technique* handleSchemeNotFound (
            unsigned short schemeIndex, const Ogre::String &schemeName, Ogre::Material *originalMaterial,
            unsigned short lodIndex, const Ogre::Renderable *rend);


    private:
        Ogre::TexturePtr mTexture;
        Ogre::RenderTexture* mRenderTarget;

        Ogre::Image mBuffer;

        std::map<Ogre::ColourValue, int, cmp_ColourValue> mColourMap;

        Ogre::ColourValue mCurrentColour;

        void getNextColour();
    };

}
}

#endif
