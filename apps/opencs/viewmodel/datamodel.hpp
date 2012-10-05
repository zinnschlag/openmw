#ifndef DATAMODEL_HPP
#define DATAMODEL_HPP

#include <QAbstractItemModel>
#include <QUndoStack>

#include <QMenu>

#include "../persistence/filter/filterdom.hpp"

#include "../model/filter/filter.hpp"
#include "../model/filter/setoperationfilter.hpp"

class DataModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Roles {
        ItemCommandsRole = Qt::UserRole + 1,
        ItemParamsRole
    };

    DataModel(QObject *parent);
    ~DataModel();

    void loadGuiData();
    void loadFilterDirectory(QString path);
    void loadEsmFile(QString filePath);

    void fillContextMenu(QMenu *menu, const QModelIndex &index);

    bool accept(const QModelIndex &index, QList<QString> headers, QList<QVariant> row);

    QUndoStack *undoStack() const;

    // QAbstractTableModel

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;


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

    void emitLayoutChanged()
    {
      layoutChanged();
    }

    //TODO end

public slots:
    void actionExecuted();

private:
    ModelItem *mModelRoot;

    ModelItem *filterParentItem;
    ModelItem *esmFilesParent;
    ModelItem *guiRootItem;

    QUndoStack *mUndoStack;
};

#endif
