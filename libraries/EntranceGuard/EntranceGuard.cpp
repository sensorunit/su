/*      EntranceGuard.cpp
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

#include "EntranceGuard.h"

String EntranceGuard::info()
{
	item_t range = itemNew("Enable", itemRange("False", "True"));
	
	return itemInfo("EntranceGuard", MODE_VISI | MODE_SWITCH, range, 0);
}

void EntranceGuard::setup()
{
	m_time = 0;
	pinMode(getIndex(), OUTPUT);
}

void EntranceGuard::flash()
{
	const int times = 10;
	const int interval = 2;
	
	for (int i = 0; i < times; i++) {
		enableNotifier();
		delay(interval);
		disableNotifier();
		delay(interval);
	}
}
void EntranceGuard::open()
{
	unsigned long time = millis();
	unsigned long interval = 5000;
	
	if (time - m_time > interval) {
		digitalWrite(getIndex(), HIGH);
		flash();
		digitalWrite(getIndex(), LOW);
		m_time = time;
	}
}

void EntranceGuard::close()
{
	digitalWrite(getIndex(), LOW);
}
