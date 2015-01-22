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
	m_cnt = 0;
	m_time = 0;
}

void IRD::setup()
{
	pinMode(getIndex(), INPUT);
}

int IRD::loop()
{
	int ret = 0;
	unsigned long time = millis();

	if (time - m_time < IRD_INTERVAL)
		return 0;
	
	m_time = time;

	if (!digitalRead(getIndex()))
		m_cnt++;
	else
		m_cnt = 0;

	if (m_cnt == IRD_COUNT) {
		m_cnt = 0;
		ret = POLLIN;
	}
	return ret;
}

int IRD::get(char *buf, size_t size)
{
  item_t res = itemNew() + item("Enable", "True");
  
  return itemGet(res, buf, size);
}
