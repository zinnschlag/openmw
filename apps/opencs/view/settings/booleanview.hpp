#ifndef CSVSETTINGS_BOOLEANVIEW_HPP
#define CSVSETTINGS_BOOELANVIEW_HPP

#include <QList>
#include <QWidget>

#include "view.hpp"
#include "support.hpp"

class QDataWidgetMapper;
class QAbstractItemModel;
class QSortFilterProxyModel;
class QStandardItemModel;

namespace CSMSettings {
    class IViewAdapter;
    class DefinitionModel;
}

namespace CSVSettings
{
    class BooleanView : public View
    {
        QList <QWidget *> mWidgets;

    public:
        explicit BooleanView (QAbstractItemModel *booleanAdapter,
                              const CSMSettings::Setting *setting,
                              QWidget *parent = 0);


    protected:

        void createView (const CSMSettings::Setting *setting);
        void createModel (const QString &settingName);
    };

    class BooleanViewFactory : public QObject, public IViewFactory
    {
        Q_OBJECT

    public:
        explicit BooleanViewFactory (QWidget *parent = 0)
            : QObject (parent)
        {}

        BooleanView *createView (QStandardItemModel &model,
                                 const CSMSettings::Setting *setting);
    };
}
#endif // CSVSETTINGS_BOOLEANVIEW_HPP
