#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<winsock2.h>
#include<sys/types.h>
#include<My_TCP_Sever.h>
#include <time.h>

#include "Windows.h"

static	SOCKET ServerSocket;
static	SOCKET ClientSocket;
static	SOCKADDR_IN ServerAddr;//��������ַ
static	SOCKADDR_IN ClientAddr;//�ͻ��˵�ַ

int Get_TCP_State(void )
{
	int Tcp_Sta;
	int Tcp_Sta_Len = sizeof(Tcp_Sta);
	int ret;
	ret = getsockopt(ServerSocket, SOL_SOCKET , SO_KEEPALIVE , (char*)&Tcp_Sta , &Tcp_Sta_Len );

	if (ret < 0) {
		printf("SO_KEEPALIVE Value : %d \n", Tcp_Sta);
		printf("������������ \n");
		return -1;
	}
	return 1;
	//printf( "�ӵ�һ������ %s ������/n", inet_ntoa( ClientAddr.sin_addr));
}

int Creat_TCP_Sever( void)
{
	int len;
	uint8_t ret;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 0), &wsa);	//��ʼ��WS2_32.DLL

	/*����������ļ�������*/
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket <= 0X00) {
		printf(" �׽��ֽ���ʧ�ܣ�\n");
		return -1;
	}
	/*��������ַ��ֵ*/
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(8100); //1024 ~49151����ͨ�û�ע��Ķ˿ں�
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	/*���׽����ļ����������ַ��Ϣ�������*/
	ret = bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if (ret != 0) {
		printf("�׽������ַ��ʧ�ܣ�\n");
		return -1;
	}

	printf("��ʼ�����豸!\n");
	ret = listen(ServerSocket, 1);
	if (ret != 0) {
		printf("�����豸ʧ��!\n");
		return -1;
	}
	len = sizeof(ClientAddr);
	ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &len);
	printf("���ӳɹ���\n");
	if (ClientSocket <= 0) {
		printf("�����豸ʧ��!\n");
		return -1;
	}
}

int TCP_Main_Fun( void)
{
	char RevBuf[128] = { 0x00 };
	char SendBuf[128] = {0x00};

	UINT8 RevLengh = 128;
	UINT8 SendLengh = 128;
	UINT8 ret;

	int len;
_InitTCP:
	ret = Creat_TCP_Sever();
	if (ret < 0) {
		printf(" ��ʼ��TCPʧ��");
		goto _InitTCP;
	}

	while (1) {
		
		ret = recv(ClientSocket, RevBuf, RevLengh, 0);
		printf("���յ������ݣ�%s,���յ��ĳ��ȣ�%x\n", RevBuf, RevLengh);
		if (ret <= 0) {
			printf("�ر����ӣ�\n");
			//return -1;
		}

		printf("�����뷢�͸��ͻ��˵��ַ�:\n");
		scanf("%s", SendBuf);
		if (send(ClientSocket, SendBuf, strlen(SendBuf) + 1, 0) <= 0)
		{
			printf("���ʹ���!\n");
		}
		printf("���ͽ���!\n");

		memset(RevBuf, 0, sizeof(RevBuf));
		memset(SendBuf, 0, sizeof(SendBuf));
	}
	//closesocket(ClientSocket);
}
char *Get_Tcp_Time( void)
{
	char Tim_buf[200];
	time_t timep;
	//ctime����һ����ʾ����ʱ����ַ���
	//��ʾϵͳ�ĵ�ǰʱ�� 
	timep = time(NULL);
	if (timep == NULL) {
		printf("��ȡʱ��ʧ�ܣ�");
		return NULL;
	}
	snprintf(Tim_buf, sizeof(Tim_buf), "%s", ctime(&timep));
	printf(" time is %s", Tim_buf);
	return Tim_buf;
}

void main()
{
	while (1) {
		HANDLE Get_Time, TCP_main;
#if 0		Get_Time = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Get_Tcp_Time, NULL, 0, NULL);
		if (Get_Time == 0x00)
		{
			printf(" Get_Tcp_Time�̴߳���ʧ��");
		}
		printf("�߳� Get_Tcp_Time ��ʼ����!\r\n");
		Sleep(3000);
#endif
		TCP_main = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TCP_Main_Fun, NULL, 0, NULL);
		if (TCP_main == 0x00)
		{
			printf(" TCP_main�̴߳���ʧ��");
		}
		printf("�߳� TCP_main ��ʼ����!\r\n");
		Sleep(3000);
	}
}


