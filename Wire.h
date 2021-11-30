#pragma once
#include <stdint.h>

class CWire
{
public:

	void	begin() {};
	void	setClock(uint32_t) {};
	void	beginTransmission(unsigned char address) {};
	size_t	write(const uint8_t*, size_t);
	void	flush() {};
	uint8_t endTransmission() { return 0; }


};

extern CWire Wire;

void show();

