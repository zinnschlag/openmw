#include "dialogue.hpp"

#include <boost/lexical_cast.hpp>

#include "../mwbase/environment.hpp"
#include "../mwbase/windowmanager.hpp"
#include "../mwbase/mechanicsmanager.hpp"
#include "../mwbase/world.hpp"

#include "../mwmechanics/npcstats.hpp"

#include "../mwdialogue/dialoguemanagerimp.hpp"

#include "dialoguehistory.hpp"
#include "widgets.hpp"
#include "list.hpp"
#include "tradewindow.hpp"
#include "spellbuyingwindow.hpp"
#include "inventorywindow.hpp"
#include "travelwindow.hpp"

/**
*Copied from the internet.
*/

namespace
{

    std::string lower_string(const std::string& str)
    {
            std::string lowerCase = Misc::StringUtils::lowerCase (str);

            return lowerCase;
    }

    std::string::size_type find_str_ci(const std::string& str, const std::string& substr,size_t pos)
    {
        return lower_string(str).find(lower_string(substr),pos);
    }

    bool sortByLength (const std::string& left, const std::string& right)
    {
        return left.size() > right.size();
    }
}

namespace MWGui
{

    PersuasionDialog::PersuasionDialog()
        : WindowModal("openmw_persuasion_dialog.layout")
    {
        getWidget(mCancelButton, "CancelButton");
        getWidget(mAdmireButton, "AdmireButton");
        getWidget(mIntimidateButton, "IntimidateButton");
        getWidget(mTauntButton, "TauntButton");
        getWidget(mBribe10Button, "Bribe10Button");
        getWidget(mBribe100Button, "Bribe100Button");
        getWidget(mBribe1000Button, "Bribe1000Button");
        getWidget(mGoldLabel, "GoldLabel");

        mCancelButton->eventMouseButtonClick += MyGUI::newDelegate(this, &PersuasionDialog::onCancel);
        mAdmireButton->eventMouseButtonClick += MyGUI::newDelegate(this, &PersuasionDialog::onPersuade);
        mIntimidateButton->eventMouseButtonClick += MyGUI::newDelegate(this, &PersuasionDialog::onPersuade);
        mTauntButton->eventMouseButtonClick += MyGUI::newDelegate(this, &PersuasionDialog::onPersuade);
        mBribe10Button->eventMouseButtonClick += MyGUI::newDelegate(this, &PersuasionDialog::onPersuade);
        mBribe100Button->eventMouseButtonClick += MyGUI::newDelegate(this, &PersuasionDialog::onPersuade);
        mBribe1000Button->eventMouseButtonClick += MyGUI::newDelegate(this, &PersuasionDialog::onPersuade);
    }

    void PersuasionDialog::onCancel(MyGUI::Widget *sender)
    {
        setVisible(false);
    }

    void PersuasionDialog::onPersuade(MyGUI::Widget *sender)
    {
        MWBase::MechanicsManager::PersuasionType type;
        if (sender == mAdmireButton) type = MWBase::MechanicsManager::PT_Admire;
        else if (sender == mIntimidateButton) type = MWBase::MechanicsManager::PT_Intimidate;
        else if (sender == mTauntButton) type = MWBase::MechanicsManager::PT_Taunt;
        else if (sender == mBribe10Button)
        {
            MWBase::Environment::get().getWindowManager()->getTradeWindow()->addOrRemoveGold(-10);
            type = MWBase::MechanicsManager::PT_Bribe10;
        }
        else if (sender == mBribe100Button)
        {
            MWBase::Environment::get().getWindowManager()->getTradeWindow()->addOrRemoveGold(-100);
            type = MWBase::MechanicsManager::PT_Bribe100;
        }
        else /*if (sender == mBribe1000Button)*/
        {
            MWBase::Environment::get().getWindowManager()->getTradeWindow()->addOrRemoveGold(-1000);
            type = MWBase::MechanicsManager::PT_Bribe1000;
        }

        MWBase::Environment::get().getDialogueManager()->persuade(type);

        setVisible(false);
    }

    void PersuasionDialog::open()
    {
        WindowModal::open();
        center();

        int playerGold = MWBase::Environment::get().getWindowManager()->getInventoryWindow()->getPlayerGold();

        mBribe10Button->setEnabled (playerGold >= 10);
        mBribe100Button->setEnabled (playerGold >= 100);
        mBribe1000Button->setEnabled (playerGold >= 1000);

        mGoldLabel->setCaptionWithReplacing("#{sGold}: " + boost::lexical_cast<std::string>(playerGold));
    }

    // --------------------------------------------------------------------------------------------------

    DialogueWindow::DialogueWindow()
        : WindowBase("openmw_dialogue_window.layout")
        , mPersuasionDialog()
        , mEnabled(false)
        , mServices(0)
    {
        // Centre dialog
        center();

        mPersuasionDialog.setVisible(false);

        //History view
        getWidget(mHistory, "History");
        mHistory->setOverflowToTheLeft(true);
        mHistory->setMaxTextLength(1000000);
        MyGUI::Widget* eventbox;

        //An EditBox cannot receive mouse click events, so we use an
        //invisible widget on top of the editbox to receive them
        getWidget(eventbox, "EventBox");
        eventbox->eventMouseButtonClick += MyGUI::newDelegate(this, &DialogueWindow::onHistoryClicked);
        eventbox->eventMouseWheel += MyGUI::newDelegate(this, &DialogueWindow::onMouseWheel);

        //Topics list
        getWidget(mTopicsList, "TopicsList");
        mTopicsList->eventItemSelected += MyGUI::newDelegate(this, &DialogueWindow::onSelectTopic);

        MyGUI::Button* byeButton;
        getWidget(byeButton, "ByeButton");
        byeButton->eventMouseButtonClick += MyGUI::newDelegate(this, &DialogueWindow::onByeClicked);

        getWidget(mDispositionBar, "Disposition");
        getWidget(mDispositionText,"DispositionText");

        static_cast<MyGUI::Window*>(mMainWidget)->eventWindowChangeCoord += MyGUI::newDelegate(this, &DialogueWindow::onWindowResize);
    }

    void DialogueWindow::onHistoryClicked(MyGUI::Widget* _sender)
    {
        MyGUI::ISubWidgetText* t = mHistory->getClient()->getSubWidgetText();
        if(t == NULL)
            return;

        const MyGUI::IntPoint& lastPressed = MyGUI::InputManager::getInstance().getLastPressedPosition(MyGUI::MouseButton::Left);

        size_t cursorPosition = t->getCursorPosition(lastPressed);
        MyGUI::UString color = mHistory->getColorAtPos(cursorPosition);

        if (!mEnabled && color == "#572D21")
            MWBase::Environment::get().getDialogueManager()->goodbyeSelected();

        if (!mEnabled)
            return;

        if(color != "#B29154")
        {
            MyGUI::UString key = mHistory->getColorTextAt(cursorPosition);

            if(color == "#686EBA")
            {
                std::map<size_t, HyperLink>::iterator i = mHyperLinks.upper_bound(cursorPosition);
                if( !mHyperLinks.empty() )
                {
                    --i;

                    if( i->first + i->second.mLength > cursorPosition)
                    {
                        MWBase::Environment::get().getDialogueManager()->keywordSelected(i->second.mTrueValue);
                    }
                }
                else
                {
                    // the link was colored, but it is not in  mHyperLinks.
                    // It means that those liunks are not marked with @# and found
                    // by topic name search
                    MWBase::Environment::get().getDialogueManager()->keywordSelected(lower_string(key));
                }
            }

            if(color == "#572D21")
                MWBase::Environment::get().getDialogueManager()->questionAnswered(lower_string(key));
        }
    }

    void DialogueWindow::onWindowResize(MyGUI::Window* _sender)
    {
        mTopicsList->adjustSize();
    }

    void DialogueWindow::onMouseWheel(MyGUI::Widget* _sender, int _rel)
    {
        if (mHistory->getVScrollPosition() - _rel*0.3 < 0)
            mHistory->setVScrollPosition(0);
        else
            mHistory->setVScrollPosition(mHistory->getVScrollPosition() - _rel*0.3);
    }

    void DialogueWindow::onByeClicked(MyGUI::Widget* _sender)
    {
        MWBase::Environment::get().getDialogueManager()->goodbyeSelected();
    }

    void DialogueWindow::onSelectTopic(const std::string& topic, int id)
    {
        if (!mEnabled || MWBase::Environment::get().getDialogueManager()->isInChoice())
            return;

        int separatorPos = 0;
        for (unsigned int i=0; i<mTopicsList->getItemCount(); ++i)
        {
            if (mTopicsList->getItemNameAt(i) == "")
                separatorPos = i;
        }

        if (id >= separatorPos)
            MWBase::Environment::get().getDialogueManager()->keywordSelected(lower_string(topic));
        else
        {
            const MWWorld::Store<ESM::GameSetting> &gmst =
                MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>();

            if (topic == gmst.find("sPersuasion")->getString())
            {
                mPersuasionDialog.setVisible(true);
            }
            else if (topic == gmst.find("sCompanionShare")->getString())
            {
                MWBase::Environment::get().getWindowManager()->pushGuiMode(GM_Companion);
                MWBase::Environment::get().getWindowManager()->showCompanionWindow(mPtr);
            }
            else if (!MWBase::Environment::get().getDialogueManager()->checkServiceRefused())
            {
                if (topic == gmst.find("sBarter")->getString())
                {
                    MWBase::Environment::get().getWindowManager()->pushGuiMode(GM_Barter);
                    MWBase::Environment::get().getWindowManager()->getTradeWindow()->startTrade(mPtr);
                }
                else if (topic == gmst.find("sSpells")->getString())
                {
                    MWBase::Environment::get().getWindowManager()->pushGuiMode(GM_SpellBuying);
                    MWBase::Environment::get().getWindowManager()->getSpellBuyingWindow()->startSpellBuying(mPtr);
                }
                else if (topic == gmst.find("sTravel")->getString())
                {
                    MWBase::Environment::get().getWindowManager()->pushGuiMode(GM_Travel);
                    MWBase::Environment::get().getWindowManager()->getTravelWindow()->startTravel(mPtr);
                }
                else if (topic == gmst.find("sSpellMakingMenuTitle")->getString())
                {
                    MWBase::Environment::get().getWindowManager()->pushGuiMode(GM_SpellCreation);
                    MWBase::Environment::get().getWindowManager()->startSpellMaking (mPtr);
                }
                else if (topic == gmst.find("sEnchanting")->getString())
                {
                    MWBase::Environment::get().getWindowManager()->pushGuiMode(GM_Enchanting);
                    MWBase::Environment::get().getWindowManager()->startEnchanting (mPtr);
                }
                else if (topic == gmst.find("sServiceTrainingTitle")->getString())
                {
                    MWBase::Environment::get().getWindowManager()->pushGuiMode(GM_Training);
                    MWBase::Environment::get().getWindowManager()->startTraining (mPtr);
                }
                else if (topic == gmst.find("sRepair")->getString())
                {
                    MWBase::Environment::get().getWindowManager()->pushGuiMode(GM_MerchantRepair);
                    MWBase::Environment::get().getWindowManager()->startRepair (mPtr);
                }
            }
        }
    }

    void DialogueWindow::startDialogue(MWWorld::Ptr actor, std::string npcName)
    {
        mEnabled = true;
        mPtr = actor;
        mTopicsList->setEnabled(true);
        setTitle(npcName);

        mTopicsList->clear();
        mHyperLinks.clear();
        mHistory->setCaption("");
        updateOptions();
    }

    void DialogueWindow::setKeywords(std::list<std::string> keyWords)
    {
        mTopicsList->clear();

        bool isCompanion = !MWWorld::Class::get(mPtr).getScript(mPtr).empty()
                && mPtr.getRefData().getLocals().getIntVar(MWWorld::Class::get(mPtr).getScript(mPtr), "companion");

        bool anyService = mServices > 0 || isCompanion || mPtr.getTypeName() == typeid(ESM::NPC).name();

        const MWWorld::Store<ESM::GameSetting> &gmst =
            MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>();

        if (mPtr.getTypeName() == typeid(ESM::NPC).name())
            mTopicsList->addItem(gmst.find("sPersuasion")->getString());

        if (mServices & Service_Trade)
            mTopicsList->addItem(gmst.find("sBarter")->getString());

        if (mServices & Service_BuySpells)
            mTopicsList->addItem(gmst.find("sSpells")->getString());

        if (mServices & Service_Travel)
            mTopicsList->addItem(gmst.find("sTravel")->getString());

        if (mServices & Service_CreateSpells)
            mTopicsList->addItem(gmst.find("sSpellmakingMenuTitle")->getString());

        if (mServices & Service_Enchant)
            mTopicsList->addItem(gmst.find("sEnchanting")->getString());

        if (mServices & Service_Training)
            mTopicsList->addItem(gmst.find("sServiceTrainingTitle")->getString());

        if (mServices & Service_Repair)
            mTopicsList->addItem(gmst.find("sRepair")->getString());

        if (isCompanion)
            mTopicsList->addItem(gmst.find("sCompanionShare")->getString());

        if (anyService)
            mTopicsList->addSeparator();


        for(std::list<std::string>::iterator it = keyWords.begin(); it != keyWords.end(); ++it)
        {
            mTopicsList->addItem(*it);
        }
        mTopicsList->adjustSize();
    }

    void DialogueWindow::removeKeyword(std::string keyWord)
    {
        if(mTopicsList->hasItem(keyWord))
        {
            mTopicsList->removeItem(keyWord);
        }
        mTopicsList->adjustSize();
    }

    void addColorInString(std::string& str, const std::string& keyword,std::string color1, std::string color2)
    {
        size_t pos = 0;
        while((pos = find_str_ci(str,keyword, pos)) != std::string::npos)
        {
            // do not add color if this portion of text is already colored.
            {
                MyGUI::TextIterator iterator (str);
                MyGUI::UString colour;
                while(iterator.moveNext())
                {
                    size_t iteratorPos = iterator.getPosition();
                    iterator.getTagColour(colour);
                    if (iteratorPos == pos)
                        break;
                }

                if (colour == color1)
                    return;
            }

            str.insert(pos,color1);
            pos += color1.length();
            pos += keyword.length();
            str.insert(pos,color2);
            pos+= color2.length();
        }
    }

    std::string DialogueWindow::parseText(const std::string& text)
    {
        bool separatorReached = false; // only parse topics that are below the separator (this prevents actions like "Barter" that are not topics from getting blue-colored)

        std::vector<std::string> topics;

        bool hasSeparator = false;
        for (unsigned int i=0; i<mTopicsList->getItemCount(); ++i)
        {
            if (mTopicsList->getItemNameAt(i) == "")
                hasSeparator = true;
        }

        for(unsigned int i = 0;i<mTopicsList->getItemCount();i++)
        {
            std::string keyWord = mTopicsList->getItemNameAt(i);
            if (separatorReached || !hasSeparator)
                topics.push_back(keyWord);
            else if (keyWord == "")
                separatorReached = true;
        }

        // sort by length to make sure longer topics are replaced first
        std::sort(topics.begin(), topics.end(), sortByLength);

        std::vector<MWDialogue::HyperTextToken> hypertext = MWDialogue::ParseHyperText(text);

        size_t historySize = 0;
        if(mHistory->getClient()->getSubWidgetText() != NULL)
        {
            historySize = mHistory->getOnlyText().size();
        }

        std::string result;
        size_t hypertextPos = 0;
        for (size_t i = 0; i < hypertext.size(); ++i)
        {
            if (hypertext[i].mLink)
            {
                size_t asterisk_count = MWDialogue::RemovePseudoAsterisks(hypertext[i].mText);
                std::string standardForm = hypertext[i].mText;
                for(; asterisk_count > 0; --asterisk_count)
                    standardForm.append("*");

                standardForm =
                    MWBase::Environment::get().getWindowManager()->
                    getTranslationDataStorage().topicStandardForm(standardForm);

                if( std::find(topics.begin(), topics.end(), std::string(standardForm) ) != topics.end() )
                {
                    result.append("#686EBA").append(hypertext[i].mText).append("#B29154");

                    mHyperLinks[historySize+hypertextPos].mLength = MyGUI::UString(hypertext[i].mText).length();
                    mHyperLinks[historySize+hypertextPos].mTrueValue = lower_string(standardForm);
                }
                else
                    result += hypertext[i].mText;
            }
            else
            {
                if( !MWBase::Environment::get().getWindowManager()->getTranslationDataStorage().hasTranslation() )
                {
                    for(std::vector<std::string>::const_iterator it = topics.begin(); it != topics.end(); ++it)
                    {
                        addColorInString(hypertext[i].mText, *it, "#686EBA", "#B29154");
                    }
                }

                result += hypertext[i].mText;
            }

            hypertextPos += MyGUI::UString(hypertext[i].mText).length();
        }

        return result;
    }

    void DialogueWindow::addText(std::string text)
    {
        mHistory->addDialogText("#B29154"+parseText(text)+"#B29154");
    }

    void DialogueWindow::addMessageBox(const std::string& text)
    {
        mHistory->addDialogText("\n#FFFFFF"+text+"#B29154");
    }

    void DialogueWindow::addTitle(std::string text)
    {
        // This is called from the dialogue manager, so text is
        // case-smashed - thus we have to retrieve the correct case
        // of the text through the topic list.
        for (size_t i=0; i<mTopicsList->getItemCount(); ++i)
        {
            std::string item = mTopicsList->getItemNameAt(i);
            if (lower_string(item) == text)
                text = item;
        }

        mHistory->addDialogHeading(text);
    }

    void DialogueWindow::askQuestion(std::string question)
    {
        mHistory->addDialogText("#572D21"+question+"#B29154"+" ");
    }

    void DialogueWindow::updateOptions()
    {
        //Clear the list of topics
        mTopicsList->clear();
        mHyperLinks.clear();
        mHistory->eraseText(0, mHistory->getTextLength());

        if (mPtr.getTypeName() == typeid(ESM::NPC).name())
        {
            mDispositionBar->setProgressRange(100);
            mDispositionBar->setProgressPosition(MWBase::Environment::get().getMechanicsManager()->getDerivedDisposition(mPtr));
            mDispositionText->eraseText(0, mDispositionText->getTextLength());
            mDispositionText->addText("#B29154"+boost::lexical_cast<std::string>(MWBase::Environment::get().getMechanicsManager()->getDerivedDisposition(mPtr))+std::string("/100")+"#B29154");
        }
    }

    void DialogueWindow::goodbye()
    {
        mHistory->addDialogText("\n#572D21" + MWBase::Environment::get().getWorld()->getStore().get<ESM::GameSetting>().find("sGoodbye")->getString());
        mTopicsList->setEnabled(false);
        mEnabled = false;
    }

    void DialogueWindow::onReferenceUnavailable()
    {
        MWBase::Environment::get().getWindowManager()->removeGuiMode(GM_Dialogue);
    }

    void DialogueWindow::onFrame()
    {
        if(mMainWidget->getVisible() && mEnabled && mPtr.getTypeName() == typeid(ESM::NPC).name())
        {
            int disp = std::max(0, std::min(100,
                MWBase::Environment::get().getMechanicsManager()->getDerivedDisposition(mPtr)
                    + MWBase::Environment::get().getDialogueManager()->getTemporaryDispositionChange()));
            mDispositionBar->setProgressRange(100);
            mDispositionBar->setProgressPosition(disp);
            mDispositionText->eraseText(0, mDispositionText->getTextLength());
            mDispositionText->addText("#B29154"+boost::lexical_cast<std::string>(disp)+std::string("/100")+"#B29154");
        }
    }
}
