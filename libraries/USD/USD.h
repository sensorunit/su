#ifndef _USD_H_
#define _USD_H_

#include "../Device/Device.h"

#define USD_DISTANCE0	30
#define USD_DISTANCE1	70
#define USD_INTERVAL	20
#define USD_COUNT 		25
#define USD_HIT			10

class USD: public Device
{
public:
	USD(int pinTrig, int pinEcho);

public:
	int loop();
	void setup();
	int get(char *buf, size_t size);
	const char *name() {return "USD";}

private:
	int check();

private:
	int m_cnt;
	int m_hit;
	int m_pinTrig;
	int m_pinEcho;
	unsigned long m_time;
};

#endif
