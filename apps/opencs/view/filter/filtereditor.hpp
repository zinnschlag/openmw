#ifndef FILTEREDITOR_HPP
#define FILTEREDITOR_HPP

#include "ui_filtereditor.h"

#include <QStandardItemModel>
#include <QDataWidgetMapper>

#include "../../viewmodel/datamodel.hpp"

namespace Ui
{
    class FilterEditor;
}

class FilterEditor : public QWidget, private Ui::FilterEditor
{
    Q_OBJECT

public:
    explicit FilterEditor(QWidget *parent = 0);
    ~FilterEditor();

    void setModel(DataModel *model);

public slots:
    void setCurrentModelIndex(const QModelIndex & index);

private:
    QDataWidgetMapper *mMapper;

    QStandardItemModel *mMatchTypes;
    QStandardItemModel *mSetTypes;
};

#endif
