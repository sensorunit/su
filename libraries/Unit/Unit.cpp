/*      Unit.cpp
 *
 *      Copyright (C) 2014 Yi-Wei Ci <ciyiwei@hotmail.com>
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

#include "Unit.h"

Device *_notifier = NULL;

Unit::Unit()
{
	m_total = 0;
}

void Unit::setup()
{
	for (int i = 0; i < m_total; i++)
		m_list[i]->setup();
}

Device *Unit::get(int pos)
{
	if (pos >= 0 && pos < m_total)
		return m_list[pos];
	else
		return NULL;
}

Device *Unit::find(int index)
{
	for (int i = 0; i < m_total; i++)
		if (m_list[i]->getIndex() == index)
			return m_list[i];
	return NULL;
}

int Unit::add(Device *device)
{
	int ret;

	if (m_total == DEVICE_MAX)
		return -1;

	ret = m_total;
	m_list[m_total] = device;
	m_total++;
	return ret;
}

void Unit::open(int index)
{
	Device *device = get(index);

	if (device)
		return device->open();
}

void Unit::close(int index)
{
	Device *device = get(index);

	if (device)
		return device->close();
}

int Unit::remove(int index)
{
	int i;
	int pos = -1;

	if ((m_total == 0) || (index < 0))
		return -1;

	for (i = 0; i < m_total; i++) {
		if (m_list[i]->getIndex() == index) {
			pos = i;
			break;
		}
	}

	if (pos >= 0) {
		for (i = pos; i < m_total - 1; i++)
			m_list[i] = m_list[i + 1];
		m_total--;
	} else
		return -1;
	return 0;
}

int Unit::list(char *buf, size_t size)
{
	item_t res = itemFirst(String(m_list[0]->getIndex()), String(m_list[0]->name()));

	for (int i = 1; i < m_total; i++)
		res += item(String(m_list[i]->getIndex()), String(m_list[i]->name()));

	return itemGet(res, buf, size);
}

int Unit::count()
{
	return m_total;
}
