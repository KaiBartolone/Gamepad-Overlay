/**
 * @file mainwindow.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date October 2020
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
