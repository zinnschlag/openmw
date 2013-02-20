#include <QSortFilterProxyModel>

class OpenFileProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    OpenFileProxyModel(QObject *parent = 0);
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};