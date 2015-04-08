#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "Arduino.h"
#include "Notifier.h"
#include "Item.h"

#define MODE_POLL	0x0010
#define MODE_TRIG	0x0020
#define MODE_SYNC	0x0040
#define MODE_VISI	0x0080
#define MODE_SWITCH	0x0200
#define MODE_IN		0x0400
#define MODE_OUT	0x0800

class Device
{
public:
	Device(int index) {m_index = index;}

public:
	virtual void open() {}
	virtual void close() {}
	virtual void setup() {}
	virtual bool loop() {return false;}
	virtual int get(char *buf, size_t size) {return 0;}
	virtual String info() {return itemInfo("Unknown", 0, "", 0);}
	virtual int put(char *in, size_t inlen, char *out, size_t outlen) {return 0;}

public:
	int getIndex() {return m_index;}

private:
	int m_index;
};

#endif
