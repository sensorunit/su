#ifndef _RELAY_H_
#define _RELAY_H_

#include "../Controller/Device.h"

class Relay: public Device
{
public:
	Relay(int pin):Device(pin) {}

public:
	void open();
	void close();
	void setup();
	String info();
};

#endif
