#ifndef _RELAY_H_
#define _RELAY_H_

#include "../Device/Device.h"

class Relay: public Device
{
public:
	Relay(int pin):Device(pin) {}

public:
	void open();
	void close();
	void setup();
	const char *name() {return "RELAY";}
};

#endif
