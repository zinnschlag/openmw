#include "idlistitemdelegate.hpp"

#include <QtGui>


void IdlistItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{

    QStyledItemDelegate::paint(painter, option, index);
}

QSize IdlistItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *IdlistItemDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const

{
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void IdlistItemDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    QStyledItemDelegate::setEditorData(editor, index);
}

void IdlistItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QStyledItemDelegate::setModelData(editor, model, index);
}
