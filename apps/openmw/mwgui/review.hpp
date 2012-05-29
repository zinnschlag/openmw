#ifndef MWGUI_REVIEW_H
#define MWGUI_REVIEW_H

#include "window_base.hpp"
#include "../mwmechanics/stat.hpp"
#include "widgets.hpp"

namespace MWGui
{
    class WindowManager;
}

/*
This file contains the dialog for reviewing the generated character.
Layout is defined by resources/mygui/openmw_chargen_review_layout.xml.
*/

namespace MWGui
{
    using namespace MyGUI;

    class ReviewDialog : public WindowBase
    {
    public:
        enum Dialogs {
            NAME_DIALOG,
            RACE_DIALOG,
            CLASS_DIALOG,
            BIRTHSIGN_DIALOG
        };
        typedef std::vector<int> SkillList;

        ReviewDialog(WindowManager& parWindowManager);

        void setPlayerName(const std::string &name);
        void setRace(const std::string &raceId);
        void setClass(const ESM::Class& class_);
        void setBirthSign (const std::string &signId);

        void setHealth(const MWMechanics::DynamicStat<int>& value);
        void setMagicka(const MWMechanics::DynamicStat<int>& value);
        void setFatigue(const MWMechanics::DynamicStat<int>& value);

        void setAttribute(ESM::Attribute::AttributeID attributeId, const MWMechanics::Stat<int>& value);

        void configureSkills(const SkillList& major, const SkillList& minor);
        void setSkillValue(ESM::Skill::SkillEnum skillId, const MWMechanics::Stat<float>& value);

        void open();

        // Events
        typedef delegates::CMultiDelegate0 EventHandle_Void;
        typedef delegates::CMultiDelegate1<int> EventHandle_Int;

        /** Event : Back button clicked.\n
        signature : void method()\n
        */
        EventHandle_Void eventBack;

        EventHandle_Int eventActivateDialog;

    protected:
        void onOkClicked(MyGUI::Widget* _sender);
        void onBackClicked(MyGUI::Widget* _sender);

        void onNameClicked(MyGUI::Widget* _sender);
        void onRaceClicked(MyGUI::Widget* _sender);
        void onClassClicked(MyGUI::Widget* _sender);
        void onBirthSignClicked(MyGUI::Widget* _sender);

        void onMouseWheel(MyGUI::Widget* _sender, int _rel);

    private:
        void addSkills(const SkillList &skills, const std::string &titleId, const std::string &titleDefault, MyGUI::IntCoord &coord1, MyGUI::IntCoord &coord2);
        void addSeparator(MyGUI::IntCoord &coord1, MyGUI::IntCoord &coord2);
        void addGroup(const std::string &label, MyGUI::IntCoord &coord1, MyGUI::IntCoord &coord2);
        MyGUI::TextBox* addValueItem(const std::string text, const std::string &value, const std::string& state, MyGUI::IntCoord &coord1, MyGUI::IntCoord &coord2);
        void addItem(const std::string text, MyGUI::IntCoord &coord1, MyGUI::IntCoord &coord2);
        void updateScroller();
        void updateSkillArea();

        void onScrollChangePosition(MyGUI::ScrollBar* scroller, size_t pos);
        void onWindowResize(MyGUI::Window* window);

        static const int lineHeight;

        MyGUI::TextBox *nameWidget, *raceWidget, *classWidget, *birthSignWidget;
        MyGUI::WidgetPtr skillAreaWidget, skillClientWidget;
        MyGUI::ScrollBar* skillScrollerWidget;
        int lastPos, clientHeight;

        Widgets::MWDynamicStatPtr health, magicka, fatigue;

        std::map<int, Widgets::MWAttributePtr> attributeWidgets;

        SkillList majorSkills, minorSkills, miscSkills;
        std::map<int, MWMechanics::Stat<float> > skillValues;
        std::map<int, MyGUI::TextBox*> skillWidgetMap;
        std::string name, raceId, birthSignId;
        ESM::Class klass;
        std::vector<MyGUI::WidgetPtr> skillWidgets; //< Skills and other information
    };
}
#endif
