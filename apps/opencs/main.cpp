#include <QtGui/QApplication>
#include "opencs.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenCS w;
    w.show();

    return a.exec();
}
