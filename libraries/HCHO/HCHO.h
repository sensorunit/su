#ifndef _HCHO_H_
#define _HCHO_H_

#include "../Controller/Device.h"

class HCHO: public Device
{
public:
	HCHO(int pin):Device(pin) {}

public:
	String info();
	int get(char *buf, size_t size);
};

#endif
