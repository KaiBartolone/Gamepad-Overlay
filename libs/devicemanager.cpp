/**
 * @file devicemanager.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date November 2020
 */

#include <devicemanager.h>

#define MAX_STR 255
#define MAX_PATH_LENGTH 260

DeviceManager::DeviceManager()
{
    if (hid_init())
    {
        std::cerr << "HID initialization failed." << std::endl;
        throw;
    }
}

DeviceManager::~DeviceManager() { hid_exit(); }

void DeviceManager::listDevices()
{
    struct hid_device_info *devs, *cur_dev;

    // Grab starting dev
    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;

    // Iterate through devs and printout information
    while (cur_dev)
    {
        printf("\n----------\n");
        printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
               cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
        printf("\n");
        printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
        printf("  Product:      %ls\n", cur_dev->product_string);
        printf("  Release:      %hx\n", cur_dev->release_number);
        printf("  Interface:    %d\n", cur_dev->interface_number);
        printf("  Usage (page): 0x%hx (0x%hx)\n", cur_dev->usage, cur_dev->usage_page);
        cur_dev = cur_dev->next;
    }
    printf("\n");

    hid_free_enumeration(devs); // Free memory for dev information
}

hid_device *DeviceManager::getDevice(unsigned short id)
{
    struct hid_device_info *devs, *cur_dev;

    // Grab starting dev
    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;

    // Iterate through devs information
    while (cur_dev)
    {
        if (id == cur_dev->product_id)
        {
            // Return open device and free memory for devs information
            hid_device *handle = DeviceManager::open(cur_dev->path, false);
            hid_free_enumeration(devs);
            return handle;
        }

        cur_dev = cur_dev->next;
    }

    hid_free_enumeration(devs); // Free memory for dev information
    return nullptr;
}

hid_device *DeviceManager::getDevice(std::string product)
{
    struct hid_device_info *devs, *cur_dev;

    // Grab starting dev
    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;

    // Convert string to wide c string
    std::wstring widestr = std::wstring(product.begin(), product.end());
    const wchar_t *widecstr = widestr.c_str();

    // Iterate through devs information
    while (cur_dev)
    {
        if (wcscmp(widecstr, cur_dev->product_string) == 0)
        {
            // Return open device and free memory for devs information
            hid_device *handle = DeviceManager::open(cur_dev->path, false);
            hid_free_enumeration(devs);
            return handle;
        }

        cur_dev = cur_dev->next;
    }

    hid_free_enumeration(devs); // Free memory for dev information
    return nullptr;
}

void DeviceManager::close(hid_device *handle)
{
    hid_close(handle);
}

hid_device *DeviceManager::open(char *path, bool blocking)
{
    hid_device *handle = hid_open_path(path);
    if (handle != nullptr)
        hid_set_nonblocking(handle, !blocking);

    return handle;
}