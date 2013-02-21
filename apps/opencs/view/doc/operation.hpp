#ifndef CSV_DOC_OPERATION_H
#define CSV_DOC_OPERATION_H

#include <QObject>

class QProgressBar;
class QPushButton;
class QVBoxLayout;

namespace CSVDoc
{
    class Operation: public QObject
    {
            Q_OBJECT

            int mType;
            bool mStalling;
            QProgressBar *mProgressBar;
            QPushButton  *mAbortButton;
            QVBoxLayout  *mVBoxLayout;

            // not implemented
            Operation (const Operation&);
            Operation& operator= (const Operation&);

            void updateLabel (int threads = -1);

        public:

            Operation (int type);

            void setProgress (int current, int max, int threads);

            int getType() const;

        private:

            void setBarColor (int type);
            QVBoxLayout* getLayout() const;

        signals:

            void abortOperation (int type);

        private slots:

            void abortOperation ();
    };
}

#endif
