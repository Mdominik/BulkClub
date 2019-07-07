#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    qInfo() << QStyleFactory::keys();
//    a.setStyle(QStyleFactory::create("Fusion"));
    w.show();
    return a.exec();
}
