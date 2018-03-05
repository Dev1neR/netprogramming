#ifndef _ICMP_
#define _ICMP_
#define IP_RECORD_ROUTE 0x7

#define ICMP_ECHO 8
#define ICMP_ECHOREPLY 0
#define ICMP_MIN 8 // ����� ICMP �� ����� 8 ���� (���������)

#define DEFAULT_PACKET_SIZE 32 // ����������� ����� ������
#define MAX_PACKET_SIZE 1024 // ������������ ����� ICMP -������
#define MAX_IP_HDR_SIZE 60 // ������������ �����

// ��������� IP-���������
typedef struct _iphdr
{
	unsigned int h_len : 4; // ������� ���������
	unsigned int version : 4; // ����� IP
	unsigned char tos; // ��� ������
	unsigned short total_len; // ������ ����� ������
	unsigned short ident; // ��������� �������������
	unsigned short flags; // �������
	unsigned char ttl; // ��� �����
	unsigned char proto; // �������� (TCP, UDP � ���� ������)
	unsigned short checksum; // ���������� ���� IP
	unsigned long sourceIP;
	unsigned long destIP;
} IP_HEADER, *PIP_HEADER;

// ��������� ��������� ICMP
typedef struct _icmphdr
{
	unsigned char type;
	unsigned char code; // ��� �������
	unsigned short checksum;
	unsigned short id;
	unsigned short seq;
	unsigned long timestamp;
} ICMP_HEADER, *PICMP_HEADER;

// ���������� ��������� IP -
// ��������������� � ���������� IP_OPTIONS
typedef struct _ipoptionhdr
{
	unsigned char code; // ��� ���������
	unsigned char len; // ������� ����������� ���������
	unsigned char ptr; // ������� ����� ������
	unsigned long addr[9]; // ������ IP �����
} IP_OPTION_HEADER, *PIP_OPTION_HEADER;

// �������� ������� ���������� ���� ICMP-������
void fill_icmp_data(char*, int);
// �������� 16-����� ���� �����������
// ��� ��������� ������ �� ����������
unsigned short checksum(unsigned short*, int);
// ���� � ���������� ���������, ��������� � �����
// ��������� IP � �������� �������� ��������� ������ ��������
void decode_ip_opts(char*, int);
// ������ IP - ��������� ������ � �������
// ��� ����������� ����� ICMP.
void decode_icmp_hdr(char*, int, struct sockaddr_in*);
#endif //_ICMP_
