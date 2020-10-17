/**
 * @file overlay.h
 * -----------------------------
 * @brief Defines dualshock overlay.
 * @author Bartolone, Kai
 */

#ifndef OVERLAY_H
#define OVERLAY_H

#include <QGamepad>
#include <QGamepadManager>
#include <QObject>
#include <QPaintDevice>
#include <QPainter>
#include <QString>
#include <QSvgRenderer>
#include <QWidget>

namespace Ui
{
class Overlay;
}

class Overlay : public QWidget
{
    Q_OBJECT

  public:
    explicit Overlay(QWidget* parent = nullptr);

    /**
     * @fn search
     * -----------------------------
     * Generates list of gamepades and choose first one.
     */
    void getGamepad();

  protected:
    /**
     * @fn paintEvent
     * -----------------------------
     * Overloads default paint constructor in order to render gamepad overlay svgs.
     */
    void paintEvent(QPaintEvent*) override;

  private:
    Ui::Overlay* ui;
    QGamepadManager* manager;
    QGamepad gamepad;
    int deviceID = -1;
};

#endif // OVERLAY_H
