#ifndef CSV_WORLD_TABLESUBVIEW_H
#define CSV_WORLD_TABLESUBVIEW_H

#include "../doc/subview.hpp"
#include "../filter/filterbox.hpp"

#include <QtCore/qnamespace.h>

class QModelIndex;

namespace CSMWorld
{
    class IdTable;
}

namespace CSMDoc
{
    class Document;
}

namespace CSVWorld
{
    class Table;
    class TableBottomBox;
    class CreatorFactoryBase;

    class TableSubView : public CSVDoc::SubView
    {
            Q_OBJECT

            Table *mTable;
            TableBottomBox *mBottom;
            CSVFilter::FilterBox* mFilterBox;

        public:

            TableSubView (const CSMWorld::UniversalId& id, CSMDoc::Document& document,
                const CreatorFactoryBase& creatorFactory, bool sorting);

            virtual void setEditLock (bool locked);

            virtual void updateEditorSetting (const QString& key, const QString& value);

            virtual void setStatusBar (bool show);

        protected:
            bool eventFilter(QObject* object, QEvent *event);

        signals:
            void cloneRequest(const std::string&,
                              const CSMWorld::UniversalId::Type);

        private slots:

            void editRequest (const CSMWorld::UniversalId& id, const std::string& hint);
            void cloneRequest (const CSMWorld::UniversalId& toClone);
            void createFilterRequest(std::vector< CSMWorld::UniversalId >& types,
                                     Qt::DropAction action);
    };
}

#endif
