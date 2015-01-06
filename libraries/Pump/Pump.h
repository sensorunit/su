#ifndef _PUMP_H_
#define _PUMP_H_

#include "../Device/Device.h"

#define PUMP_DELAY 	2000

class Pump: public Device
{
public:
	Pump(int pin):Device(pin) {}

public:
	void open();
	void close();
	void setup();
	const char *name() {return "Pump";}
};

#endif
