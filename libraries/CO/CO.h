#ifndef _CO_H_
#define _CO_H_

#include "../Device/Device.h"

class CO: public Device
{
public:
	CO(int pin):Device(pin) {}

public:
	int get(char *buf, size_t size);
	const char *name() {return "CO";}
};

#endif
