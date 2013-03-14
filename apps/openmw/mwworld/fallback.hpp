#ifndef GAME_MWWORLD_FALLBACK_H
#define GAME_MWWORLD_FALLBACK_H
#include <OgreColourValue.h>
namespace MWWorld
{
    class Fallback
    {
            std::map<std::string,std::string> mFallbackMap;
        public:
            Fallback();
            void setFallbackMap(const std::map<std::string,std::string>& fallbackMap);
            std::string getFallbackString(const std::string& fall) const;
            float getFallbackFloat(const std::string& fall) const;
            bool getFallbackBool(const std::string& fall) const;
            Ogre::ColourValue getFallbackColour(const std::string& fall) const;
    };
}
#endif
