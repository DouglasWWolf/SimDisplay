//=============================================================================================
// is31fl3731.h - Defines a two-character display driver for the IS31FL3731 Led Matrix
//=============================================================================================
#ifndef _IS31FL3731_H_
#define _IS31FL3731_H_

#include <stdint.h>

class IS31FL3731
{
public:

    // Call this once at program startup to initialize the device
    void    init(int i2c_address, unsigned char brightness = 255);

    // Call this to set the brightness of an "on" LED
    void    set_brightness(unsigned char brightness, bool update_display = false);

    // Call this to determine the display orientation.  0 = Normal, 1 = Upside down
    void    set_orientation(int orientation) { m_orientation = orientation; }

    // Call this to draw a vertical bar in a given column
    void    vertical_bar(int column, bool update_display = true);

    // Call this to print a pair of characters
    void    print(char c1, char c2);

    // Call this to print a two digit integer
    void    print(int);

    // Call this to print a rounded two-digit floating point number
    void    print(double);

    // Call this to print a 2-character string
    void    print(const char*);

protected:

    // This is a generic routine that transmits to the device via I2C
    void    transmit(const unsigned char* data, size_t length);

    // This updates a single 8-bit register on the device
    void    write_reg(unsigned char address, unsigned char value);

    // Sends the bitmap to the device
    void    display_image();

    // Displays a single character
    void    print(int row, int col, uint8_t c);

    // The number of columns and rows that our bitmap and the device can handle
    enum { MAX_COLS = 16, MAX_ROWS = 9};

    // The number of physical LEDs that we have
    enum { PHYS_COLS = 15, PHYS_ROWS = 7};

    // A 16x9 bitmap of the display
    uint16_t m_bitmap[MAX_ROWS];

    // This is the value that will be PWM'd for an LED that is on
    unsigned char m_brightness;

    // Display orientation: 0 = normal, 1 = flip it upside down
    int m_orientation;

    // The I2C address of the device we're controlling
    unsigned char m_i2c_address;
};

#endif