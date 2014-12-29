/*      Com.cpp
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

#include "Com.h"
#include "CRC.h"
#include "Arduino.h"

Com::Com()
{
	m_ch = 0;
	m_count = 0;
	m_ready = 0;
	m_start = 0;
}

void Com::makeReady()
{
	m_ready = 1;
}

void Com::setup()
{
	Serial.begin(COM_RATE);
	Serial.setTimeout(COM_TIMEOUT);
}

int Com::ready()
{
	return m_ready;
}

int Com::recv()
{
	char ch;
	int ret = -1;

	if (!Serial.available())
		return ret;

	ch = Serial.read();
	if (COM_DLE == m_ch) {
		if (COM_STX == ch) {
			m_count = 0;
			m_start = 1;
		} else if (COM_ETX == ch) {
			if (m_start) {
				m_start = 0;
				if (m_count >= CRC_SIZE)
					ret = m_count;
			}
		} else if (COM_DLE == ch) {
			if (m_start) {
				if (COM_MAX_LEN == m_count) {
					m_start = 0;
				} else {
					m_buf[m_count] = ch;
					m_count++;
				}
			}
		}
	} else if (m_start && (ch != COM_DLE)) {
		if (COM_MAX_LEN == m_count) {
			m_start = 0;
		} else {
			m_buf[m_count] = ch;
			m_count++;
		}
	}
	m_ch = ch;
	return ret;
}

int Com::get(char *buf, int length)
{
	int size = recv();

	if ((size < CRC_SIZE) || (size > length))
		return -1;
	else {
		crc_t code;
		CRC crc = CRC();

		size -= CRC_SIZE;
		code = crc.encode(&m_buf[CRC_SIZE], size);
		if (code == *((crc_t *)m_buf)) {
			memcpy(buf, &m_buf[CRC_SIZE], size);
			return size;
		} else
			return -1;
	}
}

void Com::send(char *buf, int length)
{
	int i;

	for (i = 0; i < length; i++) {
		Serial.write(buf[i]);
		if (COM_DLE == buf[i])
			Serial.write(COM_DLE);
	}
}

void Com::sendBytes(char *buf, int length)
{
	for (int i = 0; i < length; i++)
		Serial.write(buf[i]);
}

void Com::put(char *buf, int length)
{
	CRC crc = CRC();
	crc_t code = crc.encode(buf, length);

	sendBytes(COM_HEAD, COM_HEAD_LEN);
	send((char *)&code, sizeof(crc_t));
	send(buf, length);
	sendBytes(COM_TAIL, COM_TAIL_LEN);
}
