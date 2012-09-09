#ifndef OPENCS_H
#define OPENCS_H

#include <QMainWindow>
#include <QAbstractItemModel>

#include "viewmodel/esmdatamodel.hpp"
#include "view/idlist.hpp"

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

    ModelItem *mRootItem;

    ESMDataModel *model;

    IdList *idList;

private slots:
    void openFile();
    void addIdList();
};

#endif // OPENCS_H
