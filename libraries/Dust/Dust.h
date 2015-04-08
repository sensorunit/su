#ifndef _DUST_H_
#define _DUST_H_

#include "../Controller/Device.h"

class Dust: public Device
{
public:
	Dust(int pin);

public:
	String info();
	int get(char *buf, size_t size);

private:
	int m_result;
	unsigned long m_lo;
	unsigned long m_time;
};

#endif