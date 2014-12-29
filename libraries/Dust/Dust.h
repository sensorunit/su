#ifndef _DUST_H_
#define _DUST_H_

#include "../Device/Device.h"
#define DUST_INTERVAL  30000

class Dust: public Device
{
public:
	Dust(int pin);

public:
	int get(char *buf, size_t size);
	const char *name() {return "Dust";}

private:
	int m_result;
	unsigned long m_lo;
	unsigned long m_time;
};

#endif