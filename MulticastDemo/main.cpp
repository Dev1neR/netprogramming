#pragma comment(lib, "ws2_32.lib")
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#include <winsock.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define MCASTADDR "234.5.6.7"
#define MCASTPORT 25
#define BUFSIZE 10
#define BUFSIZE 10
#define DEFAULT_COUNT 50

BOOL bSender = FALSE, //ĳ��� �� ���������?
bLoopBack = FALSE; //���������� ����?

SOCKET gr_socket = INVALID_SOCKET; //�����
DWORD dwInterface, //���������
dwMulticastGroup, //������������� �����
dwCount; //�-�� ���������� ��� ��������/�������
short iPort; //����� �����
			 //����� ��������� ���������� ����� � ���������
			 //������ ���������� �����
void parse_cmd(int argc, char **argv);
//�������� ������
void exit_handler();
//������ ��� �������� ������������ ����� ������
#define CHECK_SET_OPT(opt_ret, err_msg)\
{\
  if ((opt_ret) < 0)\
  {\
    printf("setsockopt(%s) failed with: %d\n",\
           err_msg, WSAGetLastError());\
    return -1;\
  }\
}
//������ ��� �������� ��������-���������
#define CHECK_IO(io_ret, op_name)\
{\
  if ((io_ret) < 0)\
  {\
    printf("%s was failed with: %d\n",\
           op_name, WSAGetLastError());\
    return -1;\
  }\
}
//���� ���������, �� ���������, �� �������� ����������
//������ �� ����������.
int main(int argc, char **argv) {
	atexit(exit_handler);
	struct sockaddr_in local, remote, from;
	struct ip_mreq mcast;

	char recvbuf[BUFSIZE], sendbuf[BUFSIZE];
	int len = sizeof(struct sockaddr_in), optval, ret;
	DWORD i = 0;

	WSADATA ws;
	if (WSAStartup(MAKEWORD(1, 1), &ws) != 0) {
		printf("WSAStartup failed\n");
		return -1;
	}
	//����� ���������� �����, ������������ �������� Winsock
	parse_cmd(argc, argv);
	//��������� ������
	gr_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (gr_socket <= 0) {
		printf("socket failed with: %d\n", WSAGetLastError());
		return -1;
	}
	//�������� �� ����������
	local.sin_family = AF_INET; 
	local.sin_port = htons(iPort);
	local.sin_addr.s_addr = dwInterface;
	if (bind(gr_socket, (struct sockaddr*)&local, sizeof(local))) {
		printf("bind failed with: %d\n", WSAGetLastError());
		return -1;
	}
	//������������ ��������� im_req � ����������
	remote.sin_family = AF_INET;
	remote.sin_port = htons(iPort);
	remote.sin_addr.s_addr = dwMulticastGroup;

	mcast.imr_multiaddr.s_addr = dwMulticastGroup;
	mcast.imr_interface.s_addr = dwInterface;

	int opt_ret = setsockopt(gr_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP,
		(char *)&mcast, sizeof(mcast));
	CHECK_SET_OPT(opt_ret, "IP_ADD_MEMBERSHIP");
	//������������ �������� TTL, �� ������������� 1. optval = 8;
	opt_ret = setsockopt(gr_socket, IPPROTO_IP, IP_MULTICAST_TTL,
		(char*)&optval, sizeof(int));
	CHECK_SET_OPT(opt_ret, "IP_MULTICAST_TTL");
	//�������� ����, ���� �����.
	//� Windows NT4 � Windows 95 ����� ���������� �� �����.
	if (bLoopBack) {
		optval = 0;
		opt_ret = setsockopt(gr_socket, IPPROTO_IP, IP_MULTICAST_LOOP,
			(char *)&optval, sizeof(optval));
		CHECK_SET_OPT(opt_ret, "IP_MULTICAST_LOOP");
	}

	for (i = 0; i < dwCount; ++i)
	{
		if (!bSender) // ���������
		{// ������ ������ �����
			ret = recvfrom(gr_socket, recvbuf, BUFSIZE, 0,
				(struct sockaddr *)&from, &len);
			CHECK_IO(ret, "recvfrom");
			recvbuf[ret] = 0;
			printf("RECV: '%s' from <%s>\n", recvbuf,
				inet_ntoa(from.sin_addr));
		}
		else //³��������
		{//³������� ������ �����
			sprintf(sendbuf, "server 1: This is a test: %d", i);
			ret = sendto(gr_socket, (char*)sendbuf, strlen(sendbuf), 0,
				(struct sockaddr*)&remote, sizeof(remote));
			CHECK_IO(ret, "sendto");
			Sleep(500);
		}
	}

	//����� � �����
	opt_ret = setsockopt(gr_socket, IPPROTO_IP, IP_DROP_MEMBERSHIP,
		(char *)&mcast, sizeof(mcast));
	CHECK_SET_OPT(opt_ret, "IP_DROP_MEMBERSHIP");
	return 0;
}

void parse_cmd(int argc, char **argv) {
	int i;
	dwInterface = htonl(INADDR_ANY);
	dwMulticastGroup = inet_addr(MCASTADDR);
	iPort = MCASTPORT;
	dwCount = DEFAULT_COUNT;
	for (i = 1; i < argc; i++) {
		if ((argv[i][0] == '-') || (argv[i][0] == '/')) {
			switch (tolower(argv[i][1])) {
			case 's': // ³��������
				bSender = TRUE;
				break;
			case 'm': // ������������� �����
				if (strlen(argv[i]) > 3)
					dwMulticastGroup = inet_addr(&argv[i][3]);
				break;
			case 'i': // ���������
				if (strlen(argv[i]) > 3)
					dwInterface = inet_addr(&argv[i][3]);
				break;
			case 'p': // ����� �����
				if (strlen(argv[i]) > 3) iPort = atoi(&argv[i][3]);
				break;
			case 'l': // ���������� ��������� ����?
				bLoopBack = TRUE;
				break;
			case 'n': // ʳ������ ����������
				dwCount = atoi(&argv[i][3]);
				break;
			}
		}
	}
}

void exit_handler()
{
	if (gr_socket != INVALID_SOCKET)
	{
		closesocket(gr_socket);
	}
	if (WSACleanup())
	{
		printf("Error Winsock cleanup\n");
	}
}
