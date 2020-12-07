/**
 * @file overlay.cpp
 * ----------
 * @author Bartolone, Kai
 * @date October 2020
 */

#include <overlay.h>
#include <ui_overlay.h>

#define MAX_PLAYERS 12

Overlay::Overlay(QWidget* parent) : QWidget(parent), ui(new Ui::Overlay)
{
    ui->setupUi(this);
    connectGamepad();
}

void Overlay::paintEvent(QPaintEvent*)
{
    // Initialize renderer with base asset
    QSvgRenderer* renderer;

    if (deviceID != -1)
        renderer = new QSvgRenderer(QString("assets/dualshock_black/base.svg"));
    else
        renderer = new QSvgRenderer(QString("assets/dualshock_black/disconnected.svg"));

    renderer->setAspectRatioMode(Qt::KeepAspectRatio);

    // Paint base svg on widget
    QPainter painter(this);
    renderer->render(&painter);
    renderer->setViewBox(QRectF(0, 0, this->width(), this->height()));

    if (deviceID != -1)
    {
        QPoint corner = locateCorner(renderer->defaultSize(), renderer->viewBox().size());
        double scale = getScale(renderer->defaultSize(), renderer->viewBox().size());
        paintFeatures(this, corner, scale);
    }
}

void Overlay::paintFeatures(QPaintDevice* device, QPoint corner, double scale)
{
    std::string baseFolder = "assets/dualshock_black/";

    QPoint buttonPlace = {0, 0};
    QSvgRenderer renderer;

    paintButtons(this, corner, scale);
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

int Overlay::getGamepad()
{
    // Get max amount connected controllers
    int num_devices = JslConnectDevices();
    int handle_array[MAX_PLAYERS];
    JslGetConnectedDeviceHandles(handle_array, MAX_PLAYERS);

    // Grab first device if there is one
    if (num_devices == 0)
        return -1;
    else
        return handle_array[0];
}

bool Overlay::connectGamepad()
{
    // Get max amount connected controllers
    int handle_array[MAX_PLAYERS];
    int num_devices = JslConnectDevices();
    num_devices = JslGetConnectedDeviceHandles(handle_array, MAX_PLAYERS);

    // Check for devices
    if (num_devices == 0)
    {
        std::cout << "No controllers found" << std::endl;
        gamepadConnected = false;
        if (poll.joinable()) poll.join();
        return false;
    }

    // Check if controller is connected; if not try to make connection to new controller
    for (int i = 0; i < num_devices; i++)
    {
        if (this->deviceID == handle_array[i])
        {
            return true;
        }
    }

    std::cout << "Change of controllers" << std::endl;
    deviceID = handle_array[0];

    // Start polling
    gamepadConnected = false;

    if (poll.joinable()) poll.join();

    gamepadConnected = true;
    poll = std::thread(&Overlay::paintLoop, this);

    return true;
}

void Overlay::paintLoop()
{
    while (gamepadConnected)
    {
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / refresh_rate));
    }
}
Overlay::~Overlay()
{
    gamepadConnected = false;
    poll.join();
    JslDisconnectAndDisposeAll();
}
void Overlay::paintButtons(QPaintDevice* device, QPoint corner, double scale)
{
    // using json = nlohmann::json;
    // const std::string filename = "assets/dualshock_black/placement.json";
    // std::ifstream reader(filename);
    // json j;
    // reader >> j;
    // reader.close();

    int buttons = JslGetButtons(deviceID);

    QPainter painter(device);
    QSvgRenderer renderer;

    std::unordered_map<int, std::pair<std::string, QPoint>> button_map = {
        {JSMASK_DOWN, {"dpad_down", {136, 255}}},
        {JSMASK_LEFT, {"dpad_left", {92, 226}}},
        {JSMASK_RIGHT, {"dpad_right", {165, 226}}},
        {JSMASK_UP, {"dpad_up", {136, 181}}},
        {JSMASK_HOME, {"home", {382, 344}}},
        {JSMASK_L, {"left_bumper", {109, 94}}},
        {JSMASK_LCLICK, {"left_stick_pressed", {228, 308}}},
        {JSMASK_ZL, {"left_trigger", {108, 0}}},
        {JSMASK_E, {"o_button", {682, 217}}},
        {JSMASK_R, {"right_bumper", {598, 94}}},
        {JSMASK_RCLICK, {"right_stick_pressed", {484, 308}}},
        {JSMASK_ZR, {"right_trigger", {597, 0}}},
        {JSMASK_W, {"square_button", {567, 217}}},
        {JSMASK_SHARE, {"share", {227, 142}}},
        {JSMASK_OPTIONS, {"options", {551, 142}}},
        {JSMASK_TOUCHPAD_CLICK, {"touchpad", {272, 122}}},
        {JSMASK_N, {"triangle_button", {629, 159}}},
        {JSMASK_S, {"x_button", {629, 276}}}};

    for (const auto& [mask, asset] : button_map)
    {
        if ((mask & buttons) != 0)
        {
            std::string filename = "assets/dualshock_black/" + asset.first + ".svg";

            renderer.load(QString(filename.c_str()));

            int width = (int)round((double)renderer.defaultSize().width() * scale);
            int height = (int)round((double)renderer.defaultSize().height() * scale);

            QPoint location = QPoint((int)round((double)asset.second.x() * scale) + corner.x(),
                                     (int)round((double)asset.second.y() * scale) + corner.y());

            QImage image(width, height, QImage::Format_ARGB32);
            image.fill(Qt::transparent);
            QPainter imagePainter(&image);
            renderer.render(&imagePainter);

            QPainter painter(device);
            painter.drawImage(location, image);
        }
    }

    // int buttons = JslGetButtons(deviceID);

    // if (buttons & JSMASK_UP)
    //     ;
    // QPainter painter(device);
    // QSvgRenderer renderer;

    // unordered_map<string, QPoint> icons = {{"dpad_down", {136, 255}},
    //                                        {"dpad_left", {92, 226}},
    //                                        {"dpad_right", {165, 226}},
    //                                        {"dpad_up", {136, 181}},
    //                                        {"home", {382, 344}},
    //                                        {"left_bumper", {109, 94}},
    //                                        {"left_stick_pressed", {228, 308}},
    //                                        {"left_trigger", {108, 0}},
    //                                        {"o_button", {682, 217}},
    //                                        {"right_bumper", {598, 94}},
    //                                        {"right_stick_pressed", {484, 308}},
    //                                        {"right_trigger", {597, 0}},
    //                                        {"square_button", {567, 217}},
    //                                        {"share", {227, 142}},
    //                                        {"options", {551, 142}},
    //                                        {"touchpad", {272, 122}},
    //                                        {"triangle_button", {629, 159}},
    //                                        {"x_button", {629, 276}}};

    // for (pair<string, QPoint> pair : icons)
    // {
    //     if (gamepad.getButtonState(pair.first))
    //     {
    //         string filename = "assets/overlay/" + pair.first + ".svg";
    //         renderer.load(QString(filename.c_str()));

    //         int width = (int)round((double)renderer.defaultSize().width() * scale);
    //         int height = (int)round((double)renderer.defaultSize().height() * scale);

    //         QPoint location = QPoint((int)round((double)pair.second.x() * scale) +
    //         corner.x(),
    //                                  (int)round((double)pair.second.y() * scale) +
    //                                  corner.y());

    //         QImage image(width, height, QImage::Format_ARGB32);
    //         image.fill(Qt::transparent);
    //         QPainter imagePainter(&image);
    //         renderer.render(&imagePainter);

    //         QPainter painter(device);
    //         painter.drawImage(location, image);
    //     }
}
