#ifndef COMPONENTS_TRANSLATION_DATA_H
#define COMPONENTS_TRANSLATION_DATA_H

#include <components/to_utf8/to_utf8.hpp>
#include <components/files/collections.hpp>

namespace TranslationData
{
    class Storage
    {
    public:
        Storage(const ToUTF8::FromType& encoding) : mEncoding(encoding) {}

        void loadTranslationData(const Files::Collections& dataFileCollections,
                                 const std::string& esmFileName);

        std::string translateCellName(const std::string& cellName) const;
        std::string topicID(const std::string& phrase) const;

    private:
        typedef std::map<std::string, std::string> ContainerType;

        void loadData(ContainerType& container,
                      const std::string& fileNameNoExtension,
                      const std::string& extension,
                      const Files::Collections& dataFileCollections);

        void loadDataFromStream(ContainerType& container, std::istream& stream);


        ToUTF8::FromType mEncoding;
        std::map<std::string, std::string> mCellNamesTranslations, mTopicIDs, mPhraseForms;
    };
}

#endif
