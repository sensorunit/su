#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../Device/Device.h"

#define LIGHT_THRESHOLD 200

class Light: public Device
{
public:
	Light(int pin):Device(pin) {}

public:
	int put(char *in, size_t inlen, char *out, size_t outlen);
	const char *name() {return "Light";}

private:
	int check();

private:
	int m_close;
	int m_active;
};

#endif
