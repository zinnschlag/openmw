#include "filtereditor.hpp"
#include "ui_filtereditor.h"

FilterEditor::FilterEditor(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::FilterEditor)
{
    ui->setupUi(this);
}

FilterEditor::~FilterEditor()
{
}
