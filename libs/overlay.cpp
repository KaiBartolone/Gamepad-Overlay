/**
 * @file overlay.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date October 2020
 */

#include <overlay.h>
#include <ui_overlay.h>

Overlay::Overlay(QWidget *parent)
// : QWidget(parent), ui(new Ui::Overlay), manager(QGamepadManager::instance())
{
    ui->setupUi(this);
    // connect(this->manager, &QGamepadManager::connectedGamepadsChanged, this, &Overlay::getGamepad);

    // Event connections
    // connect(this->gamepad, &QGamepad::buttonAChanged, this, &Overlay::repaint);
}

void Overlay::paintEvent(QPaintEvent *)
{
    // Initialize renderer with base asset
    QSvgRenderer *renderer;
    renderer = new QSvgRenderer(QString("assets/dualshock_black/base.svg"));
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);

    // Paint base svg on widget
    QPainter painter(this);
    renderer->render(&painter);
    renderer->setViewBox(QRectF(0, 0, this->width(), this->height()));

    QPoint corner = locateCorner(renderer->defaultSize(), renderer->viewBox().size());
    double scale = getScale(renderer->defaultSize(), renderer->viewBox().size());
}

void Overlay::paintButtons(QPaintDevice *device, QPoint corner, double scale)
{
    const double joystickRange = 10;
    std::string baseFolder = "assets/dualshock/";
    QPoint buttonPlace = {0, 0};
    QSvgRenderer renderer;
}

QPoint Overlay::locateCorner(QSize defaultSize, QSize viewBox)
{
    double defaultAR = (double)defaultSize.width() / (double)defaultSize.height();
    double viewAR = (double)viewBox.width() / (double)viewBox.height();

    // @var arCoeff lets us know which side of the svg borders the widget
    double arCoeff = viewAR / defaultAR;
    double width, height;
    int x, y;

    if (arCoeff > 1)
    {
        height = (double)viewBox.height();
        width = height * defaultAR;
        y = 0;
        x = (int)(.5 + ((double)viewBox.width() - width) / 2);
    }
    else if (arCoeff < 1)
    {
        width = (double)viewBox.width();
        height = width * 1 / defaultAR;
        x = 0;
        y = (int)(.5 + ((double)viewBox.height() - height) / 2);
    }
    else
    {
        x = 0;
        y = 0;
    }

    return QPoint(x, y);
}

double Overlay::getScale(QSize defaultSize, QSize viewBox)
{
    double result;
    QPoint corner = locateCorner(defaultSize, viewBox);

    // Since svg maintains aspect ratio, only height or width is needed
    double width = (double)viewBox.width() - 2 * corner.x();
    result = width / (double)defaultSize.width();

    return result;
}

// void Overlay::getGamepad()
// {
//     // Grab our device list
//     QList<int> gamepadList = manager->connectedGamepads();

//     // If empty set deviceID equal to -1
//     if (gamepadList.isEmpty())
//     {
//         deviceID = -1;
//         return;
//     }

//     // If gamepad is not connected, get new one
//     if (!manager->isGamepadConnected(deviceID)) deviceID = gamepadList[0];
// }