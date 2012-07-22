#ifndef IDLIST_HPP
#define IDLIST_HPP

#include <QDockWidget>

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

namespace Ui {
class IdList;
}

class IdList : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit IdList(QWidget *parent = 0);
    ~IdList();
    
    void setModel(QAbstractItemModel *model);

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::IdList *ui;

    QSortFilterProxyModel *mSortModel;
};

#endif
