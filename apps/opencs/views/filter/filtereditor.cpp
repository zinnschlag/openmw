#include "filtereditor.hpp"
#include "ui_filtereditor.h"



FilterEditor::FilterEditor(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::FilterEditor)
{
    ui->setupUi(this);

    ui->typeCombo->addItem("Exact", MatchFilter::Exact);
    ui->typeCombo->addItem("Wildcard", MatchFilter::Wildcard);
    ui->typeCombo->addItem("Regex", MatchFilter::Regex);
}

FilterEditor::~FilterEditor()
{
}

void FilterEditor::editFilter(Filter *filter)
{
    mFilter = filter;

    MatchFilter* matchFilter = qobject_cast<MatchFilter*>(filter);
    if(matchFilter) {
       int selectedIndex = ui->typeCombo->findData(matchFilter->type());
       ui->typeCombo->setCurrentIndex(selectedIndex);

       ui->keyEdit->setText(matchFilter->key());
       ui->valueEdit->setText(matchFilter->value());
    }
}

void FilterEditor::on_pushButton_clicked()
{
    MatchFilter* matchFilter = qobject_cast<MatchFilter*>(mFilter);
    if(matchFilter) {
        int typeIndex = ui->typeCombo->currentIndex();
        QVariant typeData = ui->typeCombo->itemData(typeIndex);
        MatchFilter::MatchType filterType = static_cast<MatchFilter::MatchType>(typeData.toInt());
        matchFilter->setType(filterType);

        matchFilter->setKey(ui->keyEdit->text());
        matchFilter->setValue(ui->valueEdit->text());
    }
}
