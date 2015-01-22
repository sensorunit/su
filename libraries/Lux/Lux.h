#ifndef _LUX_H_
#define _LUX_H_

#include "../Device/Device.h"
#include <Wire.h>

#define LUX_ADDR	0x23

class Lux: public Device
{
public:
	Lux(int pin);

public:
	int get(char *buf, size_t size);
	const char *name() {return "LUX";}

private:
	int check();
};

#endif
