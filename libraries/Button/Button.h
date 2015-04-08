#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "../Controller/Device.h"

class Button: public Device
{
public:
	Button(int pin);

public:
	bool loop();
	void setup();
	String info();
	int get(char *buf, size_t size);

private:
	bool m_active;
	unsigned long m_time;
};

#endif
