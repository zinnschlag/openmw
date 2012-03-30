#include "window_base.hpp"
#include "window_manager.hpp"

using namespace MWGui;

WindowBase::WindowBase(const std::string& parLayout, WindowManager& parWindowManager)
  : Layout(parLayout)
  , mWindowManager(parWindowManager)
{
}

void WindowBase::open()
{
}

void WindowBase::center()
{
    // Centre dialog
    MyGUI::IntSize gameWindowSize = MyGUI::RenderManager::getInstance().getViewSize();
    MyGUI::IntCoord coord = mMainWidget->getCoord();
    coord.left = (gameWindowSize.width - coord.width)/2;
    coord.top = (gameWindowSize.height - coord.height)/2;
    mMainWidget->setCoord(coord);
}

void WindowBase::center_low()
{
    // Centre dialog
    MyGUI::IntSize gameWindowSize = MyGUI::RenderManager::getInstance().getViewSize();
    MyGUI::IntCoord coord = mMainWidget->getCoord();
    coord.left = (gameWindowSize.width - coord.width)/2;
    // lower the dialog a bit, it isn't exactly centered in the screen in vanilla
    coord.top = ((gameWindowSize.height - coord.height)/2) + 83;
    mMainWidget->setCoord(coord);
}
