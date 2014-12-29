/*      TH.cpp (Temperature & Humidity)
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

#include "TH.h"

int TH::get(char *buf, size_t size)
{
	uint8_t cnt = 7;
	uint8_t idx = 0;
	uint8_t data[5];
	item_t res = itemNew();
	unsigned int loopCnt = 10000;

	for(int i = 0; i < 5; i++)
		data[i] = 0;

	pinMode(getIndex(), OUTPUT);
	digitalWrite(getIndex(), LOW);
	delay(18);
	digitalWrite(getIndex(), HIGH);
	delayMicroseconds(HOST_WAIT_TIME);
	pinMode(getIndex(), INPUT);

	loopCnt = 10000;
	while(digitalRead(getIndex()) == LOW)
		if (loopCnt-- == 0)
			return 0;

	loopCnt = 10000;
	while(digitalRead(getIndex()) == HIGH)
		if (loopCnt-- == 0)
			return 0;

	for(int bits = 0; bits < 40; bits++) {
		loopCnt = 10000;
		while(digitalRead(getIndex()) == LOW)
			if (loopCnt-- == 0)
				return 0;

		unsigned long t = micros();

		loopCnt = 10000;
		while(digitalRead(getIndex()) == HIGH)
			if (loopCnt-- == 0)
				return 0;

		if ((micros() - t) > 40)
			data[idx] |= (1 << cnt);

		if (cnt == 0) {
			cnt = 7;
			idx++;
		} else
			cnt--;
	}

	delayMicroseconds(PRE_DATA_TIME * 2);
	pinMode(getIndex(), OUTPUT);
	digitalWrite(getIndex(), HIGH);

	if(data[4] != data[0] + data[2])
		return 0;

	res += item("T", String(data[2]));
	res += item("H", String(data[0]));
	return itemGet(res, buf, size);
}
