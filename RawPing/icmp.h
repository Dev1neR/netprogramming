#ifndef _ICMP_
#define _ICMP_
#define IP_RECORD_ROUTE 0x7

#define ICMP_ECHO 8
#define ICMP_ECHOREPLY 0
#define ICMP_MIN 8 // ����� ICMP �� ����� 8 ���� (���������)

#define DEFAULT_PACKET_SIZE 32 // ����������� ����� ������
#define MAX_PACKET_SIZE 1024 // ������������ ����� ICMP -������
#define MAX_IP_HDR_SIZE 60 // ������������ �����

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long ulong_t;

// ��������� IP-���������
typedef struct _iphdr
{
	unsigned int h_len : 4; // ������� ���������
	unsigned int version : 4; // ����� IP
	uint8_t tos; // ��� ������
	uint16_t total_len; // ������ ����� ������
	uint16_t ident; // ��������� �������������
	uint16_t flags; // �������
	uint8_t ttl; // ��� �����
	uint8_t proto; // �������� (TCP, UDP � ���� ������)
	uint16_t checksum; // ���������� ���� IP
	ulong_t sourceIP;
	ulong_t destIP;
} IP_HEADER, *PIP_HEADER;

// ��������� ��������� ICMP
typedef struct _icmphdr
{
	uint8_t type;
	uint8_t code; // ��� �������
	uint16_t checksum;
	uint16_t id;
	uint16_t seq;
	ulong_t timestamp;
} ICMP_HEADER, *PICMP_HEADER;

// ���������� ��������� IP -
// ��������������� � ���������� IP_OPTIONS
typedef struct _ipoptionhdr
{
	uint8_t code; // ��� ���������
	uint8_t len; // ������� ����������� ���������
	uint8_t ptr; // ������� ����� ������
	ulong_t addr[9]; // ������ IP �����
} IP_OPTION_HEADER, *PIP_OPTION_HEADER;

// �������� ������� ���������� ���� ICMP-������
void fill_icmp_data(char*, int);
// �������� 16-����� ���� �����������
// ��� ��������� ������ �� ����������
uint16_t checksum(uint16_t*, int);
// ���� � ���������� ���������, ��������� � �����
// ��������� IP � �������� �������� ��������� ������ ��������
void decode_ip_opts(char*, int);
// ������ IP - ��������� ������ � �������
// ��� ����������� ����� ICMP.
void decode_icmp_hdr(char*, int, struct sockaddr_in*);
#endif //_ICMP_
