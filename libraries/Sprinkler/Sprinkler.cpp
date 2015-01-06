/*      Sprinkler.cpp
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

#include "Sprinkler.h"

Sprinkler::Sprinkler(int pinSM, int pinPump):Device(pinPump)
{
	m_pinSM = pinSM;
	m_pinPump = pinPump;
}

void Sprinkler::setup()
{
	pinMode(m_pinPump, OUTPUT);
	digitalWrite(m_pinPump, HIGH);
}

void Sprinkler::open()
{
	digitalWrite(m_pinPump, LOW);
	delay(SPRINKLER_DELAY);
	digitalWrite(m_pinPump, HIGH);
}

void Sprinkler::close()
{
	digitalWrite(m_pinPump, HIGH);
}

int Sprinkler::get(char *buf, size_t size)
{
	item_t res = itemNew();
	int sm = analogRead(m_pinSM);
	
	if (sm < SPRINKLER_SOIL_MOISTURE)
		sm = (SPRINKLER_SOIL_MOISTURE - sm) / float(SPRINKLER_SOIL_MOISTURE)  * 100;
	else
		sm = 0;
	res += item("SM", String(sm));
	return itemGet(res, buf, size);
}
