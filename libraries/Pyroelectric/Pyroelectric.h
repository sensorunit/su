#ifndef _PYROELECTRIC_H_
#define _PYROELECTRIC_H_

#include "../Controller/Device.h"

class Pyroelectric: public Device
{
public:
	Pyroelectric(int pin);

public:
	bool loop();
	void setup();
	String info();
	int get(char *buf, size_t size);

private:
	bool check();

private:
	int m_status;
	unsigned long m_time;
};

#endif
