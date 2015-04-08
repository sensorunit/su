#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "../Controller/Device.h"

class Buzzer: public Device
{
public:
	Buzzer(int pin):Device(pin) {}

public:
	void open();
	void close();
	void setup();
	String info();
};

#endif
