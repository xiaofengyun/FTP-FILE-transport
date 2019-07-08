#include "mainwindow.h"
#include <QApplication>
#include"painter.h"
#include <QMetaType>
//Q_DECLARE_METATYPE("char *");
int main(int argc, char *argv[])
{
    qRegisterMetaType<char *>( "char *" );
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
