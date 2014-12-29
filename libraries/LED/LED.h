#ifndef _LED_H_
#define _LED_H_

#include "../Device/Device.h"

class LED: public Device
{
public:
	LED(int pin):Device(pin) {}

public:
	void open();
	void close();
	void setup();

public:
	const char *name() {return "LED";}
};

#endif
