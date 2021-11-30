#include "Wire.h"
#include <stdio.h>
CWire Wire;

#define BANK_SELECT_REG 0xFD
#define PWM_BASE_REG    0x24

#define PHYS_COLS  15
#define PHYS_ROWS   7
#define LAST_LED_INDEX (16 * (PHYS_ROWS-1) + PHYS_COLS - 1)

class CLedMatrix
{
public:
    CLedMatrix() { m_bank = m_bank0; }

    void	write_reg(unsigned char address, unsigned char value);

    void	show_matrix();

protected:

    unsigned char* m_bank;

    unsigned char m_bank0[256];
    unsigned char m_bank9[256];

} LedMatrix;


static char led_char(int c)
{
    if (c == 0x00) return ' ';
    if (c <= 0x40) return '.';
    if (c <= 0x80) return ':';
    return '*';
}


void CLedMatrix::show_matrix()
{
    printf("\n");
    printf("#################\n");
    for (int row = 0; row < PHYS_ROWS; ++row)
    {
        unsigned char address = PWM_BASE_REG + (row * 16);

        printf("#");
        for (int col = 0; col < PHYS_COLS; ++col)
        {
            int c = m_bank0[address++];
            printf("%c",led_char(c));
        }
        printf("#\n");
    }
    printf("#################\n");

}


void CLedMatrix::write_reg(unsigned char address, unsigned char value)
{
    // If the caller wants to switch which frame bank we're writing to...
    if (address == BANK_SELECT_REG)
    {
        m_bank0[address] = value;
        m_bank9[address] = value;
        m_bank = (value == 0x0B) ? m_bank9 : m_bank0;
        return;
    }

    // This this value to this address (in the current bank)
    m_bank[address] = value;

    // If we are writing to the last PWM register, show the display
    if (address == PWM_BASE_REG + LAST_LED_INDEX) show();
}




size_t CWire::write(const uint8_t* data, size_t count)
{
    if (count < 2) return count;

    unsigned char address = *data++;

    while (--count)
    {
        LedMatrix.write_reg(address++, *data++);
    }

    return count;
}

void show()
{
    LedMatrix.show_matrix();
}