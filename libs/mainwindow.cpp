/**
 * @file mainwindow.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date October 2020
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "overlay.h"
#include <Windows.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // SetForegroundWindow((HWND)winId());
    // setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    SetWindowPos((HWND)winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

    int size = qMin(this->size().height(), this->size().width()) / 2;
    ui->gamepad->setFixedSize(size, size);
}
