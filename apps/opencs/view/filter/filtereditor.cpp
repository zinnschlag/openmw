#include "filtereditor.hpp"

#include "../../model/filter/matchfilter.hpp"



FilterEditor::FilterEditor(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);


    mMatchTypes = new QStandardItemModel(this);

    QStandardItem *row1 = new QStandardItem("Exact");
    row1->setIcon(QIcon(":/icon/filter/exact.png"));
    row1->setData(MatchFilter::Exact);
    mMatchTypes->appendRow(row1);

    QStandardItem *row2 = new QStandardItem("Wildcard");
    row2->setIcon(QIcon(":/icon/filter/wildcard.png"));
    row2->setData(MatchFilter::Wildcard);
    mMatchTypes->appendRow(row2);

    QStandardItem *row3 = new QStandardItem("Regex");
    row3->setIcon(QIcon(":/icon/filter/regex.png"));
    row3->setData(MatchFilter::Regex);
    mMatchTypes->appendRow(row3);


    mSetTypes = new QStandardItemModel(this);

    QStandardItem *setOpUnion = new QStandardItem("Union");
    setOpUnion->setIcon(QIcon(":/icon/filter/union.png"));
    setOpUnion->setData(SetOperationFilter::Union);
    mSetTypes->appendRow(setOpUnion);

    QStandardItem *setOpInter = new QStandardItem("Intersection");
    setOpInter->setIcon(QIcon(":/icon/filter/intersection.png"));
    setOpInter->setData(SetOperationFilter::Intersection);
    mSetTypes->appendRow(setOpInter);


    mMapper = new QDataWidgetMapper(this);
}

FilterEditor::~FilterEditor()
{
}

void FilterEditor::setModel(DataModel *model)
{
    mMapper->setModel(model);
    mMapper->addMapping(nameEdit, 0);
    mMapper->addMapping(typeCombo, 1, "currentIndex");
    mMapper->addMapping(keyEdit, 2);
    mMapper->addMapping(valueEdit, 3);
}

void FilterEditor::setCurrentModelIndex(const QModelIndex &index)
{
    //FIXME
    Filter* filter = static_cast<Filter*>(index.internalPointer());
    if(dynamic_cast<MatchFilter*>(filter)) {
        typeCombo->setModel(mMatchTypes);
    } else if (dynamic_cast<SetOperationFilter*>(filter)){
        typeCombo->setModel(mSetTypes);
    }

    mMapper->setRootIndex(index.parent());
    mMapper->setCurrentModelIndex(index);

    for(int i=0; i<4; i++) {
        bool editable = (mMapper->rootIndex().child(index.row(), i).flags() & Qt::ItemIsEnabled);
        mMapper->mappedWidgetAt(i)->setEnabled(editable);
    }
}
