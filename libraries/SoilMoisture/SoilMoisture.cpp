/*      SoilMoisture.cpp 
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

#include "SoilMoisture.h"

String SoilMoisture::info()
{
	item_t range = itemNew("SM", itemRange(0, 100));
	
	return itemInfo("SoilMoisture", MODE_POLL | MODE_SYNC | MODE_VISI | MODE_OUT, range, 0.01);
}

int SoilMoisture::get(char *buf, size_t size)
{
	item_t res;
	int val = analogRead(getIndex());
	
	if (val < SOILMOISTURE_MAX)
		val = (SOILMOISTURE_MAX - val) * 100 / SOILMOISTURE_MAX;
	else
		val = 0;
	
	res = itemNew("SM", String(val));
	return itemCopy(res, buf, size);
}
