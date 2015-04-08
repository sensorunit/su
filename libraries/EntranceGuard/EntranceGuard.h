#ifndef _ENTRANCEGUARD_H_
#define _ENTRANCEGUARD_H_

#include "../Controller/Device.h"

class EntranceGuard: public Device
{
public:
	EntranceGuard(int pin):Device(pin) {}

public:
	void open();
	void close();
	void setup();
	String info();

private:
	void flash();

private:
	unsigned long m_time;
};

#endif
