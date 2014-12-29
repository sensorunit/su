/*      EG.cpp (Entrance Guard)
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

#include "EG.h"

void EG::setup()
{
	m_time = 0;
	pinMode(getIndex(), OUTPUT);
}

void EG::blink()
{
	for (int i = 0; i < EG_BLINK_TIMES; i++) {
		enableNotifier();
		delay(EG_BLINK_INTERVAL);
		disableNotifier();
		delay(EG_BLINK_INTERVAL);
	}
}
void EG::open()
{
	unsigned long time = millis();
	
	if (time - m_time > EG_RESET_INTERVAL) {
		digitalWrite(getIndex(), HIGH);
		blink();
		digitalWrite(getIndex(), LOW);
		m_time = time;
	}
}

void EG::close()
{
	digitalWrite(getIndex(), LOW);
}
