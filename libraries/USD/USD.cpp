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
	m_cnt = 0;
	m_hit = 0;
	m_time = 0;
	m_pinTrig = pinTrig;
	m_pinEcho = pinEcho;
}

void USD::setup()
{
	pinMode(m_pinTrig, OUTPUT);
	pinMode(m_pinEcho, INPUT);
}

int USD::check()
{
	float distance;

	digitalWrite(m_pinTrig, LOW);
	delayMicroseconds(2);
	digitalWrite(m_pinTrig, HIGH);
	delayMicroseconds(10);
	digitalWrite(m_pinTrig, LOW);
	distance = pulseIn(m_pinEcho, HIGH) / 58.82;
	if ((distance > USD_DISTANCE0) && (distance < USD_DISTANCE1))
		return 1;
	else
		return 0;
}

int USD::loop()
{
	int ret = 0;
	unsigned long time = millis();

	if (time - m_time < USD_INTERVAL)
		return 0;

	m_time = time;
  
	if (m_cnt > 0)
		m_cnt++;

	if (check()) {
		if (!m_cnt) {
			m_cnt = 1;
			enableNotifier();
		}
		m_hit++;
	} 
	else if (!m_cnt)
		disableNotifier();

	if (m_cnt == USD_COUNT) {
		if (m_hit >= USD_HIT)
			ret = POLLIN;
		m_cnt = 0;
		m_hit = 0;
	}
    return ret;
}

int USD::get(char *buf, size_t size)
{
	item_t res = itemNew() + item("Enable", "True");
	
	return itemGet(res, buf, size);
}
