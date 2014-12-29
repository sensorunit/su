#ifndef _TV_H_
#define _TV_H_

#include "../Device/Device.h"
#define TV_DELAY 	50

class TV: public Device
{
public:
	TV(int pin):Device(pin) {}

public:
	void open();
	void close();
	void setup();
	const char *name() {return "TV";}
};

#endif
