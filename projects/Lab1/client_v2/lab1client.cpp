#include "common_utils.h"
using namespace std;
#define BUFLEN 512
int main(int argc,char* argv[]){
	//Буфер повідомлень
	char dataBuffer[BUFFER_SIZE];
	SOCKET sendSocket;
	struct sockaddr_in receiveAddr;
	char receiveName[256];
	strcpy(receiveName,"localhost");
	char buf[BUFLEN];
	int nPort = 5150;
	//Отримуємо сервер та порт підключення з командного рядка
	getServerAndPort(argv,argc,receiveName,&nPort);
	memset(&receiveAddr,0,sizeof(receiveAddr));
	if (initSocketAPI()){
		return socketError(TRUE,"init socket API");
	}
	//Створюємо слухаючий сокет
	if ((sendSocket=socket(AF_INET,SOCK_DGRAM,
		IPPROTO_UDP))<=0){
			return socketError(TRUE,"socket create",TRUE);
		}
		//Заповнюємо структуру receiveAddr для зв’язування
		//функцією bind
		receiveAddr.sin_family = AF_INET;
		//Переходимо до мережевого порядку байт
		receiveAddr.sin_port = htons(nPort);
		//Вказуємо адресу серверу
		struct hostent* hptr;
		hptr = gethostbyname(receiveName);
		memcpy(&receiveAddr.sin_addr.s_addr,
		hptr->h_addr_list[0],hptr->h_length);
		printInfo(argv[0],NULL,FALSE);
		do{
			cout<<"Enter a message: ";
			cin.getline(dataBuffer,BUFFER_SIZE);
			int nSend=0;
			if ((nSend=sendto(sendSocket,dataBuffer,
				strlen(dataBuffer),0,
				(sockaddr*)&receiveAddr,
				sizeof(receiveAddr)))<=0){
					closeSocket(sendSocket);
						return socketError(TRUE,"sending",TRUE);
				}
				
			
			memset(buf, '\0', BUFLEN);

			if (recvfrom(sendSocket, dataBuffer, BUFLEN, 0, (sockaddr*)&receiveAddr, &slen) == SOCKET_ERROR)
			{
				printf("recvfrom() failed with error code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}

			puts(buf);
		}while (stricmp(dataBuffer,disconnetClientCmd)!=0);
		//Закриваємо сокет і звільняємо системні ресурси
		closeSocket(sendSocket);
		deinitSocketAPI();
		return 0;
}
