/*      Pyroelectric.cpp
 *
 *      Copyright (C) 2014  Yanpeng Li <lyp40293@gmail.com>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include "Pyroelectric.h"

Pyroelectric::Pyroelectric(int pin):Device(pin)
{
	m_time = 0;
	m_status = 0;
}

void Pyroelectric::setup()
{
	pinMode(getIndex(), INPUT);
}

int Pyroelectric::check()
{
	if(HIGH == digitalRead(getIndex())) {
		enableNotifier();
		return 1;
	} else {
		disableNotifier();
		return 0;
	}
}

int Pyroelectric::loop()
{
	int status;
	unsigned long time = millis();

	if (time - m_time < PYROELECTRIC_INTERVAL)
		return 0;

	m_time = time;
	status = check();
	if (status != m_status) {
		m_status = status;
		return POLLIN;
	}
	return 0;
}

int Pyroelectric::get(char *buf, size_t size)
{
  	item_t res = itemNew();

	if (m_status)
		res += item("Enable", "True");
	else
		res += item("Enable", "False");

	return itemGet(res, buf, size);
}
