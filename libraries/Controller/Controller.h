#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <Com.h>
#include <Unit.h>
#include <string.h>

#define REQ_GET					0x0001
#define REQ_PUT					0x0002
#define REQ_OPEN				0x0004
#define REQ_CLOSE				0x0008
#define REQ_PAIR				0x0010
#define REQ_RESET				0x0020

#define REQ_HEAD_SIZE			8
#define REQ_SECRET				"VIRTDEVLOGIN"
#define BUF_SIZE				COM_MAX_LEN

typedef struct request {
	int len;
	int index;
	int flags;
	char *buf;
} req_t;

class Controller
{
public:
	void process(Com *com, Unit *unit);

private:
	void reset();
	char *getReplyBuf();
	int listen(Com *com);
	int getRequest(req_t *req);
	int pair(Com *com, Unit *unit);
	void reply(Com *com, size_t len);
	void procEvent(Com *com, Unit *unit);
	void procRequest(Com *com, Unit *unit);
	void checkDevice(Com *com, Device *device);
	const size_t getReplyBufSize();

private:
	int m_len;
	char m_buf[BUF_SIZE];
};

#endif
