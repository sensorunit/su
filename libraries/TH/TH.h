#ifndef _TH_H_
#define _TH_H_

#include "../Device/Device.h"

#define HOST_START_TIME		20  // ms
#define HOST_WAIT_TIME 		40
#define PRE_DATA_TIME			50  // us
#define TIME_OUT					200

class TH: public Device
{
public:
	TH(int pin):Device(pin) {}

public:
	int get(char *buf, size_t size);
	const char *name() {return "TH";}
};

#endif
