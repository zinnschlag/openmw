#ifndef STARTUPDIALOG_HPP
#define STARTUPDIALOG_HPP

#include <QDialog>

class QLabel;
class QDialogButtonBox;
class QFrame;

namespace CSVDoc
{
    class StartupDialog : public QDialog
    {
        Q_OBJECT
    public:
        explicit StartupDialog(QWidget *parent = 0);
    
    private:

        QLabel* mTitleLabel;
        QLabel* mSubtitleLabel;
        QLabel* mIconLabel;
        QDialogButtonBox* mDocumentButtonBox;
        QPushButton* mNewDocumentButton;
        QPushButton* mExistingDocumentButton;
        QPushButton* mRecentDocumentButton;
        QFrame* mRecentDocumentFrame;

        void buildLayout();
        void initWindow();
        void initWidgets();

    //signals:
    
    //public slots:
    
    };
}

#endif // STARTUPDIALOG_HPP
