#ifndef USERSETTINGSDIALOG_H
#define USERSETTINGSDIALOG_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QListWidgetItem>
#include <QApplication>

#include "../../model/settings/usersettings.hpp"
#include "../../model/settings/support.hpp"

class QStackedWidget;
class QListWidget;
class QDataWidgetMapper;

namespace CSVSettings {

    class AbstractPage;

    class UserSettingsDialog : public QMainWindow
    {
        Q_OBJECT

        QListWidget *mListWidget;
        QStackedWidget *mStackedWidget;
        QDataWidgetMapper *mMapper;

    public:
        explicit UserSettingsDialog(QMainWindow *parent = 0);

    private:

        /// Settings are written on close
        void closeEvent (QCloseEvent *event);

        /// return the setting page by name
        /// performs dynamic cast to AbstractPage *
        AbstractPage &getAbstractPage (int index);

        void setupStack();
        void createPage (const QString &pageName);

    public slots:

        /// Called when a different page is selected in the left-hand list widget
        void slotChangePage (QListWidgetItem*, QListWidgetItem*);
    };

}
#endif // USERSETTINGSDIALOG_H
