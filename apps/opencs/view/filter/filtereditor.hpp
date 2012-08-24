#ifndef FILTEREDITOR_HPP
#define FILTEREDITOR_HPP

#include "ui_filtereditor.h"

#include "../../viewmodel/filtereditmodel.hpp"
#include "QDataWidgetMapper"


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

    void setModel(FilterEditModel *model);

public slots:
    void setCurrentModelIndex(const QModelIndex & index);

private:
    QDataWidgetMapper *mMapper;
    bool mInputChanged;

private slots:
    void inputChanged();
    void submitChanges();
};

#endif
