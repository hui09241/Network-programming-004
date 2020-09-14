#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include <time.h>
#define MAXLINE 1024    /* �r��w�İϪ��� */

void main()
{
	SOCKET	serv_sd, cli_sd;        /* socket �y�z�l */
  	int   	cli_len, n,i,j;
  	char  	str[MAXLINE]="1234",str_r[MAXLINE];
	clock_t start,end;
	long long int total=0;
	double time;
  	struct 	sockaddr_in   	serv, cli;
  	WSADATA wsadata;

    WSAStartup(0x101, &wsadata); //�I�s WSAStartup() ���U WinSock DLL ���ϥ�

  	serv_sd=socket(AF_INET, SOCK_STREAM, 0);// �}�� TCP socket

   	//���w socket �� IP ��}�M port number
   	serv.sin_family      = AF_INET;
   	serv.sin_addr.s_addr = 0;
   	serv.sin_port        = htons(5678);	// ���wport

    //bind(serv_sd, &serv, sizeof(serv)) ;
    bind(serv_sd, (LPSOCKADDR) &serv, sizeof(serv));

   	listen(serv_sd, 5) ; //�I�s listen() �� socket �i�J�u��ť�v���A

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
		   	n=recv(cli_sd, str_r, MAXLINE, 0); //��server����
		   	total = total + n;
		    printf("server recv: %d bytes, total:%d \n",n,total);
		   // sleep(3);
		   end=clock();
		     time=total/(end-start)/1000;
		   	printf("�����t�v�G%f MBytes\n",time);
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

	  		 n = send(cli_sd, str, MAXLINE, 0); //�ǰe
	 	 	 total = total + n;
	  		 printf( "server send:%d bytes, total:%d\n",n,total);
	  		 //sleep(3);
	  		 end=clock();
	  		  time=total/(end-start)/1000000000;
    		printf("�����t�v�G%f MBytes\n",time);
   			}
		}
		}

		closesocket(cli_sd);
		r++;
		if (r==2)
		   break;
	}
	//���� WinSock DLL ���ϥ�
   	closesocket(serv_sd);

   	WSACleanup();
   	system("pause");
}
