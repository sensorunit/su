/*      HT.cpp (Humidity and Temperature)
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

#include "HT.h"

String HT::info()
{
	item_t range = itemNew("H", itemRange(0, 100)) + itemNext("T", itemRange(0, 100));
	
	return itemInfo("HT", MODE_POLL | MODE_SYNC | MODE_VISI | MODE_OUT, range, 0.01);
}

int HT::get(char *buf, size_t size)
{
	item_t res;
	uint8_t cnt = 7;
	uint8_t idx = 0;
	uint8_t data[5];
	unsigned int loopCnt = 10000;

	for(int i = 0; i < 5; i++)
		data[i] = 0;

	pinMode(getIndex(), OUTPUT);
	digitalWrite(getIndex(), LOW);
	delay(18);
	digitalWrite(getIndex(), HIGH);
	delayMicroseconds(40);
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

	delayMicroseconds(100);
	pinMode(getIndex(), OUTPUT);
	digitalWrite(getIndex(), HIGH);

	if(data[4] != data[0] + data[2])
		return 0;

	res = itemNew("H", String(data[0]));
	res += itemNext("T", String(data[2]));
	return itemCopy(res, buf, size);
}
