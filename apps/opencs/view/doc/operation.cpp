
#include <sstream>

#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>

#include "operation.hpp"
#include "../../model/doc/document.hpp"

void CSVDoc::Operation::updateLabel (int threads)
{
    if (threads==-1 || ((threads==0)!=mStalling))
    {
        std::string name ("unknown operation");

        switch (mType)
        {
            case CSMDoc::State_Saving: name = "saving"; break;
            case CSMDoc::State_Verifying: name = "verifying"; break;
        }

        std::ostringstream stream;

        if ((mStalling = (threads<=0)))
        {
            stream << name << " (waiting for a free worker thread)";
        }
        else
        {
            stream << name << " (%p%)";
        }

        mProgressBar->setFormat (stream.str().c_str());
    }
}

CSVDoc::Operation::Operation (int type) : mType (type), mStalling (false)
{
    mProgressBar = new QProgressBar ();
    mAbortButton = new QPushButton ("Abort");
    mVBoxLayout = new QVBoxLayout();

    mVBoxLayout->addWidget (mProgressBar);
    mVBoxLayout->addWidget (mAbortButton);

    connect (mAbortButton, SIGNAL (clicked()), this, SLOT (abortOperation()));
    /// \todo Add a cancel button or a pop up menu with a cancel item

    updateLabel();

    /// \todo assign different progress bar colours to allow the user to distinguish easily between operation types
}

void CSVDoc::Operation::setProgress (int current, int max, int threads)
{
    updateLabel (threads);
    mProgressBar->setRange (0, max);
    mProgressBar->setValue (current);
}

int CSVDoc::Operation::getType() const
{
    return mType;
}

QVBoxLayout *CSVDoc::Operation::getLayout() const
{
    return mVBoxLayout;
}

void CSVDoc::Operation::abortOperation()
{
    emit abortOperation (mType);
}
