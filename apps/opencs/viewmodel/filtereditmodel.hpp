#ifndef FILTEREDITMODEL_HPP
#define FILTEREDITMODEL_HPP

#include <QAbstractItemModel>
#include <QUndoStack>

#include <QtXml/QDomElement>

#include "../model/filter/filter.hpp"
#include "../model/filter/setoperationfilter.hpp"

class FilterEditModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Roles {
        ItemCommandsRole = Qt::UserRole + 1
    };

    FilterEditModel(QObject *parent);
    ~FilterEditModel();

    void load();
    void readFilter(const QDomElement &element, Filter *parent);


    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex &parent);

    void executeCommand(const QString name, const QModelIndex &parent);

    bool accept(QList<QString> headers, QList<QVariant> row);


    QUndoStack *undoStack() const;

    //TODO make friend
    void emitDataChanged(const QModelIndex &index)
    {
      emit dataChanged(index, index);
    }

private:
    SetOperationFilter *mRootItem;
    QUndoStack *mUndoStack;
};

#endif
