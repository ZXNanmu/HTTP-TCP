#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")//静态加载ws2_32.lib
typedef unsigned char uint_8t;
typedef unsigned int  uint_16t;
typedef unsigned long uint_32t;

WSADATA wsa;
WSAStartup(MAKEWORD(2, 0), &wsa);	//初始化WS2_32.DLL

SOCKET ServerSocket;
SOCKET ClientSocket;
SOCKADDR_IN ServerAddr;//服务器地址
SOCKADDR_IN ClientAddr;//客户端地址

int Creat_TCP_Sever()
{
	int ret;

	/*创建服务端文件描述符*/
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket <= 0X00) {
		printf(" 套接字建立失败！\n");
		return -1;
	}
	/*服务器地址赋值*/
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(8000); //1024 ~49151：普通用户注册的端口号
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	bzero(ServerAddr, sizeof(ServerAddr));

	/*绑定套接字文件描述符与地址信息结合起来*/
	ret = bind(ServerSocket, (SOCKADDR*)ServerAddr, sizeof(ServerSocket));
	if (ret < 0) {
		printf("套接字与地址绑定失败！\n");
		return -1；
	}

	printf("开始监听设备!\n");
	ret = listen(ServerSocket, 3);
	if (ret != 0) {
		printf("监听设备失败!\n");
		return -1;
	}

	printf("接受连接！\n");
	ClientSocket = accept(ServerSocket, (SOCKADDR*)ClientAddr, sizeof(ClientAddr));
	if (ClientSocket <= 0) {
		printf("连接设备失败!\n");
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
		printf("接收到的数据：%s,接收到的长度：%x", Recv, RevLengh);
		if (ret <= 0) {
			printf("关闭连接！\n")
				return -1;
		}
		printf("请输入发送给客户端的字符:\n");
		scanf("%s", buf);
		if (send(ClientSocket, buf, strlen(buf) + 1, 0) <= 0)
		{
			printf("发送错误!\n");
		}
		
	}
	closesocket(ClientSocket);

}

