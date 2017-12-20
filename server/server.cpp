#include"server.h"
using namespace BOT_ORM;
using namespace BOT_ORM::Expression;

int server(LPVOID  lparam)
{
    SOCKET sClient = (SOCKET)(LPVOID)lparam; //�ͻ����׽���
    int    retVal;    //����ֵ  

    user   userT; //�û�����
    elf    elfT;  //�������
    auto   field = FieldExtractor{ userT, elfT };
    ORMapper mapper("user.db");

    //�������ݿ⣨ֻ����һ�Σ�
    try
    {
        mapper.CreateTbl(user{});
        mapper.CreateTbl(elf{});
    }
    catch (...)
    {
    }

    char recvBuf[BUF_SIZE] = { '\0' };  //�������ݻ�����  
    char sendBuf[BUF_SIZE] = { '\0' };  //���ظ��ͻ��˵����� 
    std::string stName = "";			//��¼��ע���û���
    std::string updateName = "";		//��½�ɹ������ݸ����û���
    std::string sychroName = "";		//�ǳ�����ͬ���û���
    int totalSendTimes = 0;				//�û�С�������
    int sendTimes = 0;				//�ѷ���С������Ϣ����

    while (true)
    {
        //���տͻ�������  
        retVal = recv(sClient, recvBuf, BUF_SIZE, 0);

        //����ʧ�� ������ǰ�߳� �ͷ��߳���Դ
        if (SOCKET_ERROR == retVal)
        {
            std::cout << "recv failed!\n";
            return -1;
        }

        //�û���������Ļ���
        char passwordBuf[maxLength] = { '\0' };
        char userNameBuf[maxLength] = { '\0' };

        //�û�ע�������û���
        if (SIGNUP_NAME == recvBuf[0])
        {
            //��ȡ�û���
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            //���û���ת��Ϊstring���ͣ����ݿ����û���Ϊstring���ͣ�
            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);

            //�����û����Ա��´���������ʱ�����ݿ����
            stName = stNameBuf;

            std::cout << "sign up name: " << stName << "\n";

            //�����ݿ���û����в��������û����������û�����ͬ�ı���
            auto result = mapper.Query(user{})
                .Where(field(userT.userName) == stNameBuf)//string
                .ToVector(); //ת��Ϊ����

                             //��������ͬ�û�������ǰ�û�������ʹ��
            if (0 == result.size())//length
            {
                sendBuf[0] = SUCCESS;
            }
            //������ͬ�û�������ǰ�û����޷�ʹ��
            else
            {
                sendBuf[0] = FAILURE;

                //����û������棨�˴��û����޷��������ң�
                stName = "";
            }
        }

        //�û�ע����������
        else if (SIGNUP_PASSWORD == recvBuf[0])
        {
            //��ȡ����
            strncpy_s(passwordBuf, recvBuf + 1, maxLength);

            //������ת��Ϊstring���ͣ����ݿ����û���Ϊstring���ͣ�
            std::string stPasswordBuf(&passwordBuf[0], &passwordBuf[strlen(passwordBuf)]);
            std::cout << "sign up password: " << stPasswordBuf << "\n";


            //�����ݿ��û����в����µı���
            mapper.Insert(user{ stName, stPasswordBuf, online, 0, 0 });

            sendBuf[0] = SUCCESS;

            //���������
            srand((int)time(NULL));

            //�������������С����
            for (int i = 0; i < 3; i++)
            {
                int p = rand() % 8 + 1;
                sendBuf[i + 1] = p;

                //С��������в���������ɵ�С���� С����ȼ�1 ����0
                mapper.Insert(elf{ 0, stName, p, 1, 0 }, false);
            }

            //����û�������
            stName = "";
        }

        //�û���¼�����û���
        else if (LOGIN_NAME == recvBuf[0])
        {
            //��ȡ�û���
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            //���û���ת��Ϊstring���ͣ����ݿ����û���Ϊstring���ͣ�
            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);

            //�����û����Ա��´���������ʱ�����ݿ����
            stName = stNameBuf;
            std::cout << "log in name: " << stName << "\n";

            //�ɹ�
            sendBuf[0] = SUCCESS;
        }

        //�û���¼��������
        else if (LOGIN_PASSWORD == recvBuf[0])
        {
            //��ȡ����
            strncpy_s(passwordBuf, recvBuf + 1, maxLength);

            //������ת��Ϊstring���ͣ����ݿ����û���Ϊstring���ͣ�
            std::string stPasswordBuf(&passwordBuf[0], &passwordBuf[strlen(passwordBuf)]);
            std::cout << "log in password: " << stPasswordBuf << "\n";

            //�����ݿ���û����в��������û����������û�����ͬ�ı���
            auto result = mapper.Query(user{})
                .Where(field(userT.userName) == stName)
                .ToVector();

            //δ�鵽���û�
            if (0 == result.size())
            {
                //�û�����ʧ��
                sendBuf[0] = FAILURE;
                sendBuf[1] = INEXISTENCE;//�û���������
            }
            //���ݿ��û������д洢���������û������������ͬ
            else if (result[0].passWord == stPasswordBuf)//length
            {
                //�ñ����û�״̬Ϊ����״̬
                if (result[0].state == offline)
                {
                    //�������ݿ⣬�û�״̬��Ϊ����
                    mapper.Update(user{},
                        (field(userT.state) = online),
                        field(userT.userName) == stName);
                    //������Ϣ �ɹ���¼
                    sendBuf[0] = SUCCESS;
                    //��������û���
                    updateName = stName;
                }
                //�û�״̬Ϊ��¼�����û��Ѿ���¼
                else
                {
                    sendBuf[0] = FAILURE;
                    sendBuf[1] = ALREADYONLINE;
                }
            }
            //�û������������
            else
            {
                sendBuf[0] = FAILURE;
                sendBuf[1] = PASSWORDERROR;//�������
            }
            //����û������棨�˴��û����޷��������ң�
            stName = "";
        }

        //�û�����ǳ�
        else if (LOGOUT_REQ == recvBuf[0])
        {
            //��ȡ�û���
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            //���û���ת��Ϊstring���ͣ����ݿ����û���Ϊstring���ͣ�
            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);
            std::cout << "log out name: " << stNameBuf << "\n";


            //�����ݿ���û����в��������û����������û�����ͬ�ı���
            auto result = mapper.Query(user{})
                .Where(field(userT.userName) == stNameBuf)//string
                .ToVector();

            //δ���ҵ����û�����
            if (0 == result.size())//length
            {
                sendBuf[0] = FAILURE;
                sendBuf[1] = FAILURE;  //δע��
            }

            //�û�����
            else if (result[0].state == online)
            {
                //�������ݿ⣬�û�״̬��Ϊ����
                mapper.Update(user{},
                    (field(userT.state) = offline),
                    field(userT.userName) == stNameBuf);
                sendBuf[0] = SUCCESS;

                //���û������浽ͬ���û���
                sychroName = stNameBuf;

                //ɾ�����ݿ����û�ӵ�е�С����ľ����ݣ��û�����ʱ��ͬ��С�������ݣ�
                mapper.Delete(elf{}, field(elfT.userName) == sychroName);
            }
            //�û�������
            else
            {
                sendBuf[0] = FAILURE;
                sendBuf[1] = OFFLINE;//δ��¼
            }
        }

        //��ѯ�����û�
        else if (SEARCHUSER_REQ == recvBuf[0])
        {
            //�����ݿ��в���״̬Ϊ���ߵ������û�
            auto result = mapper.Query(user{})
                .Where(field(userT.state) == online)//string
                .ToVector();

            //�����������û�
            if (0 == result.size())
            {
                sendBuf[0] = FAILURE;
            }

            //�û���������
            else if (REQUEST == recvBuf[1])
            {
                totalSendTimes = int(result.size());

                //���û���תΪ�ַ����鷢��
                strncpy(sendBuf + 1, result[sendTimes].userName.c_str(),
                    result[sendTimes].userName.length());

                //���ʹ�����һ
                sendTimes++;
                sendBuf[0] = SUCCESS;
            }

            //�û��յ����ݺ��Ӧ
            else
            {
                //�������
                if (sendTimes == totalSendTimes)
                {
                    sendBuf[0] = 0;
                    sendTimes = 0;
                    totalSendTimes = 0;
                }
                //δ�������
                else
                {
                    //���û���תΪ�ַ����鷢��
                    sendBuf[0] = SUCCESS;
                    strncpy(sendBuf + 1, result[sendTimes].userName.c_str(),
                        result[sendTimes].userName.length());
                    sendTimes++;
                }
            }
        }//SEARCH ONLINE USER

         //�û������ѯĳ�û���С����
        else if (SEARCHPOKEMON_REQ == recvBuf[0])
        {
            //��ȡ�û���
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            //���û���ת��Ϊstring���ͣ����ݿ����û���Ϊstring���ͣ�
            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);
            std::cout << "query pokemon of a user: " << stNameBuf << "\n";

            //�����ݿ��С������в����û����������û�����ͬ�ı���
            auto result = mapper.Query(elf{})
                .Where(field(elfT.userName) == stNameBuf)//string
                .ToVector();

            //δ�鵽С����
            if (0 == result.size())//length
            {
                sendBuf[0] = FAILURE;
            }
            //�鵽С����
            else
            {
                //����С��������
                sendBuf[0] = SUCCESS;
                for (int i = 0; i < (int)result.size(); i++)
                {
                    sendBuf[i + 1] = result[i].elfKind;
                }
            }
        }//SEARCH POKEMON

         //�û���¼�����С������Ϣ
        else if (UPDATE_REQ == recvBuf[0])
        {
            //�����ݿ��С������в����û����������û�����ͬ�ı���
            auto result = mapper.Query(elf{})
                .Where(field(elfT.userName) == updateName)//string
                .ToVector();

            //�û���������
            if (REQUEST == recvBuf[1])
            {
                //��¼С�������
                totalSendTimes = int(result.size());

                //��С������Ϣת��Ϊ�ַ�����
                char toStr[msgLength] = { '\0' };

                toString(toStr, result[sendTimes]);
                strncpy(sendBuf + 1, toStr, strlen(toStr));

                //���ʹ�������
                sendTimes++;
                //����ɹ�
                sendBuf[0] = SUCCESS;
            }
            //�û��յ����ݺ��Ӧ
            else
            {
                //���ʹ��������ܴ������������ ��ռ���
                if (sendTimes == totalSendTimes)
                {
                    sendBuf[0] = FAILURE;
                    sendTimes = 0;
                    totalSendTimes = 0;
                }
                //δ�������
                else
                {
                    //��С������Ϣת��Ϊ�ַ�����
                    sendBuf[0] = SUCCESS;

                    char toStr[msgLength] = { '\0' };

                    toString(toStr, result[sendTimes]);
                    strncpy(sendBuf + 1, toStr, strlen(toStr));
                    //���ʹ�����һ
                    sendTimes++;
                }
            }
        }//UPDATE_REQ

         //�û�����ͬ��С��������
        else if (SYNCHRONIZATION == recvBuf[0])
        {
            char elfInfo[msgLength] = { '\0' };
            int kind, level, exp;

            //��recfBuf��ȡС������Ϣ,�ŵ�elfInfo��
            strncpy(elfInfo, recvBuf + 1, BUF_SIZE - 1);
            readInfo(elfInfo, kind, level, exp);

            //��С������Ϣ���뵽���ݿ�
            mapper.Insert(elf{ 0, sychroName, kind, level, exp }, false);
        }//SYNCHRONIZATION

         //�û���ѯĳ�û�ʤ��
        else if (WINRATE_REQ == recvBuf[0])
        {
            //��ȡ�û���
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            //���û���ת��Ϊstring���ͣ����ݿ����û���Ϊstring���ͣ�
            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);

            std::cout << "search for win rate: " << stNameBuf << "\n";

            //�����ݿ���û����в��������û����������û�����ͬ�ı���
            auto result = mapper.Query(user{})
                .Where(field(userT.userName) == stNameBuf)//string
                .ToVector(); //ת��Ϊ����

                             //�������û�  �޷�����ʤ��
            if (0 == result.size())//length
            {
                sendBuf[0] = FAILURE;
            }
            //�����û�
            else
            {
                sendBuf[0] = SUCCESS;

                char toStr[msgLength] = { '\0' };

                //���û�ʤ��ת��Ϊ�ַ�����
                winRateStr(toStr, result[0].winNum, result[0].sumNum, 0);
                strncpy(sendBuf + 1, toStr, strlen(toStr));
            }
        }//WINRATE_REQ

         //�û�����ʤ��ͬ����������
        else if (SYNCHROWINRATE == recvBuf[0])
        {
            char winRate[msgLength] = { '\0' };
            int winN, sumN, useless;

            //��recfBuf��ȡС������Ϣ,�ŵ�elfInfo��
            strncpy(winRate, recvBuf + 1, BUF_SIZE - 1);
            readInfo(winRate, winN, sumN, useless);

            //�������ݿ⣬�޸��û�ʤ��
            mapper.Update(user{},
                (field(userT.winNum) = winN) && (field(userT.sumNum) = sumN),
                field(userT.userName) == sychroName);
        }//SYNCHROWINRATE

         //��������
        else if (0 == recvBuf[0])
        {
            std::cout << "�Ͽ�����\n";
        }

        //������Ϣ
        send(sClient, sendBuf, BUF_SIZE, 0);

        //��շ��ͻ���ͽ��ջ���
        for (int i = 0; i < BUF_SIZE; i++)
        {
            sendBuf[i] = '\0';
            recvBuf[i] = '\0';
        }
    }//while(true)    
}
