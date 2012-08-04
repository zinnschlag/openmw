#ifndef IDLISTITEMDELEGATE_HPP
#define IDLISTITEMDELEGATE_HPP

#include <QItemEditorFactory>
#include <QStyledItemDelegate>


class IdlistItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    IdlistItemDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

private slots:
    void commitAndCloseEditor();

};


#endif
