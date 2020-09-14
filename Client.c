#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024

int main(int argc, char** argv) {

   SOCKET        	sd;
   struct sockaddr_in serv;
   char  		str[1024];
   char  		str_r[1024];
   WSADATA 		wsadata;

   int n,i,j,t=0;
   long long int total=0;
   double time;
   clock_t start,end;
   memset(str,"1",MAXLINE);

   WSAStartup(0x101,(LPWSADATA) &wsadata); // �I�s WSAStartup() ���U WinSock DLL ���ϥ�



   sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.

   serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);

   connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server

	start=clock(); //�ǰe
	sleep(1);
	total=0;
	for(j=0;j<1024;j++)
	{
		for(i=0;i<1024;i++)
   		{

	   n = send(sd, str, MAXLINE, 0); //�ǰe
	   total = total + n;
	   printf( "client send:%d bytes, total:%d\n",n,total);
	   end=clock();
	   time=total/(end-start)/1000;
		printf("�ǿ�t�v�G%f MBytes\n",time);
	   //sleep(3);

   		}
	}
   	/*end=clock();
	printf("�ǿ�t�v�G%f MBytes\n",total/(end-start)1000000000);*/

    closesocket(sd); //����TCP socket
    sd=socket(AF_INET, SOCK_STREAM, 0); //�}�Ҥ@�� TCP socket.
    serv.sin_family       = AF_INET;
   serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
   serv.sin_port         = htons(5678);
	connect(sd, (LPSOCKADDR) &serv, sizeof(serv)); // �s���� echo server

	start=clock();
	sleep(1);
	total=0;
	for(j=0;j<1024;j++)
	{
		for(i=0;i<1024;i++)
   		{

	   n = recv(sd, str, MAXLINE, 0); //�ǰe
	   total = total + n;
	   printf( "client recv:%d bytes, total:%d\n",n,total);
	   //sleep(3);
	   end=clock();
	   time=total/(end-start)/1000;
    	printf("�����t�v�G%f MBytes\n",time);
   		}
	}
	closesocket(sd); //����TCP socket

   WSACleanup();  // ���� WinSock DLL ���ϥ�
   system("pause");

   return 0;
}
