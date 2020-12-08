#include "common_utils.h"
using namespace std;
	int main(int argc,char* argv[]){
		//Буфер повідомлень
		char dataBuffer[BUFFER_SIZE];
		SOCKET receiveSocket;
		struct sockaddr_in senderAddr;
		struct sockaddr_in receiveAddr;
		#ifdef OS_WINDOWS
		int senderAddrLen = sizeof(senderAddr);
		#else
	
		unsigned int senderAddrLen = sizeof(senderAddr);
		#endif
		int nPort = 5150;
		char strPort[6];
		//Отримуємо порт серверу з командного рядка
		if (getParameter(argv,argc,"-port",strPort,’:’)){
			int tempPort = atoi(strPort);
			if (tempPort>0)
				nPort = tempPort;
			else {
				cout<<"\nError command argument "<<argv[0]<<";
				cout<<"-port:<integer value>\n";
				cout<<"\nUsage "<<argv[0]<<" -port:<integer value>\n";
			}
		}
		memset(&senderAddr,0,sizeof(senderAddr));
		memset(&receiveAddr,0,sizeof(receiveAddr));
		if (initSocketAPI()){
			return socketError(TRUE,"init socket API");
		}
		//Створюємо слухаючий сокет
		if ((receiveSocket=socket(AF_INET,SOCK_DGRAM,
		IPPROTO_UDP))<=0){
			return socketError(TRUE,"create socket",TRUE);
		}
		//Заповнюємо структуру receiveAddr для зв’язування
		//функцією bind
		receiveAddr.sin_family = AF_INET;
		//Переходимо до мережевого порядку байт
		receiveAddr.sin_port = htons(nPort);
		//Вказуємо адресу серверу
		receiveAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(receiveSocket,(struct sockaddr*)&receiveAddr,
			sizeof(receiveAddr))!=0){
				closeSocket(receiveSocket);
				return socketError(TRUE,"bind socket",TRUE);
			}
			printInfo(argv[0]);
			cout<<"Ready incoming messages..."<<endl;
			do{
				int nRec=0;
				do{
					nRec=recvfrom(receiveSocket,dataBuffer, BUFFER_SIZE,0,
					(sockaddr*)&senderAddr,&senderAddrLen);
					dataBuffer[nRec]=‘\0’;
					if (stricmp(dataBuffer,disconnetClientCmd) && nRec>0){
						cout<<"["<<inet_ntoa(senderAddr.sin_addr)<<":";
						cout<<ntohs(senderAddr.sin_port)<<"] "<<" ";
						cout<<dataBuffer<<endl;
					}
					
					if (sendto(receiveSocket, dataBuffer, nRec_len, 0, (sockaddr*)&senderAddr, senderAddrLen) == SOCKET_ERROR)
					{
						printf("sendto() failed with error code : %d", WSAGetLastError());
						exit(EXIT_FAILURE);
					}
					else {
						cout << "Disconnect client [";
						cout<<inet_ntoa(senderAddr.sin_addr)<<":"
						cout<<ntohs(senderAddr.sin_port)<<"]\n";
						break;
					}
				}while(1);
			}while (1);
			//Закриваємо сокет і звільняємо системні ресурси
			closeSocket(receiveSocket);
			deinitSocketAPI();
			return 0;
	}
