#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")//��̬����ws2_32.lib
typedef unsigned char uint_8t;
typedef unsigned int  uint_16t;
typedef unsigned long uint_32t;

WSADATA wsa;
WSAStartup(MAKEWORD(2, 0), &wsa);	//��ʼ��WS2_32.DLL

SOCKET ServerSocket;
SOCKET ClientSocket;
SOCKADDR_IN ServerAddr;//��������ַ
SOCKADDR_IN ClientAddr;//�ͻ��˵�ַ

int Creat_TCP_Sever()
{
	int ret;

	/*����������ļ�������*/
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket <= 0X00) {
		printf(" �׽��ֽ���ʧ�ܣ�\n");
		return -1;
	}
	/*��������ַ��ֵ*/
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(8000); //1024 ~49151����ͨ�û�ע��Ķ˿ں�
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	bzero(ServerAddr, sizeof(ServerAddr));

	/*���׽����ļ����������ַ��Ϣ�������*/
	ret = bind(ServerSocket, (SOCKADDR*)ServerAddr, sizeof(ServerSocket));
	if (ret < 0) {
		printf("�׽������ַ��ʧ�ܣ�\n");
		return -1��
	}

	printf("��ʼ�����豸!\n");
	ret = listen(ServerSocket, 3);
	if (ret != 0) {
		printf("�����豸ʧ��!\n");
		return -1;
	}

	printf("�������ӣ�\n");
	ClientSocket = accept(ServerSocket, (SOCKADDR*)ClientAddr, sizeof(ClientAddr));
	if (ClientSocket <= 0) {
		printf("�����豸ʧ��!\n");
		return -1;
	}
}



void main()
{
	char RevBuf[128]; 
	char SendBuf[128];
	uint8_t RevLengh = 128;
	uint8_t SendLengh = 128;

	
	while (1) {
		Creat_TCP_Sever();
		
		ret = recv(ClientSocket, RevBuf, RevLengh, 0);
		printf("���յ������ݣ�%s,���յ��ĳ��ȣ�%x", Recv, RevLengh);
		if (ret <= 0) {
			printf("�ر����ӣ�\n")
				return -1;
		}
		printf("�����뷢�͸��ͻ��˵��ַ�:\n");
		scanf("%s", buf);
		if (send(ClientSocket, buf, strlen(buf) + 1, 0) <= 0)
		{
			printf("���ʹ���!\n");
		}
		
	}
	closesocket(ClientSocket);

}

