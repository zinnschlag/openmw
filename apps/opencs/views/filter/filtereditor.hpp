#ifndef FILTEREDITOR_HPP
#define FILTEREDITOR_HPP

#include <QDockWidget>

namespace Ui
{
    class FilterEditor;
}

class FilterEditor : public QDockWidget
{
    Q_OBJECT

public:
    explicit FilterEditor(QWidget *parent = 0);
    ~FilterEditor();

private:
    Ui::FilterEditor *ui;
};

#endif
