#ifndef _SOILMOISTURE_H_
#define _SOILMOISTURE_H_

#include "../Controller/Device.h"

#define SOILMOISTURE_MAX 1023

class SoilMoisture: public Device
{
public:
	SoilMoisture(int pin):Device(pin) {}

public:
	String info();
	int get(char *buf, size_t size);
};

#endif
