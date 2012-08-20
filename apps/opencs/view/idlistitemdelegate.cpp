#include "idlistitemdelegate.hpp"

#include "../viewmodel/esmdatamodel.hpp"

#include <QtGui>

IdlistItemDelegate::IdlistItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

QWidget *IdlistItemDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &,
                                          const QModelIndex &index) const
{

    QStringList possibleValues = index.model()->data(index, ESMDataModel::PossibleValuesRole).toStringList();

    QCompleter *autoComplete = new QCompleter(possibleValues);

    QLineEdit *editor = new QLineEdit(parent);
    editor->setCompleter(autoComplete);

    connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
    return editor;
}

void IdlistItemDelegate::commitAndCloseEditor()
{
    QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

void IdlistItemDelegate::setEditorData(QWidget *editor,
                                       const QModelIndex &index) const
{
    QLineEdit *edit = qobject_cast<QLineEdit*>(editor);
    if (edit)
    {
        edit->setText(index.model()->data(index, Qt::EditRole).toString());
    }
}

void IdlistItemDelegate::setModelData(QWidget *editor,
                                      QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *edit = qobject_cast<QLineEdit *>(editor);
    if (edit)
    {
        model->setData(index, edit->text());
    }
}
