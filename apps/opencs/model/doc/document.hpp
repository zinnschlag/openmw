#ifndef CSM_DOC_DOCUMENT_H
#define CSM_DOC_DOCUMENT_H

#include <string>

#include <boost/filesystem/path.hpp>

#include <QUndoStack>
#include <QObject>
#include <QTimer>

#include <components/to_utf8/to_utf8.hpp>

#include "../world/data.hpp"

#include "../tools/tools.hpp"

#include "state.hpp"
#include "saving.hpp"

class QAbstractItemModel;

namespace ESM
{
    struct GameSetting;
    struct Global;
}

namespace Files
{
    class ConfigurationManager;
}

namespace CSMDoc
{
    class Document : public QObject
    {
            Q_OBJECT

        private:

            boost::filesystem::path mSavePath;
            std::vector<boost::filesystem::path> mContentFiles;
            bool mNew;
            CSMWorld::Data mData;
            CSMTools::Tools mTools;
            boost::filesystem::path mProjectPath;
            Saving mSaving;
            boost::filesystem::path mResDir;

            // It is important that the undo stack is declared last, because on desctruction it fires a signal, that is connected to a slot, that is
            // using other member variables.  Unfortunately this connection is cut only in the QObject destructor, which is way too late.
            QUndoStack mUndoStack;

            // not implemented
            Document (const Document&);
            Document& operator= (const Document&);

            void createBase();

            void addGmsts();

            void addOptionalGmsts();

            void addOptionalGlobals();

            void addOptionalGmst (const ESM::GameSetting& gmst);

            void addOptionalGlobal (const ESM::Global& global);

        public:

            Document (const Files::ConfigurationManager& configuration,
                const std::vector< boost::filesystem::path >& files, bool new_,
                const boost::filesystem::path& savePath, const boost::filesystem::path& resDir,
                ToUTF8::FromType encoding);

            ~Document();

            QUndoStack& getUndoStack();

            int getState() const;

            const boost::filesystem::path& getSavePath() const;

            const boost::filesystem::path& getProjectPath() const;

            const std::vector<boost::filesystem::path>& getContentFiles() const;
            ///< \attention The last element in this collection is the file that is being edited,
            /// but with its original path instead of the save path.

            bool isNew() const;
            ///< Is this a newly created content file?

            void save();

            CSMWorld::UniversalId verify();

            void abortOperation (int type);

            const CSMWorld::Data& getData() const;

            CSMWorld::Data& getData();

            CSMTools::ReportModel *getReport (const CSMWorld::UniversalId& id);
            ///< The ownership of the returned report is not transferred.

        signals:

            void stateChanged (int state, CSMDoc::Document *document);

            void progress (int current, int max, int type, int threads, CSMDoc::Document *document);

        private slots:

            void modificationStateChanged (bool clean);

            void reportMessage (const CSMWorld::UniversalId& id, const std::string& message,
                int type);

            void operationDone (int type);

        public slots:

            void progress (int current, int max, int type);
    };
}

#endif

