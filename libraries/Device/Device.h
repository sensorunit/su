#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "Arduino.h"

#define POLLIN 0x01

class Device
{
public:
	Device(int pin) {m_index=pin;}

public:
	virtual void open() {}
	virtual void close() {}
	virtual void setup() {}
	virtual int loop() {return 0;}
	virtual int get(char *buf, size_t size) {return 0;}
	virtual int put(char *in, size_t inlen, char *out, size_t outlen) {return 0;}
	virtual const char *name() {return "Unknown";}

public:
	int getIndex() {return m_index;}

private:
	int m_index;
};

extern Device *_notifier;

#define enableNotifier() do { \
	if (_notifier) \
		_notifier->open(); \
} while (0)

#define disableNotifier() do { \
	if (_notifier) \
		_notifier->close(); \
} while (0)

#define itemNew() (String("'_i':'") + getIndex() + "'")
#define itemFirst(key, value) (String("'") + key + "':'" + value + "'")
#define item(key, value) (String(", '") + key + "':'" + value + "'")
#define setNotifier(notifier) do {_notifier = notifier;} while (0)
#define isEnabled(buf, buflen) (buflen == 18 ? strncmp("{'Enable': 'True'}", buf, 18) == 0 : false)

static inline int itemGet(String &item, char *buf, size_t size)
{
	item.toCharArray(buf, size);
	return item.length();
}

typedef String item_t;

#endif
