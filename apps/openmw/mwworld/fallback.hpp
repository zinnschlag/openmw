#ifndef GAME_MWWORLD_FALLBACK_H
#define GAME_MWWORLD_FALLBACK_H
#include <OgreColourValue.h>
namespace MWWorld
{
    class Fallback
    {
            const std::map<std::string,std::string>& mFallbackMap;
        public:
            Fallback(const std::map<std::string,std::string>& fallbackMap);
            std::string getFallbackString(const std::string& fall);
            float getFallbackFloat(const std::string& fall);
            bool getFallbackBool(const std::string& fall);
            Ogre::ColourValue getFallbackColour(const std::string& fall);
    };
}
#endif
