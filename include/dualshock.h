/**
 * @file dualshock.h
 * -----------------------------
 * @author Bartolone, Kai
 * @date November 2020
 */

#ifndef DUALSHOCK_H
#define DUALSHOCK_H

#include <hidapi.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <thread>

// Event Enumerations
enum ds_button
{

};

// Struct definitions for dualshock data
typedef struct
{
    int x;
    int y;
} gyro_state;

typedef struct
{
    int x;
    int y;
} touch_state;

typedef struct
{
    int x;
    int y;
} motion_state;

typedef struct
{
    unsigned char r, g, b;
} color_t;

class Dualshock
{
public:
    Dualshock();
    ~Dualshock();

    /**
     * @fn getId
     * ----------
     * @return: device id
     */
    void getId();

    /**
     * @fn setLed
     * ----------
     * @description: Attempts to set the color of the dualshock's led.
     */
    void setLed(unsigned char r, unsigned char g, unsigned char b);

    /**
 * @fn getMotionState
 * ----------
 * @return: motion state of controller
 */
    motion_state getMotionState();

    /**
     * @fn rumble
     * @description: Sends command to dualshock to rumble.
     */
    void rumble(int frequency, uint8_t intensity);

private:
    hid_device *handle;
    color_t color = {0, 0, 0xff}; // Default color is blue
    bool usb = false;
    bool isPolling = false;
    std::thread thread;

    // Private Functions
private:
    /**
     * @fn clear
     * ----------
     * @description: Resets dualshock data to their default values.
     */
    void clear();

    /** 
     * @fn get_device
     * ----------
     * @description: Searches for device with product id or 
     * @param id: product id
     * @param product: name of product
     * @return: hid_device or null if no device is found with matching information
     */
    hid_device *get_device(unsigned short id);
    hid_device *get_device(std::string product);

    /**
     * @fn poll
     * ----------
     * @description: Polls the dualshock controller for events and updates dualshock class.
     */
    void poll();

    /**
     * @fn send_command
     * ----------
     * @description: Sends command to dualshock controller.
     * @param data: see https://www.psdevwiki.com/ps4/DS4-BT for structure of message
     */
    bool send_command(int command, uint8_t *data, size_t len);

    /**
     * @fn release_bt
     * ----------
     * @description: Resets light and rumble on bluetooth dualshock.
     */
    void release_bt();

    /**
     * @fn release_usb
     * ----------
     * @description: Resets light and rumble on usb dualshock.
     */
    void release_usb();

    /**
     * @fn release
     * ----------
     * @description: Resets light and rumble on connected dualshock.
     */
    void release();

    /**
     * @fn hid_exchange
     * ----------
     * @description: Writes buffer and reads 64 bytes of response for timeout of 1000ms.
     * @return: error code of hid_read_timeout or number of bytes read
     */
    int hid_exchange(hid_device *handle, uint8_t *buf, size_t len);

    /**
     * @fn enable_gyro
     * ----------
     * @description: Writes data to enable gyro readout from dualshock.
     */
    void enable_gyro(uint8_t *buf, int bufLength);

    /**
     * @fn init_usb
     * ----------
     * @description:
     */
    void init_usb();

    /**
     * @fn init_bt
     * ----------
     * @description:
     */
    void init_bt();

    /**
     * @fn init
     * ----------
     * @description:
     */
    void init();

    /**
     * @fn send_command
     * ----------
     * @description:
     */
    int send_command(int command, uint8_t *data, int len)
}
#endif // DUALSHOCK_H
