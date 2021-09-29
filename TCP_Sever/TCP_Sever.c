#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<winsock2.h>


#pragma comment(lib,"ws2_32.lib")//静态加载ws2_32.lib

int main()
{ 
	SOCKET serversoc;
	SOCKET clientsoc;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN clientaddr;
	char buf[1024];
	int len;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 0), &wsa);	//初始化WS2_32.DLL

	//创建套接字
	if ((serversoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		printf("套接字socket创建失败!\n");
		return -1;
	}

	//命名协议，IP，端口
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(8000);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	//绑定套接字
	if (bind(serversoc, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) != 0)
	{
		printf("套接字绑定失败!\n");
		return -1;
	}

	printf("开始监听...\n");
	//监听请求
	if (listen(serversoc, 1) != 0)
	{
		printf("监听失败!\n");
		return -1;
	}

	len = sizeof(SOCKADDR_IN);

	//接收请求
	if ((clientsoc = accept(serversoc, (SOCKADDR*)&clientaddr, &len)) <= 0)
	{
		printf("接受连接失败!\n");
		return -1;
	}
	printf("连接成功\n");

	//接收数据
	while (1)
	{
		if (recv(clientsoc, buf, 1024, 0) <= 0)
		{
			printf("关闭连接!\n");
			closesocket(clientsoc);
		}
		printf("接收来自客户端的信息: %s\n", buf);
		//发送数据
		printf("请输入发送给客户端的字符:\n");
		scanf("%s", buf);
		//send to client
		if (send(clientsoc, buf, strlen(buf) + 1, 0) <= 0)
		{
			printf("发送错误!\n");
		}
		//break;
	}
#if 0
	//发送数据
	printf("请输入发送给客户端的字符:\n");
	scanf("%s", buf);
	//send to client
	if (send(clientsoc, buf, strlen(buf) + 1, 0) <= 0)
	{
		printf("发送错误!\n");
	}
#endif
	WSACleanup();     //释放WS2_32.DLL
	return 0;
}