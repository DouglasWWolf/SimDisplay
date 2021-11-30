#include <iostream>
#include "is31fl3731.h"


IS31FL3731 display;

int main()
{
	display.init(0x74);

	display.print("AB");

	display.set_orientation(1);
	display.print("AB");
	
	display.set_orientation(0);
	display.set_brightness(100, true);
}
