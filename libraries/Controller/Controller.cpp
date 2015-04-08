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

Device *_notifier = NULL;

Controller::Controller()
{
	m_len = 0;
	m_total = 0;
	m_mount = false;
}

void Controller::setup()
{
	m_comm.setup();
	for (int i = 0; i < m_total; i++)
		m_devices[i]->setup();
}


int Controller::add(Device *device)
{
	if (m_total == DEVICE_MAX)
		return -1;
	
	m_devices[m_total] = device;
	m_total++;
	return 0;
}

void Controller::reply(Device *device, size_t len)
{
	if (len > 0) {
		item_t key = itemKey(device->getIndex());
		
		m_rep[key.length() + len + 2] = '}';
		m_rep[key.length() + len + 3] = '}';
		m_comm.put(m_rep, key.length() + len + 4);
	} else
		m_comm.put(m_rep, 0);
}

char *Controller::getReplyBuf(Device *device)
{
	int len;
	int index = device->getIndex();
	item_t key = itemKey(index);
	
	m_rep[0] = '{';
	key.toCharArray(&m_rep[1], REP_SIZE - 1);
	len = 1 + key.length();
	m_rep[len] = '{';
	return &m_rep[len + 1];
}

const size_t Controller::getReplyBufSize(Device *device)
{
	item_t key = itemKey(device->getIndex());
	
	return REP_SIZE - 4 - key.length();
}

int Controller::getRequest(req_t *req)
{
	if (m_len < REQ_HEAD_SIZE)
		return -1;

	memcpy(&req->index, m_req, 4);
	memcpy(&req->flags, &m_req[4], 4);
	req->buf = &m_req[REQ_HEAD_SIZE];
	req->len = m_len - REQ_HEAD_SIZE;
	return 0;
}

void Controller::getDeviceInfo()
{
	int len;
	int index;
	item_t key;
	item_t info;
	
	m_rep[0] = '{';
	index = m_devices[0]->getIndex();
	key = itemKey(index);
	key.toCharArray(&m_rep[1], REP_SIZE - 1);
	len = 1 + key.length();
	info = m_devices[0]->info();
	info.toCharArray(&m_rep[len], REP_SIZE - len);
	len += info.length();
	for (int i = 1; i < m_total; i++) {
		index = m_devices[i]->getIndex();
		key = itemKeyNext(index);
		key.toCharArray(&m_rep[len], REP_SIZE - len);
		len += key.length();
		info = m_devices[i]->info();
		info.toCharArray(&m_rep[len], REP_SIZE - len);
		len += info.length(); 
	}
	m_rep[len] = '}';
	m_comm.put(m_rep, len + 1);
}

void Controller::mount()
{
	int len;

	if (strncmp(&m_req[REQ_HEAD_SIZE], REQ_SECRET, strlen(REQ_SECRET)))
		return;

	getDeviceInfo();
	m_mount = true;
}

int Controller::listen()
{
	int ret = m_comm.get(m_req, REQ_SIZE);

	if (ret > 0) {
		m_len = ret;
		return 0;
	} else
		return -1;
}

void Controller::checkEvent()
{
	if(!m_mount)
		return;
	
	for (int i = 0; i < m_total; i++) {
		Device *device = m_devices[i];
		
		if (device->loop()) {
			int len = device->get(getReplyBuf(device), getReplyBufSize(device));

			if (len > 0)
				reply(device, len);
		}
	}
}

void Controller::reset()
{
	void (*func)(void) = 0;
	
	m_mount = false;
	func();
}

Device *Controller::find(int index)
{
	for (int i = 0; i < m_total; i++)
		if (m_devices[i]->getIndex() == index)
			return m_devices[i];
	return NULL;
}

void Controller::checkRequest()
{
	int len;
	req_t req;
	Device *device;

	if (listen() < 0)
		return;

	if (getRequest(&req) < 0)
		return;

	if (req.flags & REQ_MOUNT) {
		mount();
		return;
	} else if (req.flags & REQ_RESET) {
		reset();
		return;
	}
	
	if(!m_mount)
		return;

	device = find(req.index);
	if (!device)
		return;

	if (req.flags & REQ_OPEN) {
    	device->open();
	} else if (req.flags & REQ_GET) {
		len = device->get(getReplyBuf(device), getReplyBufSize(device));
		reply(device, len);
	} else if (req.flags & REQ_PUT) {
		len = device->put(req.buf, req.len, getReplyBuf(device), getReplyBufSize(device));
		reply(device, len);
	} else if (req.flags & REQ_CLOSE) {
		device->close();
	}
}

void Controller::proc()
{
	checkRequest();
	checkEvent();
}
