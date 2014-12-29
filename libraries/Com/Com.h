#ifndef _COM_H_
#define _COM_H_

#include <string.h>

#define COM_DLE 	'@'
#define COM_STX 	'0'
#define COM_ETX 	'1'
#define COM_CHR 	"@@"
#define COM_HEAD 	"@0"
#define COM_TAIL 	"@1"

#define COM_RATE 	9600
#define COM_MAX_LEN 256
#define COM_TIMEOUT 100
#define COM_WRITEBACK

const int COM_HEAD_LEN = strlen(COM_HEAD);
const int COM_TAIL_LEN = strlen(COM_TAIL);

class Com
{
public:
	Com();
	int ready();
	int get(char *buf, int length);
	void put(char *buf, int length);
	void makeReady();
	void setup();

private:
	int recv();
	void send(char *buf, int length);
	void sendBytes(char *buf, int length);

private:
	int m_ready;
	int m_count;
	int m_start;
	char m_ch;
	char m_buf[COM_MAX_LEN];
};

#endif
