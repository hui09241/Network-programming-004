#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024    /* 字串緩衝區長度 */

void main()
{
	SOCKET	serv_sd, cli_sd;        /* socket 描述子 */
  	int   	cli_len, n,i,j;
  	char  	str[MAXLINE]="1234",str_r[MAXLINE];
	clock_t start,end;
	long long int total=0;
	double time;
  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;

    WSAStartup(0x101, &wsadata); //呼叫 WSAStartup() 註冊 WinSock DLL 的使用

  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// 開啟 TCP socket

   	//指定 socket 的 IP 位址和 port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// 指定port

    //bind(serv_sd, &serv, sizeof(serv)) ;
    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

   	listen(serv_sd, 5) ; //呼叫 listen() 使 socket 進入「監聽」狀態

   	int r=0;
   	while(1) {

	   	cli_len = sizeof(cli);
		printf("server waits for client\n");
		cli_sd=accept(serv_sd, (LPSOCKADDR) &cli, &cli_len);
		if (r==0)
		{
			total=0;
		start=clock();
		sleep(1);
		for(j=0;j<1024;j++)
		{
			for(i=0;i<1024;i++){
		   	n=recv(cli_sd, str_r, MAXLINE, 0); //由server接收
		   	total = total + n;
		    printf("server recv: %d bytes, total:%d \n",n,total);
		   // sleep(3);
		   end=clock();
		     time=total/(end-start)/1000;
		   	printf("接收速率：%f MBytes\n",time);
		}
		}


		}
		//	closesocket(cli_sd);

		if(r==1)
		{
			total=0;
			start=clock();
			sleep(1);
				for(j=0;j<1024;j++)
		{
			for(i=0;i<1024;i++)
   			{

	  		 n = send(cli_sd, str, MAXLINE, 0); //傳送
	 	 	 total = total + n;
	  		 printf( "server send:%d bytes, total:%d\n",n,total);
	  		 //sleep(3);
	  		 end=clock();
	  		  time=total/(end-start)/1000000000;
    		printf("接收速率：%f MBytes\n",time);
   			}
		}
		}

		closesocket(cli_sd);
		r++;
		if (r==2)
		   break;
	}
	//結束 WinSock DLL 的使用
   	closesocket(serv_sd);

   	WSACleanup();
   	system("pause");
}
