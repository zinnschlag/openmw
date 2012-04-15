#include "stats_window.hpp"

#include "../mwmechanics/mechanicsmanager.hpp"
#include "window_manager.hpp"

#include <cmath>
#include <algorithm>
#include <iterator>
#include <boost/lexical_cast.hpp>

using namespace MWGui;
const int StatsWindow::lineHeight = 18;

StatsWindow::StatsWindow (WindowManager& parWindowManager)
  : WindowPinnableBase("openmw_stats_window_layout.xml", parWindowManager)
  , skillAreaWidget(NULL)
  , skillClientWidget(NULL)
  , skillScrollerWidget(NULL)
  , lastPos(0)
  , clientHeight(0)
  , majorSkills()
  , minorSkills()
  , miscSkills()
  , skillValues()
  , skillWidgetMap()
  , factionWidgetMap()
  , factions()
  , birthSignId()
  , reputation(0)
  , bounty(0)
  , skillWidgets()
{
    setCoord(0,0,498, 342);

    const char *names[][2] =
    {
        { "Attrib1", "sAttributeStrength" },
        { "Attrib2", "sAttributeIntelligence" },
        { "Attrib3", "sAttributeWillpower" },
        { "Attrib4", "sAttributeAgility" },
        { "Attrib5", "sAttributeSpeed" },
        { "Attrib6", "sAttributeEndurance" },
        { "Attrib7", "sAttributePersonality" },
        { "Attrib8", "sAttributeLuck" },
        { "Health_str", "sHealth" },
        { "Magicka_str", "sMagic" },
        { "Fatigue_str", "sFatigue" },
        { "Level_str", "sLevel" },
        { "Race_str", "sRace" },
        { "Class_str", "sClass" },
        { 0, 0 }
    };

    const ESMS::ESMStore &store = mWindowManager.getStore();
    for (int i=0; names[i][0]; ++i)
    {
        setText (names[i][0], store.gameSettings.find (names[i][1])->str);
    }

    getWidget(skillAreaWidget, "Skills");
    getWidget(skillClientWidget, "SkillClient");
    getWidget(skillScrollerWidget, "SkillScroller");

    skillScrollerWidget->eventScrollChangePosition += MyGUI::newDelegate(this, &StatsWindow::onScrollChangePosition);
    updateScroller();

    for (int i = 0; i < ESM::Skill::Length; ++i)
    {
        skillValues.insert(std::pair<int, MWMechanics::Stat<float> >(i, MWMechanics::Stat<float>()));
        skillWidgetMap.insert(std::pair<int, MyGUI::TextBox*>(i, nullptr));
    }

    MyGUI::WindowPtr t = static_cast<MyGUI::WindowPtr>(mMainWidget);
    t->eventWindowChangeCoord += MyGUI::newDelegate(this, &StatsWindow::onWindowResize);
}

void StatsWindow::onScrollChangePosition(MyGUI::ScrollBar* scroller, size_t pos)
{
    int diff = lastPos - pos;
    // Adjust position of all widget according to difference
    if (diff == 0)
        return;
    lastPos = pos;

    std::vector<MyGUI::WidgetPtr>::const_iterator end = skillWidgets.end();
    for (std::vector<MyGUI::WidgetPtr>::const_iterator it = skillWidgets.begin(); it != end; ++it)
    {
        (*it)->setCoord((*it)->getCoord() + MyGUI::IntPoint(0, diff));
    }
}

void StatsWindow::onWindowResize(MyGUI::Window* window)
{
    updateScroller();
}

void StatsWindow::setBar(const std::string& name, const std::string& tname, int val, int max)
{
    MyGUI::ProgressPtr pt;
    getWidget(pt, name);
    pt->setProgressRange(max);
    pt->setProgressPosition(val);

    std::stringstream out;
    out << val << "/" << max;
    setText(tname, out.str().c_str());
}

void StatsWindow::setPlayerName(const std::string& playerName)
{
    static_cast<MyGUI::Window*>(mMainWidget)->setCaption(playerName);
}

void StatsWindow::setStyledText(MyGUI::TextBox* widget, ColorStyle style, const std::string &value)
{
    widget->setCaption(value);
    if (style == CS_Super)
        widget->setTextColour(MyGUI::Colour(0, 1, 0));
    else if (style == CS_Sub)
        widget->setTextColour(MyGUI::Colour(1, 0, 0));
    else
        widget->setTextColour(MyGUI::Colour(1, 1, 1));
}

void StatsWindow::setValue (const std::string& id, const MWMechanics::Stat<int>& value)
{
    static const char *ids[] =
    {
        "AttribVal1", "AttribVal2", "AttribVal3", "AttribVal4", "AttribVal5",
        "AttribVal6", "AttribVal7", "AttribVal8",
        0
    };

    for (int i=0; ids[i]; ++i)
        if (ids[i]==id)
        {
            std::ostringstream valueString;
            valueString << value.getModified();
            setText (id, valueString.str());

            if (value.getModified()>value.getBase())
                setTextColor (id, 0, 1, 0);
            else if (value.getModified()<value.getBase())
                setTextColor (id, 1, 0, 0);
            else
                setTextColor (id, 1, 1, 1);

            break;
        }
}

void StatsWindow::setValue (const std::string& id, const MWMechanics::DynamicStat<int>& value)
{
    static const char *ids[] =
    {
        "HBar", "MBar", "FBar",
        0
    };

    for (int i=0; ids[i]; ++i)
        if (ids[i]==id)
        {
            std::string id (ids[i]);
            setBar (id, id + "T", value.getCurrent(), value.getModified());
        }
}

void StatsWindow::setValue (const std::string& id, const std::string& value)
{
    if (id=="name")
        setPlayerName (value);
    else if (id=="race")
        setText ("RaceText", value);
    else if (id=="class")
        setText ("ClassText", value);
}

void StatsWindow::setValue (const std::string& id, int value)
{
    if (id=="level")
    {
        std::ostringstream text;
        text << value;
        setText("LevelText", text.str());
    }
}

void StatsWindow::setValue(const ESM::Skill::SkillEnum parSkill, const MWMechanics::Stat<float>& value)
{
    skillValues[parSkill] = value;
    MyGUI::TextBox* widget = skillWidgetMap[(int)parSkill];
    if (widget)
    {
        float modified = value.getModified(), base = value.getBase();
        std::string text = boost::lexical_cast<std::string>(std::floor(modified));
        ColorStyle style = CS_Normal;
        if (modified > base)
            style = CS_Super;
        else if (modified < base)
            style = CS_Sub;

        setStyledText(widget, style, text);
    }
}

void StatsWindow::configureSkills (const std::vector<int>& major, const std::vector<int>& minor)
{
    majorSkills = major;
    minorSkills = minor;

    // Update misc skills with the remaining skills not in major or minor
    std::set<int> skillSet;
    std::copy(major.begin(), major.end(), std::inserter(skillSet, skillSet.begin()));
    std::copy(minor.begin(), minor.end(), std::inserter(skillSet, skillSet.begin()));
    boost::array<ESM::Skill::SkillEnum, ESM::Skill::Length>::const_iterator end = ESM::Skill::skillIds.end();
    miscSkills.clear();
    for (boost::array<ESM::Skill::SkillEnum, ESM::Skill::Length>::const_iterator it = ESM::Skill::skillIds.begin(); it != end; ++it)
    {
        int skill = *it;
        if (skillSet.find(skill) == skillSet.end())
            miscSkills.push_back(skill);
    }
}

void StatsWindow::setFactions (const std::vector<Faction>& factions)
{
    this->factions = factions;
}

void StatsWindow::setBirthSign (const std::string& signId)
{
    birthSignId = signId;
}

void StatsWindow::addSeparator(MyGUI::IntCoord &coord1, MyGUI::IntCoord &coord2)
{
    MyGUI::ImageBox* separator = skillClientWidget->createWidget<MyGUI::ImageBox>("MW_HLine", MyGUI::IntCoord(10, coord1.top, coord1.width + coord2.width - 4, 18), MyGUI::Align::Default);
    skillWidgets.push_back(separator);

    coord1.top += separator->getHeight();
    coord2.top += separator->getHeight();
}

void StatsWindow::addGroup(const std::string &label, MyGUI::IntCoord &coord1, MyGUI::IntCoord &coord2)
{
    MyGUI::TextBox* groupWidget = skillClientWidget->createWidget<MyGUI::TextBox>("SandBrightText", MyGUI::IntCoord(0, coord1.top, coord1.width + coord2.width, coord1.height), MyGUI::Align::Default);
    groupWidget->setCaption(label);
    skillWidgets.push_back(groupWidget);

    coord1.top += lineHeight;
    coord2.top += lineHeight;
}

MyGUI::TextBox* StatsWindow::addValueItem(const std::string& text, const std::string& tooltip, const std::string &value, ColorStyle style, MyGUI::IntCoord &coord1, MyGUI::IntCoord &coord2)
{
    MyGUI::TextBox *skillNameWidget, *skillValueWidget;

    skillNameWidget = skillClientWidget->createWidget<MyGUI::TextBox>("SandText", coord1, MyGUI::Align::Default);
    skillNameWidget->setCaption(text);
    skillNameWidget->setUserString("ToolTipType", "Text");
    skillNameWidget->setUserString("ToolTipText", tooltip);

    skillValueWidget = skillClientWidget->createWidget<MyGUI::TextBox>("SandTextRight", coord2, MyGUI::Align::Default);
    skillValueWidget->setUserString("ToolTipType", "Text");
    skillValueWidget->setUserString("ToolTipText", tooltip);
    setStyledText(skillValueWidget, style, value);

    skillWidgets.push_back(skillNameWidget);
    skillWidgets.push_back(skillValueWidget);

    coord1.top += lineHeight;
    coord2.top += lineHeight;

    return skillValueWidget;
}

void StatsWindow::addItem(const std::string text, MyGUI::IntCoord &coord1, MyGUI::IntCoord &coord2)
{
    MyGUI::TextBox* skillNameWidget;

    skillNameWidget = skillClientWidget->createWidget<MyGUI::TextBox>("SandText", coord1 + MyGUI::IntSize(coord2.width, 0), MyGUI::Align::Default);
    skillNameWidget->setCaption(text);

    skillWidgets.push_back(skillNameWidget);

    coord1.top += lineHeight;
    coord2.top += lineHeight;
}

void StatsWindow::addSkills(const SkillList &skills, const std::string &titleId, const std::string &titleDefault, MyGUI::IntCoord &coord1, MyGUI::IntCoord &coord2)
{
    // Add a line separator if there are items above
    if (!skillWidgets.empty())
    {
        addSeparator(coord1, coord2);
    }

    addGroup(mWindowManager.getGameSettingString(titleId, titleDefault), coord1, coord2);

    SkillList::const_iterator end = skills.end();
    for (SkillList::const_iterator it = skills.begin(); it != end; ++it)
    {
        int skillId = *it;
        if (skillId < 0 || skillId > ESM::Skill::Length) // Skip unknown skill indexes
            continue;
        assert(skillId >= 0 && skillId < ESM::Skill::Length);
        const std::string &skillNameId = ESMS::Skill::sSkillNameIds[skillId];
        const MWMechanics::Stat<float> &stat = skillValues.find(skillId)->second;
        float base = stat.getBase();
        float modified = stat.getModified();

        ColorStyle style = CS_Normal;
        if (modified > base)
            style = CS_Super;
        else if (modified < base)
            style = CS_Sub;
        MyGUI::TextBox* widget = addValueItem(mWindowManager.getGameSettingString(skillNameId, skillNameId), "", boost::lexical_cast<std::string>(static_cast<int>(modified)), style, coord1, coord2);
        skillWidgetMap[skillId] = widget;
    }
}

void StatsWindow::updateSkillArea()
{
    for (std::vector<MyGUI::WidgetPtr>::iterator it = skillWidgets.begin(); it != skillWidgets.end(); ++it)
    {
        MyGUI::Gui::getInstance().destroyWidget(*it);
    }
    skillWidgets.clear();

    const int valueSize = 40;
    MyGUI::IntCoord coord1(10, 0, skillClientWidget->getWidth() - (10 + valueSize), 18);
    MyGUI::IntCoord coord2(coord1.left + coord1.width, coord1.top, valueSize, coord1.height);

    if (!majorSkills.empty())
        addSkills(majorSkills, "sSkillClassMajor", "Major Skills", coord1, coord2);

    if (!minorSkills.empty())
        addSkills(minorSkills, "sSkillClassMinor", "Minor Skills", coord1, coord2);

    if (!miscSkills.empty())
        addSkills(miscSkills, "sSkillClassMisc", "Misc Skills", coord1, coord2);

    const ESMS::ESMStore &store = mWindowManager.getStore();

    if (!factions.empty())
    {
        // Add a line separator if there are items above
        if (!skillWidgets.empty())
            addSeparator(coord1, coord2);

        addGroup(mWindowManager.getGameSettingString("sFaction", "Faction"), coord1, coord2);
        FactionList::const_iterator end = factions.end();
        for (FactionList::const_iterator it = factions.begin(); it != end; ++it)
        {
            const ESM::Faction *faction = store.factions.find(it->first);
            addItem(faction->name, coord1, coord2);
            // TODO: Faction rank should be placed in tooltip
        }
    }

    if (!birthSignId.empty())
    {
        // Add a line separator if there are items above
        if (!skillWidgets.empty())
            addSeparator(coord1, coord2);

        addGroup(mWindowManager.getGameSettingString("sSign", "Sign"), coord1, coord2);
        const ESM::BirthSign *sign = store.birthSigns.find(birthSignId);
        addItem(sign->name, coord1, coord2);
    }

    // Add a line separator if there are items above
    if (!skillWidgets.empty())
        addSeparator(coord1, coord2);

    addValueItem(mWindowManager.getGameSettingString("sReputation", "Reputation"),
                mWindowManager.getGameSettingString("sSkillsMenuReputationHelp", ""),
                boost::lexical_cast<std::string>(static_cast<int>(reputation)), CS_Normal, coord1, coord2);
    addValueItem(mWindowManager.getGameSettingString("sBounty", "Bounty"),
                mWindowManager.getGameSettingString("sCrimeHelp", ""),
                boost::lexical_cast<std::string>(static_cast<int>(bounty)), CS_Normal, coord1, coord2);

    clientHeight = coord1.top;
    updateScroller();
}

void StatsWindow::updateScroller()
{
    skillScrollerWidget->setScrollRange(std::max(clientHeight - skillClientWidget->getHeight(), 0));
    skillScrollerWidget->setScrollPage(std::max(skillClientWidget->getHeight() - lineHeight, 0));
}

void StatsWindow::onPinToggled()
{
    mWindowManager.setHMSVisibility(!mPinned);
}
