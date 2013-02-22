#ifndef CSV_DOC_OPERATION_H
#define CSV_DOC_OPERATION_H

#include <QObject>

class QHBoxLayout;
class QProgressBar;
class QPushButton;

namespace CSVDoc
{
    class Operation: public QObject
    {
            Q_OBJECT

            int mType;
            bool mStalling;
            QHBoxLayout *mLayout;
            QProgressBar *mProgressBar;
            QPushButton *mAbortButton;

            // not implemented
            Operation (const Operation&);
            Operation& operator= (const Operation&);

            void updateLabel (int threads = -1);

        public:

            Operation (int type);
            ~Operation();

            void setProgress (int current, int max, int threads);

            int getType() const;
            QHBoxLayout *getLayout() const;
            void deleteLayout();

        private:

            void setBarColor (int type);


        signals:

            void abortOperation (int type);

        private slots:

            void abortOperation ();
    };
}

#endif
