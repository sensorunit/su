#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <Comm.h>
#include <Device.h>

#define REQ_GET					0x0001
#define REQ_PUT					0x0002
#define REQ_OPEN				0x0004
#define REQ_CLOSE				0x0008
#define REQ_MOUNT				0x0010
#define REQ_RESET				0x0020

#define REQ_HEAD_SIZE			8
#define DEVICE_MAX 				16
#define REQ_SECRET				"VIRTDEVLOGIN"
#define REQ_SIZE				COMM_MAX_LEN
#define REP_SIZE				192

typedef struct request {
	int len;
	int index;
	int flags;
	char *buf;
} req_t;

class Controller
{
public:
	Controller();
	void proc();
	void setup();
	int add(Device *device);

private:
	int listen();
	void reset();
	void mount();
	void checkEvent();
	void checkRequest();
	void getDeviceInfo();
	Device *find(int index);
	int getRequest(req_t *req);
	char *getReplyBuf(Device *device);
	void reply(Device *device, size_t len);
	const size_t getReplyBufSize(Device *device);

private:
	int m_len;
	int m_total;
	Comm m_comm;
	bool m_mount;
	char m_req[REQ_SIZE];
	char m_rep[REP_SIZE];
	Device *m_devices[DEVICE_MAX];
};

#endif
