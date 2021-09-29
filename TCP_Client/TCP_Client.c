#include<stdio.h>
#include<winsock2.h>



#pragma comment(lib,"ws2_32.lib")
int main()
{
	SOCKET clientsocket;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN clientaddr;
	char buf[1024];

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 0), &wsa);	//初始化WS2_32.DLL

	//创建套接字
	if ((clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		printf("套接字socket创建失败!\n");
		return -1;
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(8080);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//请求连接
	printf("尝试连接中...\n");
	if (connect(clientsocket, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) != 0)
	{
		printf("连接失败!\n");
		return -1;
	}
	printf("连接成功!\n");

	//发送数据
	printf("请输入发送给服务器的字符:\n");
	scanf("%s", buf);
	if (send(clientsocket, buf, strlen(buf) + 1, 0) <= 0)
	{
		printf("发送错误!\n");
	}

	//接收数据
	while (1) {
		if (recv(clientsocket, buf, 1024, 0) <= 0)
		{
			printf("关闭连接!\n");
			closesocket(clientsocket);
		}
		printf("接收来自服务器的信息: %s\n", buf);
		break;
	}
	//关闭套接字
	closesocket(clientsocket);
	WSACleanup();    //释放WS2_32.DLL
	return 0;
}