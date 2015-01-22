#ifndef _PYROELECTRIC_H_
#define _PYROELECTRIC_H_

#include "../Device/Device.h"

#define PYROELECTRIC_INTERVAL		20

class Pyroelectric: public Device
{
public:
	Pyroelectric(int pin);

public:
	int loop();
	void setup();
	int get(char *buf, size_t size);
	const char *name() {return "PYROELECTRIC";}

private:
	int check();

private:
	int m_status;
	unsigned long m_time;
};

#endif
