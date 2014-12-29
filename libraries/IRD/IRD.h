#ifndef _IRD_H_
#define _IRD_H_

#include "../Device/Device.h"

#define IRD_COUNT 		30
#define IRD_INTERVAL	20

class IRD: public Device
{
public:
	IRD(int pin);

public:
	int loop();
	void setup();
	int get(char *buf, size_t size);
	const char *name() {return "IRD";}

private:
	int m_cnt;
	unsigned long m_time;
};

#endif
