#ifndef CSV_FILTER_RECORDFILTERBOX_H
#define CSV_FILTER_RECORDFILTERBOX_H

#include <boost/shared_ptr.hpp>

#include <QWidget>
#include <QtCore/qnamespace.h>

#include <QHBoxLayout>

#include "./editwidget.hpp"

#include "../../model/filter/node.hpp"

namespace CSMWorld
{
    class Data;
}

namespace CSVFilter
{
    class RecordFilterBox : public QWidget
    {
            Q_OBJECT

            EditWidget* mEditWidget;
        public:

            RecordFilterBox (CSMWorld::Data& data, QWidget *parent = 0);

    public:
            void createFilterRequest(std::vector<std::pair<std::string, std::vector<std::string> > >& filterSource,
                                     Qt::DropAction action);

            void useFilterRequest(const std::string& idOfFilter);

        signals:

            void filterChanged (boost::shared_ptr<CSMFilter::Node> filter);
    };

}

#endif