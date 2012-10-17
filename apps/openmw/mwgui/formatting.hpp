#ifndef MWGUI_FORMATTING_H
#define MWGUI_FORMATTING_H

#include <MyGUI.h>

namespace MWGui
{
    struct TextStyle
    {
        TextStyle() :
            mColour(0,0,0)
            , mFont("Default")
            , mTextSize(16)
            , mTextAlign(MyGUI::Align::Left | MyGUI::Align::Top)
        {
        }

        MyGUI::Colour mColour;
        std::string mFont;
        int mTextSize;
        MyGUI::Align mTextAlign;
    };

    /// \brief utilities for parsing book/scroll text as mygui widgets
    class BookTextParser
    {
        public:
            /**
             * Parse markup as MyGUI widgets
             * @param markup to parse
             * @param parent for the created widgets
             * @param maximum width
             * @return size of the created widgets
             */
            MyGUI::IntSize parse(std::string text, MyGUI::Widget* parent, int width);

            /**
             * Split the specified text into pieces that fit in the area specified by width and height parameters
             */
            std::vector<std::string> split(std::string text, int width, int height);

        protected:
            void parseSubText(std::string text);

            void parseImage(const std::string& tag, bool createWidget=true);
            void parseDiv(const std::string& tag);
            void parseFont(const std::string& tag);
        private:
            MyGUI::Widget* mParent;
            int mWidth; // maximum width
            int mHeight; // current height
            TextStyle mTextStyle;
    };
}

#endif
