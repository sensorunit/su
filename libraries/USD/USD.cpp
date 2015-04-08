/*      USD.cpp (Ultrasonic Detector)
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

#include "USD.h"

USD::USD(int pinTrig, int pinEcho):Device(pinTrig)
{
	m_hits = 0;
	m_time = 0;
	m_rounds = 0;
	m_pinTrig = pinTrig;
	m_pinEcho = pinEcho;
}

String USD::info()
{
	item_t range = itemNew("Enable", itemRange("False", "True"));
	
	return itemInfo("USD", MODE_VISI | MODE_TRIG, range, 0);
}

void USD::setup()
{
	pinMode(m_pinTrig, OUTPUT);
	pinMode(m_pinEcho, INPUT);
}

bool USD::check()
{
	float distance;
	const int d0 = 30;
	const int d1 = 70;

	digitalWrite(m_pinTrig, LOW);
	delayMicroseconds(2);
	digitalWrite(m_pinTrig, HIGH);
	delayMicroseconds(10);
	digitalWrite(m_pinTrig, LOW);
	distance = pulseIn(m_pinEcho, HIGH) / 58.82;
	if ((distance > d0) && (distance < d1))
		return true;
	else
		return false;
}

bool USD::loop()
{
	const int hits = 10;
	const int rounds = 25;
	unsigned long time = millis();
	const int check_interval = 20;

	if (time - m_time < check_interval)
		return false;

	m_time = time;
  
	if (m_rounds > 0)
		m_rounds++;

	if (check()) {
		if (!m_rounds) {
			m_hits = 1;
			m_rounds = 1;
			enableNotifier();
		} else
			m_hits++;
	} 
	else if (!m_rounds)
		disableNotifier();

	if (m_rounds == rounds) {
		m_rounds = 0;
		if (m_hits >= hits)
			return true;
	}
    return false;
}

int USD::get(char *buf, size_t size)
{
	item_t res = itemNew("Enable", "True");
	
	return itemCopy(res, buf, size);
}
