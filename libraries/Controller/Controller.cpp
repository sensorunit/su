/*      Controller.cpp
 *
 *      Copyright (C) 2014  Yi-Wei Ci <ciyiwei@hotmail.com>
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

#include "Controller.h"

void Controller::reply(Com *com, size_t len)
{
	if (len > 0) {
		m_buf[0] = '{';
		m_buf[len + 1] = '}';
		com->put(m_buf, len + 2);
	} else
		com->put(m_buf, 0);
}

char *Controller::getReplyBuf()
{
	return &m_buf[1];
}

const size_t Controller::getReplyBufSize()
{
	return BUF_SIZE - 2;
}

int Controller::getRequest(req_t *req)
{
	if (m_len < REQ_HEAD_SIZE)
		return -1;

	memcpy(&req->index, m_buf, 4);
	memcpy(&req->flags, &m_buf[4], 4);
	req->buf = &m_buf[REQ_HEAD_SIZE];
	req->len = m_len - REQ_HEAD_SIZE;
	return 0;
}

int Controller::pair(Com *com, Unit *unit)
{
	int len;

	if (strncmp(&m_buf[REQ_HEAD_SIZE], REQ_SECRET, strlen(REQ_SECRET)))
		return -1;

	len = unit->list(getReplyBuf(), getReplyBufSize());
	if (len < 0)
		return -1;

	reply(com, len);
	com->makeReady();
	return 0;
}

int Controller::listen(Com *com)
{
	int ret = com->get(m_buf, BUF_SIZE);

	if (ret > 0) {
		m_len = ret;
		return 0;
	} else
		return -1;
}

void Controller::procEvent(Com *com, Unit *unit)
{
	int total;

	if(!com->ready())
		return;

	total = unit->count();
	for (int i = 0; i < total; i++) {
		Device *device = unit->get(i);
		int ret = device->loop();

		if (ret == POLLIN) {
			int len = device->get(getReplyBuf(), getReplyBufSize());

			if (len > 0)
				reply(com, len);
		}
	}
}

void Controller::reset()
{
	void (*func)(void) = 0; 
	func();
}

void Controller::procRequest(Com *com, Unit *unit)
{
	req_t req;
	Device *device;

	if (listen(com) < 0)
		return;

	if (getRequest(&req) < 0)
		return;

	if (req.flags & REQ_PAIR) {
		if (!com->ready())
			pair(com, unit);
		return;
	} else if (req.flags & REQ_RESET) {
		reset();
		return;
	}
	
	if(!com->ready())
		return;

	device = unit->find(req.index);
	if (!device)
		return;

	if (req.flags & REQ_OPEN) {
    	device->open();
	} else if (req.flags & REQ_GET) {
		int len = device->get(getReplyBuf(), getReplyBufSize());
		reply(com, len);
	} else if (req.flags & REQ_PUT) {
		int len = device->put(req.buf, req.len, getReplyBuf(), getReplyBufSize());
		reply(com, len);
	} else if (req.flags & REQ_CLOSE) {
		device->close();
	}
}

void Controller::process(Com *com, Unit *unit)
{
	procRequest(com, unit);
	procEvent(com, unit);
}
