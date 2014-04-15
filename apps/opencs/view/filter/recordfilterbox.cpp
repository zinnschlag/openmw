
#include "recordfilterbox.hpp"

#include <QHBoxLayout>
#include <QLabel>

#include "editwidget.hpp"

CSVFilter::RecordFilterBox::RecordFilterBox (CSMWorld::Data& data, QWidget *parent)
: QWidget (parent), mEditWidget(new EditWidget(data, this))
{
    QHBoxLayout *layout = new QHBoxLayout (this);

    layout->setContentsMargins (0, 0, 0, 0);

    layout->addWidget (new QLabel ("Record Filter", this));

    layout->addWidget (mEditWidget);

    setLayout (layout);

    connect (
        mEditWidget, SIGNAL (filterChanged (boost::shared_ptr<CSMFilter::Node>)),
        this, SIGNAL (filterChanged (boost::shared_ptr<CSMFilter::Node>)));
}

void CSVFilter::RecordFilterBox::createFilterRequest (std::vector< std::pair< std::string, std::vector< std::string > > >& filterSource,
                                                      Qt::DropAction action)
{
    mEditWidget->createFilterRequest(filterSource, action);
}

void CSVFilter::RecordFilterBox::useFilterRequest (const std::string& idOfFilter)
{
    mEditWidget->clear();
    mEditWidget->insert(QString::fromUtf8(idOfFilter.c_str()));
}
