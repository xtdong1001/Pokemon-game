#include"server.h"

int main()
{
    WSADATA         wsd;            //WSADATA变量  
    SOCKET          sServer;        //服务器套接字
    SOCKET          sClient;        //客户端套接字  
    SOCKADDR_IN     addrServ;;      //服务器地址  
    int             retVal;         //返回值  

    //初始化套结字动态库  
    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
    {
        std::cout << "WSAStartup failed!\n";
        return 1;
    }

    //创建套接字  
    sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //创建失败
    if (INVALID_SOCKET == sServer)
    {
        std::cout << "socket failed!\n";
        WSACleanup();//释放套接字资源;  
        return  -1;
    }

    //服务器套接字地址   
    addrServ.sin_family = AF_INET;
    addrServ.sin_port = htons(4999);
    addrServ.sin_addr.s_addr = INADDR_ANY;

    //绑定套接字  
    retVal = bind(sServer, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
    //绑定失败
    if (SOCKET_ERROR == retVal)
    {
        std::cout << "bind failed!\n";
        closesocket(sServer);   //关闭套接字  
        WSACleanup();           //释放套接字资源;  
        return -1;
    }

    //开始监听   
    retVal = listen(sServer, 1);
    if (SOCKET_ERROR == retVal)
    {
        std::cout << "listen failed!\n";
        closesocket(sServer);   //关闭套接字  
        WSACleanup();           //释放套接字资源;  
        return -1;
    }

    //接受客户端请求  
    sockaddr_in addrClient;
    int addrClientlen = sizeof(addrClient);

    //服务器创建多线程
    while (1)
    {
        sClient = SOCKET_ERROR;
        //等待连接
        while (SOCKET_ERROR == sClient)
        {
            sClient = accept(sServer, (sockaddr FAR*)&addrClient, &addrClientlen);
        }

        //创建线程 一个客户端进程对应一个服务器线程
        DWORD  dwThreadId;
        HANDLE  hThread;

        hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)server,
            (LPVOID)sClient, 0, &dwThreadId);
        //创建线程失败
        if (hThread == NULL)
        {
            printf("CreatThread failed.\n");
        }
        //创建线程成功
        else
        {
            printf("CreateThread  OK.\n");
        }
    }

    closesocket(sServer);   //关闭套接字  
    WSACleanup();           //释放套接字资源;  
    return 0;
}