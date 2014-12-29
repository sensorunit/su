/*      Button.cpp
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

#include "Button.h"

Button::Button(int pin):Device(pin)
{
	m_time = 0;
	m_active = false;
}

void Button::setup()
{
	pinMode(getIndex(), INPUT);
}

int Button::loop()
{
	int ret = 0;
	unsigned long time = millis();

	if (time - m_time < BUTTON_INTERVAL)
		return 0;

	m_time = time;

	if (!digitalRead(getIndex())) {
		if (!m_active)
			m_active = true;
	} else {
		if (m_active) {
			m_active = false;
			ret = POLLIN;
		}
	}
	return ret;
}

int Button::get(char *buf, size_t size)
{
	item_t res = itemNew() + item("Enable", "True");

	return itemGet(res, buf, size);
}
