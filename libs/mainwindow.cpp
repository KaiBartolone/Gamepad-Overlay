/**
 * @file mainwindow.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date October 2020
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "overlay.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    int size = qMin(this->size().height(), this->size().width()) / 3;
    ui->gamepad->setFixedSize(size, size);
}
