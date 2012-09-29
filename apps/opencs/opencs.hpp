#ifndef OPENCS_H
#define OPENCS_H

#include <QMainWindow>
#include <QAbstractItemModel>

#include "model/gui/componentitem.hpp"

#include "view/idlist.hpp"

#include <QDockWidget>
#include <QUndoView>

#include <QTreeView>

#include "view/filter/filtertree.hpp"
#include "view/filter/filtereditor.hpp"

namespace Ui
{
class OpenCS;
}

class OpenCS : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit OpenCS(QWidget *parent = 0);
    ~OpenCS();
    
private:
    Ui::OpenCS *ui;
    DataModel *mModel;

    void updateComponents();

private slots:
    void openFile();
};

#endif // OPENCS_H
