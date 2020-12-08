#include "multi_thread_server.h"
#define BUFFER_SIZE 256
THREAD_RESULT handle_connection(void* data) {
	SOCKET socket;
	char dataBuffer[BUFFER_SIZE];
	CHECK_IO((socket = *((SOCKET*)data)) > 0, (THREAD_RESULT)-1, "Invalid socket\n");
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	CHECK_IO(!getpeername(socket, (sockaddr*)&addr, &addr_len), (THREAD_RESULT)-1, "Error retrieving peer info\n");
	char* str_in_addr = inet_ntoa(addr.sin_addr);
	printf("[%s:%d]>>%s\n", str_in_addr, ntohs(addr.sin_port), "Establish new connection");
	do{
		int nRec=0;
		do{
			nRec=recvfrom(socket,dataBuffer, BUFFER_SIZE,0,
			(sockaddr*)&addr,&addr_len);
			dataBuffer[nRec]=‘\0’;
			if (stricmp(dataBuffer,disconnetClientCmd) && nRec>0){
				cout<<"["<<inet_ntoa(addr.sin_addr)<<":";
				cout<<ntohs(addr.sin_port)<<"] "<<" ";
				cout<<dataBuffer<<endl;
			}
					
			if (sendto(socket, dataBuffer, nRec_len, 0, (sockaddr*)&addr, addr_len) == SOCKET_ERROR)
			{
				printf("sendto() failed with error code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}
			else {
				cout << "Disconnect client [";
				cout<<inet_ntoa(addr.sin_addr)<<":"
				cout<<ntohs(addr.sin_port)<<"]\n";
				break;
			}
		}while(1);
	}while (1);
	close_socket(socket);
	printf("[%s:%d]>>%s\n", str_in_addr,ntohs(addr.sin_port), "Close incoming connection");
	return 0;
}