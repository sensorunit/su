#ifndef _SPRINKLER_H_
#define _SPRINKLER_H_

#include "../Device/Device.h"

#define SPRINKLER_DELAY			3000
#define SPRINKLER_SOIL_MOISTURE 1023

class Sprinkler: public Device
{
public:
	Sprinkler(int pinSM, int pinPump);

public:
	void open();
	void setup();
	int get(char *buf, size_t size);
	const char *name() {return "Sprinkler";}

private:
	int m_pinSM;
	int m_pinPump;
};

#endif
