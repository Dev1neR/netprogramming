#ifndef _PING_HLP_
#define _PING_HLP_

#include <string.h>
#include "icmp.h"

//��������� ��� ����� ���������� �����
typedef struct _ping_cmd_opts {
	unsigned int packet_size;
	int record_route;
	int timeout;
	int ping_count;
} PING_CMD_OPTIONS, *PPING_CMD_OPTIONS;

#define SET_DEF_CMD_OPTS(cmd_opts)\
{\
  memset(&cmd_opts, 0, sizeof(cmd_opts));\
  cmd_opts.packet_size = DEFAULT_PACKET_SIZE;\
  cmd_opts.record_route = 0;\
  cmd_opts.timeout = 1000;\
  cmd_opts.ping_count = 4;\
}
//���� ������� ��������
#define EPARSE_CMD_COUNT -2
#define EPARSE_CMD_ANY -1
#define EPARSE_CMD_OK 0

//������� ����� ������� ping
//����� ����������� ����� ����� 
void parse_cmd_opts(const char*, PPING_CMD_OPTIONS);
//������� ��� ��������� ���������� �����
int parse_cmd(int argc, char* argv[], char*, PPING_CMD_OPTIONS);
#endif //_PING_HLP_
