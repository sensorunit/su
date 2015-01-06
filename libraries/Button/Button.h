#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "../Device/Device.h"

#define BUTTON_INTERVAL	10

class Button: public Device
{
public:
	Button(int pin);

public:
	int loop();
	void setup();
	int get(char *buf, size_t size);
	const char *name() {return "Button";}

private:
	bool m_active;
	unsigned long m_time;
};

#endif
