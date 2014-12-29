#ifndef _UNIT_H_
#define _UNIT_H_

#define DEVICE_MAX 16

#include "../Device/Device.h"

class Unit
{
public:
	Unit();

public:
	int count();
	void setup();
	void open(int index);
	void close(int index);
	int remove(int index);
	int add(Device *device);
	int list(char *buf, size_t size);
	Device *find(int index);
	Device *get(int pos);

private:
	int m_total;
	Device *m_list[DEVICE_MAX];
};

#endif
