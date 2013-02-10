#ifndef _COMPONENTS_USERDEFAULTS_H
#define _COMPONENTS_USERDEFAULTS_H

#include <OgreConfigFile.h>
#include <MyGUI_Types.h>

namespace Settings
{
    typedef std::pair < std::string, std::string > CategoryDefaults;
    typedef std::map < CategoryDefaults, std::string > CategoryDefaultsValueMap;

    ///
    /// \brief UserDefaults management (saves GUI settings between sessions)
    ///
    class UserDefaults
    {
    public:
        static Ogre::ConfigFile mFile;
        static Ogre::ConfigFile mDefaultFile;

        static CategoryDefaultsValueMap mNewSettings;
        ///< tracks all the settings that are in the first-run file, but not in user file yet

        void loadDefault (const std::string& file);
        ///< load file as the first-run defaults (can be overridden by user defaults)

        void loadUser (const std::string& file);
        ///< load file as user defaults

        void saveUser (const std::string& file);
        ///< save user defaults to file

        static MyGUI::IntCoord getMyGUICoord(const std::string& category);
        static void setMyGUICoord(const std::string& category, const MyGUI::IntCoord& value);

        static const int getInt (const std::string& setting, const std::string& category);
        static const float getFloat (const std::string& setting, const std::string& category);
        static const std::string getString (const std::string& setting, const std::string& category);
        static const bool getBool (const std::string& setting, const std::string& category);

        static void setInt (const std::string& setting, const std::string& category, const int value);
        static void setFloat (const std::string& setting, const std::string& category, const float value);
        static void setString (const std::string& setting, const std::string& category, const std::string& value);
        static void setBool (const std::string& setting, const std::string& category, const bool value);
    };

}

#endif // _COMPONENTS_USERDEFAULTS_H
