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
static	SOCKADDR_IN ServerAddr;//服务器地址
static	SOCKADDR_IN ClientAddr;//客户端地址

int Get_TCP_State(void )
{
	int Tcp_Sta;
	int Tcp_Sta_Len = sizeof(Tcp_Sta);
	int ret;
	ret = getsockopt(ServerSocket, SOL_SOCKET , SO_KEEPALIVE , (char*)&Tcp_Sta , &Tcp_Sta_Len );

	if (ret < 0) {
		printf("SO_KEEPALIVE Value : %d \n", Tcp_Sta);
		printf("请检查网络连接 \n");
		return -1;
	}
	return 1;
	//printf( "接到一个来自 %s 的连接/n", inet_ntoa( ClientAddr.sin_addr));
}

int Creat_TCP_Sever( void)
{
	int len;
	uint8_t ret;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 0), &wsa);	//初始化WS2_32.DLL

	/*创建服务端文件描述符*/
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket <= 0X00) {
		printf(" 套接字建立失败！\n");
		return -1;
	}
	/*服务器地址赋值*/
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(8100); //1024 ~49151：普通用户注册的端口号
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	/*绑定套接字文件描述符与地址信息结合起来*/
	ret = bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if (ret != 0) {
		printf("套接字与地址绑定失败！\n");
		return -1;
	}

	printf("开始监听设备!\n");
	ret = listen(ServerSocket, 1);
	if (ret != 0) {
		printf("监听设备失败!\n");
		return -1;
	}
	len = sizeof(ClientAddr);
	ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &len);
	printf("连接成功！\n");
	if (ClientSocket <= 0) {
		printf("连接设备失败!\n");
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
		printf(" 初始化TCP失败");
		goto _InitTCP;
	}

	while (1) {
		
		ret = recv(ClientSocket, RevBuf, RevLengh, 0);
		printf("接收到的数据：%s,接收到的长度：%x\n", RevBuf, RevLengh);
		if (ret <= 0) {
			printf("关闭连接！\n");
			//return -1;
		}

		printf("请输入发送给客户端的字符:\n");
		scanf("%s", SendBuf);
		if (send(ClientSocket, SendBuf, strlen(SendBuf) + 1, 0) <= 0)
		{
			printf("发送错误!\n");
		}
		printf("发送结束!\n");

		memset(RevBuf, 0, sizeof(RevBuf));
		memset(SendBuf, 0, sizeof(SendBuf));
	}
	//closesocket(ClientSocket);
}
char *Get_Tcp_Time( void)
{
	char Tim_buf[200];
	time_t timep;
	//ctime返回一个表示当地时间的字符串
	//显示系统的当前时间 
	timep = time(NULL);
	if (timep == NULL) {
		printf("获取时间失败！");
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
			printf(" Get_Tcp_Time线程创建失败");
		}
		printf("线程 Get_Tcp_Time 开始运行!\r\n");
		Sleep(3000);
#endif
		TCP_main = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TCP_Main_Fun, NULL, 0, NULL);
		if (TCP_main == 0x00)
		{
			printf(" TCP_main线程创建失败");
		}
		printf("线程 TCP_main 开始运行!\r\n");
		Sleep(3000);
	}
}


