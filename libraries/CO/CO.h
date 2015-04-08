#ifndef _CO_H_
#define _CO_H_

#include "../Controller/Device.h"

class CO: public Device
{
public:
	CO(int pin):Device(pin) {}

public:
	String info();
	int get(char *buf, size_t size);
};

#endif
