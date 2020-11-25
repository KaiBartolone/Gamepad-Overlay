/**
 * @file overlay.h
 * -----------------------------
 * @brief Defines gamepad overlay widget.
 * @author Bartolone, Kai
 */

#ifndef OVERLAY_H
#define OVERLAY_H

// #include <QGamepad>
// #include <QGamepadManager>
#include <QObject>
#include <QPaintDevice>
#include <QPainter>
#include <QString>
#include <QSvgRenderer>
#include <QWidget>
#include <string>

namespace Ui
{
  class Overlay;
}

class Overlay : public QWidget
{
  Q_OBJECT

public:
  explicit Overlay(QWidget *parent = nullptr);

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
  void paintEvent(QPaintEvent *) override;

  /** Private Functions */
private:
  /**
     * @fn paintButtons
     * -----------------------------
     * Helper function for paintEvent that paints buttons that are on.
     */
  void paintButtons(QPaintDevice *device, QPoint corner, double scale);

  /**
     * @fn getScale
     * -----------------------------
     * Returns the scale of the base dualshock svg.
     * @param defaultSize is provided by a member function of the svg renderer
     * @param viewBox is the size of the widget the svg is drawn on
     */
  double getScale(QSize defaultSize, QSize viewBox);

  /**
     * @fn locateCorner
     * -----------------------------
     * Locates the corner point of the base dualshock svg on the widget.
     * @param defaultSize is provided by a member function of the svg renderer
     * @param viewBox is the size of the widget the svg is drawn on
     */
  QPoint locateCorner(QSize defaultSize, QSize viewBox);

  /** Private Members */
private:
  Ui::Overlay *ui;
  // QGamepadManager* manager;
  // QGamepad gamepad;
  int deviceID = -1; // -1 signifies no device
};

#endif // OVERLAY_H
