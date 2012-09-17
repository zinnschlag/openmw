#ifndef OPENCS_H
#define OPENCS_H

#include <QMainWindow>
#include <QAbstractItemModel>

#include "viewmodel/esmdatamodel.hpp"
#include "view/idlist.hpp"



#include <QDockWidget>
#include <QUndoView>

#include "view/filter/filtertree.hpp"
#include "view/filter/filtereditor.hpp"

class WidgetItem : public ModelItem
{
    Q_OBJECT

public:
    explicit WidgetItem(ModelItem *parent = 0)
        : ModelItem(parent)
    {}

    ~WidgetItem() {}

    void setTypeName(QString typeName){mTypeName = typeName;}
    void setModel(FilterEditModel *model){mModel = model;}

    void setDockArea(Qt::DockWidgetArea area){mArea = area;}

    QDockWidget *createDockWidget(QWidget *parent)
    {
        QDockWidget *idListDock = new QDockWidget(widgetTitle(), parent);
        idListDock->setFeatures(QDockWidget::AllDockWidgetFeatures);

        QWidget* innerWidget = createWidget(idListDock);
        idListDock->setWidget(innerWidget);

        return idListDock;
    }

    void addWidget(QMainWindow* parentWindow)
    {
        QDockWidget* widget = createDockWidget(parentWindow);
        parentWindow->addDockWidget(mArea, widget);
    }

    virtual QString widgetTitle() = 0;
    virtual QWidget* createWidget(QWidget *parent) = 0;

protected:
    QString mTypeName;

    FilterEditModel *mModel;

    Qt::DockWidgetArea mArea;
};

class IdListWidgetItem : public WidgetItem
{
    Q_OBJECT

public:
    explicit IdListWidgetItem(ESMDataModel* legacyModel, ModelItem *parent = 0)
        : WidgetItem(parent)
        , mLegacyModel(legacyModel)
    {}

    virtual QString widgetTitle()
    {
        return "ID List";
    }

    virtual QWidget* createWidget(QWidget *parent)
    {
        IdList* idList = new IdList(parent);
        idList->setModel(mLegacyModel);
        idList->setFilterModel(mModel);

        return idList;
    }

private:
    ESMDataModel* mLegacyModel;
};

class FilterTreeWidgetItem : public WidgetItem
{
    Q_OBJECT

public:
    explicit FilterTreeWidgetItem(ModelItem *parent = 0)
        : WidgetItem(parent)
    {}

    virtual QString widgetTitle()
    {
        return "Filter Tree";
    }

    virtual QWidget* createWidget(QWidget *parent)
    {
        FilterTree* idList = new FilterTree(parent);
        idList->setModel(mModel);

        return idList;
    }
};

class FilterEditorWidgetItem : public WidgetItem
{
    Q_OBJECT

public:
    explicit FilterEditorWidgetItem(ModelItem *parent = 0)
        : WidgetItem(parent)
    {}

    virtual QString widgetTitle()
    {
        return "Filter Editor";
    }

    virtual QWidget* createWidget(QWidget *parent)
    {
        FilterEditor* idList = new FilterEditor(parent);
        idList->setModel(mModel);

        return idList;
    }
};

class UndoRedoWidgetItem : public WidgetItem
{
    Q_OBJECT

public:
    explicit UndoRedoWidgetItem(ModelItem *parent = 0)
        : WidgetItem(parent)
    {}

    virtual QString widgetTitle()
    {
        return "Undo/Redo";
    }

    virtual QWidget* createWidget(QWidget *parent)
    {
        QUndoView *undoView = new QUndoView(parent);
        //undoView->setStack(filterModel->undoStack());

        return undoView;
    }
};

class ItemModelWidgetItem : public WidgetItem
{
    Q_OBJECT

public:
    explicit ItemModelWidgetItem(ModelItem *parent = 0)
        : WidgetItem(parent)
    {}

    virtual QString widgetTitle()
    {
        return "Item Model";
    }

    virtual QWidget* createWidget(QWidget *parent)
    {
        QTreeView *itemModelTreeView = new QTreeView(parent);
        itemModelTreeView->setModel(mModel);
        itemModelTreeView->resizeColumnToContents(0);

        return itemModelTreeView;
    }
};

// =========================================================================

namespace Ui
{
class OpenCS;
}

class OpenCS : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit OpenCS(QWidget *parent = 0);
    ~OpenCS();
    
private:
    Ui::OpenCS *ui;

    ModelItem *mRootItem;

    ESMDataModel *model;

    IdList *idList;

private slots:
    void openFile();
    void addIdList();
};

#endif // OPENCS_H
