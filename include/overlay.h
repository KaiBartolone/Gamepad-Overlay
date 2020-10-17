/**
 * @file overlay.h
 * -----------------------------
 * @brief Defines dualshock overlay.
 * @author Bartolone, Kai
 */

#ifndef OVERLAY_H
#define OVERLAY_H

#include <QMouseEvent>
#include <QPaintDevice>
#include <QPainter>
#include <QSvgRenderer>
#include <QWidget>
#include <cmath>
#include <iostream>
#include <unordered_map>

namespace Ui
{
class Overlay;
}

class Overlay : public QWidget
{
    Q_OBJECT

  public:
    explicit Overlay(QWidget* parent = nullptr);
    ~Overlay();

  protected:
    /**
     * @fn painEvent
     * -----------------------------
     * Overloads default paint constructor in order to render dualshock overlay svgs.
     */
    void paintEvent(QPaintEvent*) override;
};

#endif // OVERLAY_H
