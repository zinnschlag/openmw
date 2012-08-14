#ifndef FILTEREDITOR_HPP
#define FILTEREDITOR_HPP

#include <QDockWidget>

#include "../idlistfilter.hpp"
#include "../../model/filter/matchfilter.hpp"

namespace Ui
{
    class FilterEditor;
}

class FilterEditor : public QDockWidget
{
    Q_OBJECT
    Q_ENUMS(MatchFilter::MatchType)

public:
    explicit FilterEditor(QWidget *parent = 0);
    ~FilterEditor();

public slots:
    void editFilter(Filter* filter);

private slots:
    void on_pushButton_clicked();

private:
    Ui::FilterEditor *ui;
    Filter *mFilter;
};

#endif
