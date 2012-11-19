#include "formatting.hpp"

#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>

using namespace MWGui;

namespace
{
    unsigned int convertFromHex(const std::string& hex)
    {
        char* p = 0;
        unsigned long value = strtoul(hex.c_str(), &p, 16);
        if (*p != 0)
        {
            throw std::runtime_error("invalid character in hex number");
        }

        return value;
    }

    std::string removeEol(std::string& text)
    {
        struct bad_char
        {
            bool operator()(char ch)
            {
                return ch == '\r' || ch == '\n';
            }
        };
        std::string out;
        std::remove_copy_if(text.begin(), text.end(), std::back_inserter(out), bad_char());
        return out;
    }

    std::string::size_type removeLastSentence(std::string& text)
    {
        std::string::size_type removedTextSize = 0;
        std::string::size_type tagPos = std::string::npos;
        std::string::size_type pos = text.size() - 1;

        // Check if there is a br/div/img/font tag at the end of the string
        // and if found then remove whole tag
        while (text[pos] == '>')
        {
            std::string::size_type beginTagPos = text.rfind("<", pos);
            if (beginTagPos != std::string::npos)
            {
                pos = beginTagPos - 1;
            }
        }

        // Try to remove last sentence
        tagPos = text.rfind("<BR>", pos);
        if (tagPos != std::string::npos)
        {
            pos = tagPos;
        }

        removedTextSize = text.size() - pos;
        text.erase(pos);

        return removedTextSize;
    }
}

std::vector<std::string> BookTextParser::split(std::string text, int width, int height)
{
    text = removeEol(text);

    std::vector<std::string> result;

    const int spacing = 48;
    const int additionalSpace = 2;

    while (text.size() > 0)
    {
        // read in characters until we have exceeded the size, or run out of text
        int currentWidth = 0;
        int currentHeight = 0;
        std::string currentText;
        std::string currentWord;
        unsigned int i = 0;
        bool breakOnImg = false;

        while (currentHeight <= height - spacing && i < text.size())
        {
            if (text[i] == '<')
            {
                std::string::size_type closingTagPos = text.find('>', i);
                if (closingTagPos == std::string::npos)
                {
                    throw std::runtime_error("BookTextParser Error: Tag is not terminated");
                }
                std::string tag(text.substr(i, closingTagPos - i + 1));

                if (tag.size() == 4 && (tag.compare("<BR>") == 0 || tag.compare("<br>") == 0))
                {
                    currentHeight += mTextStyle.mTextSize + additionalSpace;
                    currentWidth = 0;
                    currentWord = "";
                    currentText += "<BR>";
                    i = closingTagPos;
                }
                else
                {
                    if (tag.size() > 4 && (tag.compare(0, 4, "<IMG") == 0 || tag.compare(0, 4, "<img") == 0))
                    {
                        // Place images on new book page, so they wouldn't
                        // be cut in the middle
                        int h = mHeight;
                        int w = mWidth;

                        parseImage(tag, false);
                        int imgHeight = mHeight - h;
                        mHeight = h;
                        mWidth = w; // Restore old width

                        if (currentHeight + imgHeight + spacing < height)
                        {
                            currentHeight += imgHeight + additionalSpace;

                        }
                        else
                        {
                            currentHeight = height;
                            breakOnImg = true;
                            continue;
                        }
                    }
                    else if (tag.size() > 5 && (tag.compare(0, 5, "<FONT") == 0 || tag.compare(0, 5, "<font") == 0))
                    {
                        parseFont(tag);
                    }
                    else if (tag.size() > 4 && (tag.compare(0, 4, "<DIV") == 0 || tag.compare(0, 4, "<div") == 0))
                    {
                        parseDiv(tag);
                    }

                    currentText += text.substr(i, closingTagPos - i + 1);
                    i = closingTagPos;
                }
            }
            else
            {
                currentWidth += MyGUI::FontManager::getInstance().getByName(mTextStyle.mFont == "Default"
                            ? "EB Garamond" : mTextStyle.mFont)
                            ->getGlyphInfo(static_cast<unsigned int>(text[i]))->width;
                currentText += text[i];

                if (text[i] == ' ')
                {
                    currentWord = "";
                }
                else
                {
                    currentWord += text[i];
                }
            }

            if (currentWidth > width)
            {
                currentHeight += mTextStyle.mTextSize + additionalSpace;
                currentWidth = 0;

                // add size of the current word
                unsigned int j = 0;
                while (j < currentWord.size())
                {
                    currentWidth +=
                        MyGUI::FontManager::getInstance().getByName (mTextStyle.mFont == "Default"
                            ? "EB Garamond" : mTextStyle.mFont)
                            ->getGlyphInfo(static_cast<unsigned int>(currentWord[j]))->width;
                    ++j;
                }
            }

            ++i;
        }

        if (!breakOnImg && currentHeight > height - spacing)
        {
            // remove the last sentence
            i -= removeLastSentence(currentText);
        }

        result.push_back(currentText);
        text.erase(0, currentText.size());
    }

    return result;
}

MyGUI::IntSize BookTextParser::parse(std::string text, MyGUI::Widget* parent, int width)
{
    mParent = parent;
    mWidth = width;
    mHeight = 0;

    assert(mParent);
    while (mParent->getChildCount())
    {
        MyGUI::Gui::getInstance().destroyWidget(mParent->getChildAt(0));
    }

    // remove trailing "
    if (text[text.size()-1] == '\"')
        text.erase(text.size()-1);

    parseSubText(text);
    return MyGUI::IntSize(mWidth, mHeight);
}

void BookTextParser::parseImage(const std::string& tag, bool createWidget)
{
    int src_start = tag.find("SRC=") + 5;
    std::string image = tag.substr(src_start, tag.find('"', src_start) - src_start);

    // fix texture extension to .dds
    if (image.size() > 4)
    {
        image[image.size() - 3] = 'd';
        image[image.size() - 2] = 'd';
        image[image.size() - 1] = 's';
    }

    int width_start = tag.find("WIDTH=") + 7;
    int width = boost::lexical_cast<int>(tag.substr(width_start, tag.find('"', width_start) - width_start));

    int height_start = tag.find("HEIGHT=") + 8;
    int height = boost::lexical_cast<int>(tag.substr(height_start, tag.find('"', height_start) - height_start));

    if (createWidget)
    {
        MyGUI::ImageBox* box = mParent->createWidget<MyGUI::ImageBox> ("ImageBox",
            MyGUI::IntCoord(0, mHeight, width, height), MyGUI::Align::Left | MyGUI::Align::Top,
            mParent->getName() + boost::lexical_cast<std::string>(mParent->getChildCount()));
        box->setImageTexture("bookart\\" + image);
        box->setProperty("NeedMouse", "false");
    }

    mWidth = std::max(mWidth, width);
    mHeight += height;
}

void BookTextParser::parseDiv(const std::string& tag)
{
    std::string::size_type pos = tag.find("ALIGN=");
    if (pos == std::string::npos)
        return;

    int align_start = pos + 7;
    std::string align = tag.substr(align_start, tag.find('"', align_start) - align_start);
    if (align == "CENTER")
        mTextStyle.mTextAlign = MyGUI::Align::HCenter;
    else if (align == "LEFT")
        mTextStyle.mTextAlign = MyGUI::Align::Left;
}

void BookTextParser::parseFont(const std::string& tag)
{
    std::string::size_type pos = tag.find("COLOR="); 
    if (pos != std::string::npos)
    {
        int color_start = pos + 7;
        std::string color = tag.substr(color_start, tag.find('"', color_start) - color_start);

        mTextStyle.mColour = MyGUI::Colour(
            convertFromHex(color.substr(0, 2)) / 255.0,
            convertFromHex(color.substr(2, 2)) / 255.0,
            convertFromHex(color.substr(4, 2)) / 255.0);
    }

    pos = tag.find("FACE=");
    if (pos != std::string::npos)
    {
        int face_start = pos + 6;
        std::string face = tag.substr(face_start, tag.find('"', face_start) - face_start);

        if (face != "Magic Cards")
            mTextStyle.mFont = face;
    }

    pos = tag.find("SIZE=");
    if (pos != std::string::npos)
    {
        int size_start = pos + 6;
        mTextStyle.mTextSize = boost::lexical_cast<int>(tag.substr(size_start, tag.find('"', size_start) - size_start));

        /**
         * \todo In what units is MW font size?!
         * Temporary "hack": size = mw font size * 5
         */
        mTextStyle.mTextSize *= 5;
    }
}

void BookTextParser::parseSubText(std::string text)
{
    if (text[0] == '<')
    {
        std::string::size_type closingTagPos = text.find('>');
        if (closingTagPos == std::string::npos)
        {
            throw std::runtime_error("BookTextParser Error: Tag is not terminated, text: " + text);
        }

        if (text.compare(0, 4, "<IMG") == 0)
            parseImage(text.substr(0, closingTagPos));
        else if (text.compare(0, 5, "<FONT") == 0)
            parseFont(text.substr(0, closingTagPos));
        else if (text.compare(0, 4, "<DIV") == 0)
            parseDiv(text.substr(0, closingTagPos));

        text.erase(0, closingTagPos + 1);
    }

    boost::algorithm::replace_all(text, "<BR>", "\n");
    boost::algorithm::replace_all(text, "<P>", "\n\n");

    bool tagFound = false;
    std::string realText; // real text, without tags
    unsigned int i = 0;
    for (; i < text.size(); ++i)
    {
        char c = text[i];
        if (c == '<')
        {
            if (text[i + 1] == '/') // ignore closing tags
            {
                while (c != '>')
                {
                    if (i >= text.size())
                        throw std::runtime_error("BookTextParser Error: Tag is not terminated");
                    ++i;
                    c = text[i];
                }
                continue;
            }
            else
            {
                tagFound = true;
                break;
            }
        }
        else
            realText += c;
    }

    MyGUI::EditBox* box = mParent->createWidget<MyGUI::EditBox>("NormalText",
        MyGUI::IntCoord(0, mHeight, mWidth, 24), MyGUI::Align::Left | MyGUI::Align::Top,
        mParent->getName() + boost::lexical_cast<std::string>(mParent->getChildCount()));
    box->setProperty("Static", "true");
    box->setProperty("MultiLine", "true");
    box->setProperty("WordWrap", "true");
    box->setProperty("NeedMouse", "false");
    box->setMaxTextLength(realText.size());
    box->setTextAlign(mTextStyle.mTextAlign);
    box->setTextColour(mTextStyle.mColour);
    box->setFontName(mTextStyle.mFont);
    box->setCaption(realText);
    box->setSize(box->getSize().width, box->getTextSize().height);
    mHeight += box->getTextSize().height;

    if (tagFound)
    {
        parseSubText(text.substr(i, text.size()));
    }
}
