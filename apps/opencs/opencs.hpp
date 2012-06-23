#ifndef OPENCS_H
#define OPENCS_H

#include <QMainWindow>

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
};

#endif // OPENCS_H
