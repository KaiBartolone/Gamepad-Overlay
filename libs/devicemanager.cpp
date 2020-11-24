/**
 * @file devicemanager.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date November 2020
 */

#include <devicemanager.h>

#define MAX_STR 255

DeviceManager::DeviceManager()
{
    if (hid_init()) std::cerr << "HID initialization failed." << std::endl;
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

hid_device* DeviceManager::getDevice(int id)
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