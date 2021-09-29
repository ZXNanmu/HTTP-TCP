//#include "stdafx.h" 控制台应用自带头文件，能够加快编译的速度
#include<winsock2.h> //通过该头文件调用winsock的函数，如下文的WSAStartup、bind()、connect（）、inet_addr()等
#include<windows.h>   //调用windows内核及接口函数
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#pragma comment(lib,"ws2_32")  //说明需要使用win32的库

int main(int argc, char* argv[]) {
    int i;
    SOCKET fd;           //套接字初始化
    SOCKADDR_IN addr;//该结构体初始化可以让我们对 “协议簇类型、网络地址、端口号”进行操作
    WSADATA wsadata;

    i = WSAStartup(0x0202, &wsadata); //说明Win32库的版本及对象
    fd = socket(AF_INET, SOCK_STREAM, 0); //协议类型、地址、端口号的初始化
    addr.sin_addr.S_un.S_addr = 0;
    addr.sin_family = AF_INET;
    addr.sin_port = 0;

    i = bind(fd, (sockaddr*)&addr, sizeof(SOCKADDR_IN)); //将上文的套接字进行绑定

    addr.sin_addr.S_un.S_addr = inet_addr("14.215.177.38"); //确定IP地址和端口号
    addr.sin_port = ntohs(80);

    i = connect(fd, (sockaddr*)&addr, sizeof(SOCKADDR_IN));   //尝试进行TCP三次握手
    if (i == NOERROR) {
        char* Buffer = new char[8193];
        i = sprintf(Buffer, "GET / HTTP/1.1\r\n"//HTTP协议的语法格式
            "Host:www.baidu.com\r\n"
            "User-Agent:whatever\r\n"
            "Accept-Type:*/*\r\n"
            "Connection:open\r\n"
            "X-Power:XXX\r\n\r\n");//注意这里要空一行，因为HTTP头与体之间需要空一行进行区分　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　//否则对方服务器无法识别，请求无法通过
        int n = send(fd, Buffer, i, 0);//发送请求数据
        if (n == i) {
            do {
                i = recv(fd, Buffer, 8192, 0);//接收服务器响应
                if (i <= 0) {
                    printf("closed by peer:%d\r\n", i);
                    break;
                }
                Buffer[i] = '\0';
                printf("%s\r\n", Buffer);//循环输出网页数据
            } while ("Go!");

        }
        else//两个else是错误情况的反馈
        {
            printf("we can't send to...\r\n");
        }
        delete[]Buffer;       //数组使用完成，释放掉数组空间
    }
    else
    {
        printf("we can't connect to..\r\n");
    }
    i = closesocket(fd);//请求完成，关闭套接字，清除WSA
    i = WSACleanup();
    system("pause");
    return 0;
}