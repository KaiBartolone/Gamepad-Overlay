/*
 * @file overlay.cpp
 * -----------------------------
 * @author Bartolone, Kai
 */

#include <overlay.h>
#include <ui_overlay.h>

Overlay::Overlay(QWidget* parent)
    : QWidget(parent), ui(new Ui::Overlay), manager(QGamepadManager::instance())
{
    ui->setupUi(this);
    // QObject::connect(&manager, &QGamepadManager::connectedGamepadsChanged, this,
    //                  &Overlay::getGamepad);
    QObject::connect(this->manager, &QGamepadManager::connectedGamepadsChanged, this,
                     &Overlay::getGamepad);
}

void Overlay::paintEvent(QPaintEvent*)
{
    // Initialize renderer with base asset
    QSvgRenderer* renderer;
    renderer = new QSvgRenderer(QString("assets/dualshock_black/base.svg"));
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);

    // Paint base svg on widget
    QPainter painter(this);
    renderer->render(&painter);
    renderer->setViewBox(QRectF(0, 0, this->width(), this->height()));

    // QPoint corner = locateCorner(renderer->defaultSize(), renderer->viewBox().size());
    // double scale = getScale(renderer->defaultSize(), renderer->viewBox().size());
};

void Overlay::getGamepad()
{
    // Grab our device list
    QList<int> gamepadList = manager->connectedGamepads();

    // If empty set deviceID equal to -1
    if (gamepadList.isEmpty())
    {
        deviceID = -1;
        return;
    }

    // If gamepad is not connected, get new one
    if (!manager->isGamepadConnected(deviceID)) deviceID = gamepadList[0];
}