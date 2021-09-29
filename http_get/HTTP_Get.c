#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "winsock2.h"

#pragma comment(lib, "ws2_32.lib")

int main()
{
    SOCKET      sSocket = INVALID_SOCKET;
    SOCKADDR_IN stSvrAddrIn = { 0 }; /* �������˵�ַ */
    char        sndBuf[1024] = { 0 };
    char        rcvBuf[2048] = { 0 };
    char* pRcv = rcvBuf;
    int         num = 0;
    int         nRet = SOCKET_ERROR;

    WSADATA     wsaData;

    /* HTTP ��Ϣ���쿪ʼ�����ǳ���Ĺؼ�֮�� */
    sprintf(sndBuf, "GET / HTTP/1.1/n");
    strcat(sndBuf, "Host: www.163.com/n/r/n");
    /* HTTP ��Ϣ������� */

    /* socket DLL��ʼ�� */
    WSAStartup(MAKEWORD(2, 0), &wsaData);

    stSvrAddrIn.sin_family = AF_INET;
    stSvrAddrIn.sin_port = htons(80);
    stSvrAddrIn.sin_addr.S_un.S_addr = inet_addr("218.77.92.148");

    sSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* ���� */
    nRet = connect(sSocket, (SOCKADDR*)&stSvrAddrIn, sizeof(SOCKADDR));
    if (SOCKET_ERROR == nRet)
    {
        printf("connect fail!/n");
        return -1;
    }

    /* ����HTTP������Ϣ */
    send(sSocket, (char*)sndBuf, sizeof(sndBuf), 0);

    /* ����HTTP��Ӧ��Ϣ */
    while (1)
    {
        num = recv(sSocket, pRcv, 2048, 0);

        pRcv += num;

        if ((0 == num) || (-1 == num))
        {
            break;
        }
    }

    /* ��ӡ��Ӧ��Ϣ */
    printf("%s/n", rcvBuf);

    return 0;
}
