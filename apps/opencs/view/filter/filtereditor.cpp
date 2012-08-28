#include "filtereditor.hpp"

#include "../../model/filter/matchfilter.hpp"

#include <QStandardItemModel>

FilterEditor::FilterEditor(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    QStandardItemModel *typeModel = new QStandardItemModel(this);

    QStandardItem *row1 = new QStandardItem("Exact");
    row1->setIcon(QIcon(":/icon/filter/exact.png"));
    row1->setData(MatchFilter::Exact);
    typeModel->appendRow(row1);

    QStandardItem *row2 = new QStandardItem("Wildcard");
    row2->setIcon(QIcon(":/icon/filter/wildcard.png"));
    row1->setData(MatchFilter::Wildcard);
    typeModel->appendRow(row2);

    QStandardItem *row3 = new QStandardItem("Regex");
    row3->setIcon(QIcon(":/icon/filter/regex.png"));
    row1->setData(MatchFilter::Regex);
    typeModel->appendRow(row3);

    typeCombo->setModel(typeModel);

    mMapper = new QDataWidgetMapper(this);
}

FilterEditor::~FilterEditor()
{
}

void FilterEditor::setModel(FilterEditModel *model)
{
    mMapper->setModel(model);
    mMapper->addMapping(nameEdit, 0);
    mMapper->addMapping(typeCombo, 1, "currentIndex");
    mMapper->addMapping(keyEdit, 2);
    mMapper->addMapping(valueEdit, 3);
}

void FilterEditor::setCurrentModelIndex(const QModelIndex &index)
{
    mMapper->setRootIndex(index.parent());
    mMapper->setCurrentModelIndex(index);
}
