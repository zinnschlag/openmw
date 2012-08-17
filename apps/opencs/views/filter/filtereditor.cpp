#include "filtereditor.hpp"

FilterEditor::FilterEditor(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    typeCombo->addItem("Exact", MatchFilter::Exact);
    typeCombo->addItem("Wildcard", MatchFilter::Wildcard);
    typeCombo->addItem("Regex", MatchFilter::Regex);
}

FilterEditor::~FilterEditor()
{
}

void FilterEditor::editFilter(Filter *filter)
{
    mFilter = filter;

    MatchFilter* matchFilter = qobject_cast<MatchFilter*>(filter);
    if(matchFilter) {
       int selectedIndex = typeCombo->findData(matchFilter->type());
       typeCombo->setCurrentIndex(selectedIndex);

       keyEdit->setText(matchFilter->key());
       valueEdit->setText(matchFilter->value());
    }
}

void FilterEditor::on_pushButton_clicked()
{
    MatchFilter* matchFilter = qobject_cast<MatchFilter*>(mFilter);
    if(matchFilter) {
        int typeIndex = typeCombo->currentIndex();
        QVariant typeData = typeCombo->itemData(typeIndex);
        MatchFilter::MatchType filterType = static_cast<MatchFilter::MatchType>(typeData.toInt());
        matchFilter->setType(filterType);

        matchFilter->setKey(keyEdit->text());
        matchFilter->setValue(valueEdit->text());
    }
}
