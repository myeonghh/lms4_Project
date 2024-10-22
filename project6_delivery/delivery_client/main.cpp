#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // [ex.01]
    MainWindow w;

    w.show();
    w.hide();

    return a.exec();
}
