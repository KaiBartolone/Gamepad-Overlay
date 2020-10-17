/*
 * @file overlay.cpp
 * -----------------------------
 * @author Bartolone, Kai
 */

#include <overlay.h>
#include <ui_overlay.h>

Overlay::Overlay(QWidget* parent) : QWidget(parent), ui(new Ui::Overlay) { ui->setupUi(this); }

Overlay::~Overlay(){};
void Overlay::paintEvent(QPaintEvent*){};