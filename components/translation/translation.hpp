/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPONENTS_TRANSLATION_DATA_H
#define COMPONENTS_TRANSLATION_DATA_H

#include <components/to_utf8/to_utf8.hpp>
#include <components/files/collections.hpp>

namespace Translation
{
    class Storage
    {
    public:

        void loadTranslationData(const Files::Collections& dataFileCollections,
                                 const std::string& esmFileName);

        std::string translateCellName(const std::string& cellName) const;
        std::string topicID(const std::string& phrase) const;

        // Standard form usually means nominative case
        std::string topicStandardForm(const std::string& phrase) const;

        void setEncoder(ToUTF8::Utf8Encoder* encoder);

        bool hasTranslation() const;

    private:
        typedef std::map<std::string, std::string> ContainerType;

        void loadData(ContainerType& container,
                      const std::string& fileNameNoExtension,
                      const std::string& extension,
                      const Files::Collections& dataFileCollections);

        void loadDataFromStream(ContainerType& container, std::istream& stream);


        ToUTF8::Utf8Encoder* mEncoder;
        ContainerType mCellNamesTranslations, mTopicIDs, mPhraseForms;
    };
}

#endif
