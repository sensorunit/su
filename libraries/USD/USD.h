#ifndef _USD_H_
#define _USD_H_

#include "../Controller/Device.h"

class USD: public Device
{
public:
	USD(int pinTrig, int pinEcho);

public:
	bool loop();
	void setup();
	String info();
	int get(char *buf, size_t size);

private:
	bool check();

private:
	int m_hits;
	int m_rounds;
	int m_pinTrig;
	int m_pinEcho;
	unsigned long m_time;
};

#endif
