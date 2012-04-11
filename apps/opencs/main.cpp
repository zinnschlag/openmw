
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QtDebug>

//test
#include <string>
#include <iostream>
#include <components/esm/esm_reader.hpp>

//#include "mainwindow.hpp"
#include "esmdatamodel.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Now we make sure the current dir is set to application path
    QDir dir(QCoreApplication::applicationDirPath());

    #if defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS") {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }

    // force Qt to load only LOCAL plugins, don't touch system Qt installation
    QDir pluginsPath(QCoreApplication::applicationDirPath());
    pluginsPath.cdUp();
    pluginsPath.cd("Plugins");

    QStringList libraryPaths;
    libraryPaths << pluginsPath.path() << QCoreApplication::applicationDirPath();
    app.setLibraryPaths(libraryPaths);
    #endif

    QDir::setCurrent(dir.absolutePath());

    ESM::ESMReader esm;
    esm.setEncoding("win1252");

    std::string filename = "Morrowind.esm";
    std::cout << "\nFile: " << filename << std::endl;



    try {
        esm.open(filename);
        ESMDataModel *model = new ESMDataModel(esm);

    } catch(std::exception &e) {
        std::cout << "\nERROR:\n\n  " << e.what() << std::endl;
        return 1;
    }


    return app.exec();
//    MainDialog dialog;
//    return dialog.exec();

}
