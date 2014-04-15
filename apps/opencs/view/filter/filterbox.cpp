
#include "filterbox.hpp"

#include <QHBoxLayout>
#include <QDragEnterEvent>

#include "recordfilterbox.hpp"

#include <apps/opencs/model/world/tablemimedata.hpp>

CSVFilter::FilterBox::FilterBox (CSMWorld::Data& data, QWidget *parent)
: QWidget (parent), mRecordFilterBox(new RecordFilterBox(data, this))
{
    QHBoxLayout *layout = new QHBoxLayout (this);

    layout->setContentsMargins (0, 0, 0, 0);

    layout->addWidget (mRecordFilterBox);

    setLayout (layout);

    connect (mRecordFilterBox,
        SIGNAL (filterChanged (boost::shared_ptr<CSMFilter::Node>)),
        this, SIGNAL (recordFilterChanged (boost::shared_ptr<CSMFilter::Node>)));

    setAcceptDrops(true);
}

void CSVFilter::FilterBox::dropEvent (QDropEvent* event)
{
    std::vector<CSMWorld::UniversalId> data = dynamic_cast<const CSMWorld::TableMimeData*> (event->mimeData())->getData();

    emit recordDropped(data, event->proposedAction());
}

void CSVFilter::FilterBox::dragEnterEvent (QDragEnterEvent* event)
{
    event->acceptProposedAction();
}

void CSVFilter::FilterBox::dragMoveEvent (QDragMoveEvent* event)
{
    event->accept();
}

void CSVFilter::FilterBox::createFilterRequest (std::vector< std::pair< std::string, std::vector< std::string > > >& filterSource,
                                                Qt::DropAction action)
{
    mRecordFilterBox->createFilterRequest(filterSource, action);
}

void CSVFilter::FilterBox::useFilterRequest (const std::string& idOfFilter)
{
    mRecordFilterBox->useFilterRequest(idOfFilter);
}
