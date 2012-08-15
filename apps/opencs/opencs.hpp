#ifndef OPENCS_H
#define OPENCS_H

#include <QMainWindow>
#include <QAbstractItemModel>

#include "esmdatamodel.hpp"
#include "views/idlist.hpp"

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

    ESMDataModel *model;

    IdList *idList;

private slots:
    void openFile();
    void addIdList();
};

#endif // OPENCS_H
