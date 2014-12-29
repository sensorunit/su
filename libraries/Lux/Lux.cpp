/*      Lux.cpp
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
#include "Lux.h"

Lux::Lux(int pin): Device(pin)
{
	Wire.begin();
}

int Lux::check()
{
	int i = 0;
	byte buf[2];

	Wire.beginTransmission(LUX_ADDR);
	Wire.write(0x10);
	Wire.endTransmission();
	Wire.beginTransmission(LUX_ADDR);
	Wire.requestFrom(LUX_ADDR, 2);
	while(Wire.available()) {
		buf[i] = Wire.read();
		i++;
		if (2 == i)
			break;
	}
	Wire.endTransmission();
	if(2 == i)
		return (int)(((buf[0] << 8) | buf[1]) / 1.2);
	else
		return 0;
}

int Lux::get(char *buf, size_t size)
{
	int lx = check();
	item_t res = itemNew();
	
	res += item("Lx", String(lx));
	return itemGet(res, buf, size);
}
