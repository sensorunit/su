#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../Controller/Device.h"

class Light: public Device
{
public:
	Light(int pin):Device(pin) {}

public:
	String info();
	int get(char *buf, size_t size);
};

#endif
