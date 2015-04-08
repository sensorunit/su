#ifndef _PUMP_H_
#define _PUMP_H_

#include "../Controller/Device.h"

class Pump: public Device
{
public:
	Pump(int pin):Device(pin) {}

public:
	void open();
	void close();
	void setup();
	String info();
};

#endif
