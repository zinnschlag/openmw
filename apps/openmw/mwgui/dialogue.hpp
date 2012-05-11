#ifndef MWGUI_DIALOGE_H
#define MWGUI_DIALOGE_H

#include "window_base.hpp"
#include <boost/array.hpp>

namespace MWGui
{
    class WindowManager;

    namespace Widgets
    {
        class MWList;
    }
}

/*
  This file contains the dialouge window
  Layout is defined by resources/mygui/openmw_dialogue_window_layout.xml.
 */

namespace MWGui
{
    class DialogueHistory;

    class DialogueWindow: public WindowBase
    {
    public:
        DialogueWindow(WindowManager& parWindowManager);

        void open();

        // Events
        typedef MyGUI::delegates::CMultiDelegate0 EventHandle_Void;

        /** Event : Dialog finished, OK button clicked.\n
            signature : void method()\n
        */
        EventHandle_Void eventBye;

        void startDialogue(std::string npcName);
        void stopDialogue();
        void setKeywords(std::list<std::string> keyWord);
        void removeKeyword(std::string keyWord);
        void addText(std::string text);
        void addTitle(std::string text);
        void askQuestion(std::string question);
        void goodbye();

    protected:
        void onSelectTopic(std::string topic);
        void onByeClicked(MyGUI::Widget* _sender);
        void onHistoryClicked(MyGUI::Widget* _sender);
        void onMouseWheel(MyGUI::Widget* _sender, int _rel);
        void onWindowResize(MyGUI::Window* _sender);

    private:
        void updateOptions();
        /**
        *Helper function that add topic keyword in blue in a text.
        */
        std::string parseText(std::string text);

        bool mEnabled;

        DialogueHistory*     history;
        Widgets::MWList*      topicsList;
        MyGUI::ProgressPtr pDispositionBar;
        MyGUI::EditPtr pDispositionText;
        std::map<std::string,std::string> pTopicsText;// this map links keyword and "real" text.
    };
}
#endif
