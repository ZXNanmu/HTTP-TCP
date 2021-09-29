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
	WSAStartup(MAKEWORD(2, 0), &wsa);	//��ʼ��WS2_32.DLL

	//�����׽���
	if ((clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		printf("�׽���socket����ʧ��!\n");
		return -1;
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(8080);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//��������
	printf("����������...\n");
	if (connect(clientsocket, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) != 0)
	{
		printf("����ʧ��!\n");
		return -1;
	}
	printf("���ӳɹ�!\n");

	//��������
	printf("�����뷢�͸����������ַ�:\n");
	scanf("%s", buf);
	if (send(clientsocket, buf, strlen(buf) + 1, 0) <= 0)
	{
		printf("���ʹ���!\n");
	}

	//��������
	while (1) {
		if (recv(clientsocket, buf, 1024, 0) <= 0)
		{
			printf("�ر�����!\n");
			closesocket(clientsocket);
		}
		printf("�������Է���������Ϣ: %s\n", buf);
		break;
	}
	//�ر��׽���
	closesocket(clientsocket);
	WSACleanup();    //�ͷ�WS2_32.DLL
	return 0;
}