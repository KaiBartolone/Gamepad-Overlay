#include "mainwindow.h"

#include <JoyShockLibrary.h>
#include <QApplication>
#include <iostream>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    // JOY_SHOCK_STATE state;
}