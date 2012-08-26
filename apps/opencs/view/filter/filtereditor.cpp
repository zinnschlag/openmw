#include "filtereditor.hpp"

#include <QTimer>

#include "../../model/filter/matchfilter.hpp"

FilterEditor::FilterEditor(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    mInputChanged = false;

    //FIXME
    typeCombo->addItem("Exact", MatchFilter::Exact);
    typeCombo->addItem("Wildcard", MatchFilter::Wildcard);
    typeCombo->addItem("Regex", MatchFilter::Regex);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(submitChanges()));
    timer->start(300);

    mMapper = new QDataWidgetMapper(this);
}

FilterEditor::~FilterEditor()
{
}

void FilterEditor::setModel(FilterEditModel *model)
{
    mMapper->setModel(model);
    mMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    mMapper->addMapping(nameEdit, 0);
    mMapper->addMapping(typeCombo, 1, "currentIndex");
    mMapper->addMapping(keyEdit, 2);
    mMapper->addMapping(valueEdit, 3);

    connect(nameEdit, SIGNAL(textEdited(QString)), this, SLOT(inputChanged()));
    connect(typeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(inputChanged()));
    connect(keyEdit, SIGNAL(textEdited(QString)), this, SLOT(inputChanged()));
    connect(valueEdit, SIGNAL(textEdited(QString)), this, SLOT(inputChanged()));
}

void FilterEditor::setCurrentModelIndex(const QModelIndex &index)
{
    mMapper->setRootIndex(index.parent());
    mMapper->setCurrentModelIndex(index);
}

void FilterEditor::inputChanged()
{
    mInputChanged = true;
}

void FilterEditor::submitChanges()
{
    if(mInputChanged) {
        mMapper->submit();
        mInputChanged = false;
    }
}
