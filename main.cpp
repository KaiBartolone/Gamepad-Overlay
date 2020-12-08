#include "mainwindow.h"

#include <JoyShockLibrary.h>
#include <QApplication>
#include <iostream>

int WinMain(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    return a.exec();
}