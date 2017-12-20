#include"pokemon.h"
using namespace std;

int client()
{
    WSADATA wsd;  //WSADATA���� ���ڴ洢���յ�����Ϣ 
    SOCKET sHost; //�������׽���  
    SOCKADDR_IN servAddr; //��������ַ  
    int retVal;   //����ֵ  

    //��ʼ���׽��ֶ�̬��  
    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)  //windows�첽�׽����������� 
    {
        cout << "WSAStartup failed!" << endl;
        return -1;
    }
    //�����׽���  
    sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //�����׽���ʧ��
    if (INVALID_SOCKET == sHost)
    {
        cout << "socket failed!" << endl;
        WSACleanup();//�ͷ��׽�����Դ  
        return  -1;
    }

    //���÷�������ַ  
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons((short)4999);
    int nServAddlen = sizeof(servAddr);

    //���ӷ�����  
    retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
    //���ӷ�����ʧ��
    if (SOCKET_ERROR == retVal)
    {
        cout << "connect failed!" << endl;
        closesocket(sHost); //�ر��׽���  
        WSACleanup(); //�ͷ��׽�����Դ  
        return -1;
    }
    cout << "connect!\n";

    //�û�δ�˳�
    while (stop == 0)
    {
        //��������������� 
        if (sendRequest == SEND)
        {
            //������Ϣ
            retVal = send(sHost, sendBuf, strlen(sendBuf), 0);
            //����ʧ��
            if (SOCKET_ERROR == retVal)
            {
                cout << "send failed!" << endl;
                closesocket(sHost); //�ر��׽���  
                WSACleanup(); //�ͷ��׽�����Դ  
                return -1;
            }

            //������Ϣ �����recvBuf�У���СΪBUF_SIZE
            recv(sHost, recvBuf, BUF_SIZE, 0);

            //���Ͷ�����
            sendRequest = WAIT;
            //����Ϣ������
            receiveInfo = RECV;
        }
    }//stop==0  

     //�˳�  
    closesocket(sHost); //�ر��׽���  
    WSACleanup();       //�ͷ��׽�����Դ  

                        //�ͷ��߳���Դ
    return 0;
}