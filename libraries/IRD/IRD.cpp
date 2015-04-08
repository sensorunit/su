/*      IRD.cpp (Infrared Detector)
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

#include "IRD.h"

IRD::IRD(int pin):Device(pin)
{
	m_time = 0;
	m_rounds = 0;
}

String IRD::info()
{
	item_t range = itemNew("Enable", itemRange("False", "True"));
	
	return itemInfo("IRD", MODE_VISI | MODE_TRIG, range, 0);
}

void IRD::setup()
{
	pinMode(getIndex(), INPUT);
}

bool IRD::loop()
{
	const int rounds = 30;
	const int check_interval = 20;
	unsigned long time = millis();
	
	if (time - m_time < check_interval)
		return false;
	
	m_time = time;
	if (!digitalRead(getIndex()))
		m_rounds++;
	else
		m_rounds = 0;

	if (m_rounds == rounds) {
		m_rounds = 0;
		return true;
	}
	return false;
}

int IRD::get(char *buf, size_t size)
{
  item_t res = itemNew("Enable", "True");
  
  return itemCopy(res, buf, size);
}
