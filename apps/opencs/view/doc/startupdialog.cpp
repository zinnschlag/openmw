#include <QtGui>

#include "startupdialog.hpp"

CSVDoc::StartupDialog::StartupDialog(QWidget *parent) :
    QDialog(parent)
{
    //set modal startup values
    //Dialog acts as a main window, here.  Should probably start the main window
    //as a view without a document, then display this startup dialog over it.

    this->setModal(true);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    QDesktopWidget* d = QApplication::desktop();

    int left = (d->width() - this->width()) / 2;
    int top = (d->height() - this->height()) / 2;

    this->move(left, top);

    //create document buttons
    mNewDocumentButton = new QPushButton(tr("&New"));
    mExistingDocumentButton = new QPushButton(tr("Open &Existing..."));
    mRecentDocumentButton = new QPushButton(tr("Open &Recent"));

    //contain buttons in a button box
    mDocumentButtonBox = new QDialogButtonBox(Qt::Vertical);
    mDocumentButtonBox->addButton(mNewDocumentButton, QDialogButtonBox::ActionRole);
    mDocumentButtonBox->addButton(mExistingDocumentButton, QDialogButtonBox::ActionRole);
    mDocumentButtonBox->addButton(mRecentDocumentButton, QDialogButtonBox::ActionRole);

    //add title labels
    mTitleLabel = new QLabel(QString("OpenMW"));
    mSubtitleLabel = new QLabel(QString("Construction Set"));
    mIconLabel = new QLabel();

    mTitleLabel->setFont(QFont(mTitleLabel->font().family(),24,2,true));
    mSubtitleLabel->setFont(QFont(mSubtitleLabel->font().family(),18,1,false));
    QImage icon (QString(":./openmw.png"));

    mIconLabel->setScaledContents(true);
    mIconLabel->setPixmap(QPixmap::fromImage(icon.scaled(64, 64, Qt::KeepAspectRatio, Qt::FastTransformation)));

    //build right-hand frame for displaying recent file list
    mRecentDocumentFrame = new QFrame;
    mRecentDocumentFrame->setWindowTitle(QString("Recent Plugins..."));
    //mRecentDocumentFrame->

    //create and build form layouts
    QHBoxLayout* leftSideLayout = new QHBoxLayout;
    QHBoxLayout* rightSideLayout = new QHBoxLayout;
    QVBoxLayout* upperRightLayout = new QVBoxLayout;
    QHBoxLayout* upperLayout = new QHBoxLayout;
    QHBoxLayout* lowerLayout = new QHBoxLayout;
    QVBoxLayout* mainLayout = new QVBoxLayout;

    leftSideLayout->addWidget (mDocumentButtonBox);
    rightSideLayout->addWidget (mRecentDocumentFrame);
    upperRightLayout->addWidget (mTitleLabel);
    upperRightLayout->addWidget (mSubtitleLabel);
    upperLayout->addWidget (mIconLabel);
    upperLayout->addLayout (upperRightLayout);

    lowerLayout->addLayout (leftSideLayout);
    lowerLayout->addLayout (rightSideLayout);
    mainLayout->addLayout (upperLayout);
    mainLayout->addLayout (lowerLayout);

    setLayout (mainLayout);

}
