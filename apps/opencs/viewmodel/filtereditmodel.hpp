#ifndef FILTEREDITMODEL_HPP
#define FILTEREDITMODEL_HPP

#include <QAbstractItemModel>
#include <QUndoStack>

#include "../persistence/filter/filterdom.hpp"

#include "../model/filter/filter.hpp"
#include "../model/filter/setoperationfilter.hpp"

class FilterEditModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Roles {
        ItemCommandsRole = Qt::UserRole + 1,
        ItemParamsRole
    };

    FilterEditModel(ModelItem *rootModelItem, QObject *parent);
    ~FilterEditModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    void executeCommand(const QModelIndex &parent, const QString commandType, QVariant param);

    bool accept(const QModelIndex &index, QList<QString> headers, QList<QVariant> row);


    QUndoStack *undoStack() const;

    //TODO make friend
    void emitDataChanged(const QModelIndex &index)
    {
      emit dataChanged(index, index);
    }

    void emitBeginInsertRows(const QModelIndex& parent, int first, int last)
    {
      beginInsertRows(parent, first, last);
    }

    void emitEndInsertRows()
    {
      endInsertRows();
    }

    void emitBeginRemoveRows(const QModelIndex& parent, int first, int last)
    {
      beginRemoveRows(parent, first, last);
    }

    void emitEndRemoveRows()
    {
      endRemoveRows();
    }
    //TODO end

private:
    ModelItem* mModelRoot;

    QUndoStack *mUndoStack;
};

#endif
