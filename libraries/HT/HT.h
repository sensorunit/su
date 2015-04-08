#ifndef _HT_H_
#define _HT_H_

#include "../Controller/Device.h"

class HT: public Device
{
public:
	HT(int pin):Device(pin) {}

public:
	String info();
	int get(char *buf, size_t size);
};

#endif
