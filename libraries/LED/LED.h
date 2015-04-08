#ifndef _LED_H_
#define _LED_H_

#include "../Controller/Device.h"

class LED: public Device
{
public:
	LED(int pin):Device(pin) {}

public:
	void open();
	void close();
	void setup();

public:
	String info() {return itemInfo("LED", MODE_VISI | MODE_SWITCH, "", 0);}
};

#endif
