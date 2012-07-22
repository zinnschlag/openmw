#ifndef OPENCS_H
#define OPENCS_H

#include <QMainWindow>
#include <QAbstractItemModel>

#include <components/esm/esm_reader.hpp>

namespace Ui {
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

    ESM::ESMReader esm;
    QAbstractItemModel *model;

private slots:
    void openFile();
};

#endif // OPENCS_H
