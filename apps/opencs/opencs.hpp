#ifndef OPENCS_H
#define OPENCS_H

#include <QMainWindow>
#include <QAbstractItemModel>

<<<<<<< HEAD
#include "esmdatamodel.hpp"

=======
>>>>>>> 6a60973... OpenCS: Brackets cleanup
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

private slots:
    void openFile();
    void addIdList();
};

#endif // OPENCS_H
