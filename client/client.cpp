#include"pokemon.h"
using namespace std;

int client()
{
    WSADATA wsd;  //WSADATA变量 用于存储接收到的信息 
    SOCKET sHost; //服务器套接字  
    SOCKADDR_IN servAddr; //服务器地址  
    int retVal;   //返回值  

    //初始化套结字动态库  
    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)  //windows异步套接字启动命令 
    {
        cout << "WSAStartup failed!" << endl;
        return -1;
    }
    //创建套接字  
    sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //创建套接字失败
    if (INVALID_SOCKET == sHost)
    {
        cout << "socket failed!" << endl;
        WSACleanup();//释放套接字资源  
        return  -1;
    }

    //设置服务器地址  
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons((short)4999);
    int nServAddlen = sizeof(servAddr);

    //连接服务器  
    retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
    //连接服务器失败
    if (SOCKET_ERROR == retVal)
    {
        cout << "connect failed!" << endl;
        closesocket(sHost); //关闭套接字  
        WSACleanup(); //释放套接字资源  
        return -1;
    }
    cout << "connect!\n";

    //用户未退出
    while (stop == 0)
    {
        //向服务器发送数据 
        if (sendRequest == SEND)
        {
            //发送信息
            retVal = send(sHost, sendBuf, strlen(sendBuf), 0);
            //发送失败
            if (SOCKET_ERROR == retVal)
            {
                cout << "send failed!" << endl;
                closesocket(sHost); //关闭套接字  
                WSACleanup(); //释放套接字资源  
                return -1;
            }

            //接受信息 存放在recvBuf中，大小为BUF_SIZE
            recv(sHost, recvBuf, BUF_SIZE, 0);

            //发送端上锁
            sendRequest = WAIT;
            //打开信息处理锁
            receiveInfo = RECV;
        }
    }//stop==0  

     //退出  
    closesocket(sHost); //关闭套接字  
    WSACleanup();       //释放套接字资源  

                        //释放线程资源
    return 0;
}