#ifndef _HCHO_H_
#define _HCHO_H_

#include "../Device/Device.h"

class HCHO: public Device
{
public:
	HCHO(int pin):Device(pin) {}

public:
	int get(char *buf, size_t size);
	const char *name() {return "HCHO";}
};

#endif
