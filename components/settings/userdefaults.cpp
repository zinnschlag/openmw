#include "userdefaults.hpp"

#include <fstream>
#include <stdexcept>

#include <OgreResourceGroupManager.h>
#include <OgreStringConverter.h>

using namespace Settings;

Ogre::ConfigFile UserDefaults::mFile = Ogre::ConfigFile();
Ogre::ConfigFile UserDefaults::mDefaultFile = Ogre::ConfigFile();
CategoryDefaultsValueMap UserDefaults::mNewSettings = CategoryDefaultsValueMap();

void UserDefaults::loadUser (const std::string& file)
{
    mFile.load(file);
}

void UserDefaults::loadDefault (const std::string& file)
{
    mDefaultFile.load(file);
}

void UserDefaults::saveUser(const std::string& file)
{
    std::fstream fout(file.c_str(), std::ios::out);

    Ogre::ConfigFile::SectionIterator seci = mFile.getSectionIterator();

    while (seci.hasMoreElements())
    {
        Ogre::String sectionName = seci.peekNextKey();

        if (sectionName.length() > 0)
            fout << '\n' << '[' << seci.peekNextKey() << ']' << '\n';

        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            fout << i->first.c_str() << " = " << i->second.c_str() << '\n';
        }

        CategoryDefaultsValueMap::iterator it = mNewSettings.begin();
        while (it != mNewSettings.end())
        {
            if (it->first.first == sectionName)
            {
                fout << it->first.second << " = " << it->second << '\n';
                mNewSettings.erase(it++);
            }
            else
                ++it;
        }
    }

    std::string category = "";
    for (CategoryDefaultsValueMap::iterator it = mNewSettings.begin();
            it != mNewSettings.end(); ++it)
    {
        if (category != it->first.first)
        {
            category = it->first.first;
            fout << '\n' << '[' << category << ']' << '\n';
        }
        fout << it->first.second << " = " << it->second << '\n';
    }

    fout.close();
}

const std::string UserDefaults::getString (const std::string& setting, const std::string& category)
{
    if (mNewSettings.find(std::make_pair(category, setting)) != mNewSettings.end())
        return mNewSettings[std::make_pair(category, setting)];

    std::string defaultval = mDefaultFile.getSetting(setting, category, "NOTFOUND");
    std::string val = mFile.getSetting(setting, category, defaultval);

    if (val == "NOTFOUND")
        throw std::runtime_error("Trying to retrieve a non-existing setting: " + setting
                                 + " Make sure the userdefaults-default.cfg file was properly installed.");
    return val;
}

const float UserDefaults::getFloat (const std::string& setting, const std::string& category)
{
    return Ogre::StringConverter::parseReal( getString(setting, category) );
}

const int UserDefaults::getInt (const std::string& setting, const std::string& category)
{
    return Ogre::StringConverter::parseInt( getString(setting, category) );
}

const bool UserDefaults::getBool (const std::string& setting, const std::string& category)
{
    return Ogre::StringConverter::parseBool( getString(setting, category) );
}

void UserDefaults::setString (const std::string& setting, const std::string& category, const std::string& value)
{
    CategoryDefaults s = std::make_pair(category, setting);

    bool found=false;
    try
    {
        Ogre::ConfigFile::SettingsIterator it = mFile.getSettingsIterator(category);
        while (it.hasMoreElements())
        {
            Ogre::ConfigFile::SettingsMultiMap::iterator i = it.current();

            if ((*i).first == setting)
            {
                (*i).second = value;
                found = true;
            }

            it.getNext();
        }
    }
    catch (Ogre::Exception&)
    {}

    if (!found)
    {
        mNewSettings[s] = value;
    }
}

void UserDefaults::setInt (const std::string& setting, const std::string& category, const int value)
{
    setString(setting, category, Ogre::StringConverter::toString(value));
}

void UserDefaults::setFloat (const std::string& setting, const std::string& category, const float value)
{
    setString(setting, category, Ogre::StringConverter::toString(value));
}

void UserDefaults::setBool (const std::string& setting, const std::string& category, const bool value)
{
    setString(setting, category, Ogre::StringConverter::toString(value));
}

MyGUI::IntCoord UserDefaults::getMyGUICoord(const std::string &category)
{
    MyGUI::IntCoord coord;
    coord.left = getInt("left", category);
    coord.top = getInt("top", category);
    coord.width = getInt("width", category);
    coord.height = getInt("height", category);
    return coord;
}

void UserDefaults::setMyGUICoord(const std::string &category, const MyGUI::IntCoord &value)
{
    setInt("left", category, value.left);
    setInt("top", category, value.top);
    setInt("width", category, value.width);
    setInt("height", category, value.height);
}
