#ifndef _IRD_H_
#define _IRD_H_

#include "../Controller/Device.h"

class IRD: public Device
{
public:
	IRD(int pin);

public:
	bool loop();
	void setup();
	String info();
	int get(char *buf, size_t size);

private:
	int m_rounds;
	unsigned long m_time;
};

#endif
