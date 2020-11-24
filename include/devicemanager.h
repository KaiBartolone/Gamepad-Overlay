/**
 * @file devicemanager.h
 * -----------------------------
 * @author Bartolone, Kai
 * @date November 2020
 */

#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <hidapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <wchar.h>

class DeviceManager
{
  public:
    DeviceManager();
    ~DeviceManager();

    /**
     * @fn listDevices
     * -----------------
     * @description: Prints out hid device information (Manufacturer, Product, Release, Interface,
     * and Usage).
     */
    void listDevices();

    /**
     * @fn getDevice
     * -----------------
     * @description: Searches for hid device with product id or product type.
     * @returns: first device with matching product id or product type
     */
    hid_device* getDevice(int id);
    hid_device* getDevice(std::string product);
};

#endif // DEVICEMANAGER_H