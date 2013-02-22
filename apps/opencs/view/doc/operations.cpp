
#include "operations.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include "operation.hpp"

CSVDoc::Operations::Operations()
{
    /// \todo make widget height fixed (exactly the height required to display all operations)
    QWidget *widgetContainer = new QWidget (this);
    mLayout = new QVBoxLayout;

    widgetContainer->setLayout (mLayout);
    setFixedHeight (widgetContainer->height());
    setTitleBarWidget (new QWidget (this));

    setFeatures (QDockWidget::NoDockWidgetFeatures);
}

void CSVDoc::Operations::setProgress (int current, int max, int type, int threads)
{
    for (std::vector<Operation *>::iterator iter (mOperations.begin()); iter!=mOperations.end(); ++iter)
        if ((*iter)->getType()==type)
        {
            (*iter)->setProgress (current, max, threads);
            return;
        }

    Operation *operation = new Operation (type);

    connect (operation, SIGNAL (abortOperation (int)), this, SIGNAL (abortOperation (int)));
    mLayout->addLayout (operation->getLayout());
    mOperations.push_back (operation);
    operation->setProgress (current, max, threads);
}

void CSVDoc::Operations::quitOperation (int type)
{
    for (std::vector<Operation *>::iterator iter (mOperations.begin()); iter!=mOperations.end(); ++iter)
        if ((*iter)->getType()==type)
        {
            delete *iter;
            mOperations.erase (iter);
            break;
        }
}
