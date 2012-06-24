#ifndef OPENCS_H
#define OPENCS_H

#include <QMainWindow>

#include <components/esm/esm_reader.hpp>
#include "esmdatamodel.hpp"

//#include "qtpropertybrowser/src/qtvariantproperty.h"
//#include "qtpropertybrowser/src/qttreepropertybrowser.h"

namespace Ui {
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

    ESM::ESMReader esm;
    ESMDataModel *model;

//    QtVariantPropertyManager *variantManager;
//    QtVariantEditorFactory *variantFactory;
//    QtTreePropertyBrowser *variantEditor;

private slots:
    void openFile();
    void selectObject(const QModelIndex &index);
};

#endif // OPENCS_H
