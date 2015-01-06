#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "../Device/Device.h"
#define BUZZER_FREQUENCY    5000

class Buzzer: public Device
{
public:
	Buzzer(int pin):Device(pin) {}

public:
	void open();
	void close();
	void setup();

public:
	const char *name() {return "Buzzer";}
};

#endif
