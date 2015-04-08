#ifndef _COMM_H_
#define _COMM_H_

#include <string.h>

#define COMM_DLE 	'@'
#define COMM_STX 	'0'
#define COMM_ETX 	'1'
#define COMM_CHR 	"@@"
#define COMM_HEAD 	"@0"
#define COMM_TAIL 	"@1"

#define COMM_RATE 	9600
#define COMM_MAX_LEN 64
#define COMM_TIMEOUT 100

const int COMM_HEAD_LEN = strlen(COMM_HEAD);
const int COMM_TAIL_LEN = strlen(COMM_TAIL);

class Comm
{
public:
	Comm();
	void setup();
	int get(char *buf, int length);
	void put(char *buf, int length);

private:
	int recv();
	void send(char *buf, int length);
	void sendBytes(char *buf, int length);

private:
	char m_ch;
	int m_count;
	int m_start;
	char m_buf[COMM_MAX_LEN];
};

#endif
