#ifndef _TV_H_
#define _TV_H_

#include "../Controller/Device.h"

class TV: public Device
{
public:
	TV(int pin):Device(pin) {}

public:
	void open();
	void close();
	void setup();
	String info();
};

#endif
