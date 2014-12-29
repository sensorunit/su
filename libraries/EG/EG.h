#ifndef _EG_H_
#define _EG_H_

#include "../Device/Device.h"

#define EG_BLINK_TIMES		10
#define EG_BLINK_INTERVAL	2
#define EG_RESET_INTERVAL	5000

class EG: public Device
{
public:
	EG(int pin):Device(pin) {}

public:
	void open();
	void close();
	void setup();
	const char *name() {return "EG";}

private:
	void blink();

private:
	unsigned long m_time;
};

#endif
