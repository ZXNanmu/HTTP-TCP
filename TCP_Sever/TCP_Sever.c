#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<winsock2.h>


#pragma comment(lib,"ws2_32.lib")//��̬����ws2_32.lib

int main()
{ 
	SOCKET serversoc;
	SOCKET clientsoc;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN clientaddr;
	char buf[1024];
	int len;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 0), &wsa);	//��ʼ��WS2_32.DLL

	//�����׽���
	if ((serversoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		printf("�׽���socket����ʧ��!\n");
		return -1;
	}

	//����Э�飬IP���˿�
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(8000);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	//���׽���
	if (bind(serversoc, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) != 0)
	{
		printf("�׽��ְ�ʧ��!\n");
		return -1;
	}

	printf("��ʼ����...\n");
	//��������
	if (listen(serversoc, 1) != 0)
	{
		printf("����ʧ��!\n");
		return -1;
	}

	len = sizeof(SOCKADDR_IN);

	//��������
	if ((clientsoc = accept(serversoc, (SOCKADDR*)&clientaddr, &len)) <= 0)
	{
		printf("��������ʧ��!\n");
		return -1;
	}
	printf("���ӳɹ�\n");

	//��������
	while (1)
	{
		if (recv(clientsoc, buf, 1024, 0) <= 0)
		{
			printf("�ر�����!\n");
			closesocket(clientsoc);
		}
		printf("�������Կͻ��˵���Ϣ: %s\n", buf);
		//��������
		printf("�����뷢�͸��ͻ��˵��ַ�:\n");
		scanf("%s", buf);
		//send to client
		if (send(clientsoc, buf, strlen(buf) + 1, 0) <= 0)
		{
			printf("���ʹ���!\n");
		}
		//break;
	}
#if 0
	//��������
	printf("�����뷢�͸��ͻ��˵��ַ�:\n");
	scanf("%s", buf);
	//send to client
	if (send(clientsoc, buf, strlen(buf) + 1, 0) <= 0)
	{
		printf("���ʹ���!\n");
	}
#endif
	WSACleanup();     //�ͷ�WS2_32.DLL
	return 0;
}