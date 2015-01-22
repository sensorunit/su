#ifndef _SM_H_
#define _SM_H_

#include "../Device/Device.h"

#define SM_MAX 1023

class SM: public Device
{
public:
	SM(int pin):Device(pin) {}

public:
	int get(char *buf, size_t size);
	const char *name() {return "SM";}
};

#endif
