#include"server.h"
using namespace BOT_ORM;
using namespace BOT_ORM::Expression;

int server(LPVOID  lparam)
{
    SOCKET sClient = (SOCKET)(LPVOID)lparam; //客户端套接字
    int    retVal;    //返回值  

    user   userT; //用户表项
    elf    elfT;  //精灵表项
    auto   field = FieldExtractor{ userT, elfT };
    ORMapper mapper("user.db");

    //创建数据库（只创建一次）
    try
    {
        mapper.CreateTbl(user{});
        mapper.CreateTbl(elf{});
    }
    catch (...)
    {
    }

    char recvBuf[BUF_SIZE] = { '\0' };  //接收数据缓冲区  
    char sendBuf[BUF_SIZE] = { '\0' };  //返回给客户端得数据 
    std::string stName = "";			//登录、注册用户名
    std::string updateName = "";		//登陆成功后数据更新用户名
    std::string sychroName = "";		//登出数据同步用户名
    int totalSendTimes = 0;				//用户小精灵个数
    int sendTimes = 0;				//已发送小精灵信息个数

    while (true)
    {
        //接收客户端数据  
        retVal = recv(sClient, recvBuf, BUF_SIZE, 0);

        //接受失败 结束当前线程 释放线程资源
        if (SOCKET_ERROR == retVal)
        {
            std::cout << "recv failed!\n";
            return -1;
        }

        //用户名和密码的缓存
        char passwordBuf[maxLength] = { '\0' };
        char userNameBuf[maxLength] = { '\0' };

        //用户注册输入用户名
        if (SIGNUP_NAME == recvBuf[0])
        {
            //提取用户名
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            //将用户名转化为string类型（数据库中用户名为string类型）
            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);

            //保存用户名以便下次输入密码时在数据库查找
            stName = stNameBuf;

            std::cout << "sign up name: " << stName << "\n";

            //在数据库的用户表中查找已有用户名与请求用户名相同的表项
            auto result = mapper.Query(user{})
                .Where(field(userT.userName) == stNameBuf)//string
                .ToVector(); //转化为向量

                             //不存在相同用户名，当前用户名可以使用
            if (0 == result.size())//length
            {
                sendBuf[0] = SUCCESS;
            }
            //存在相同用户名，当前用户名无法使用
            else
            {
                sendBuf[0] = FAILURE;

                //清空用户名缓存（此次用户名无法用来查找）
                stName = "";
            }
        }

        //用户注册输入密码
        else if (SIGNUP_PASSWORD == recvBuf[0])
        {
            //提取密码
            strncpy_s(passwordBuf, recvBuf + 1, maxLength);

            //将密码转化为string类型（数据库中用户名为string类型）
            std::string stPasswordBuf(&passwordBuf[0], &passwordBuf[strlen(passwordBuf)]);
            std::cout << "sign up password: " << stPasswordBuf << "\n";


            //在数据库用户表中插入新的表项
            mapper.Insert(user{ stName, stPasswordBuf, online, 0, 0 });

            sendBuf[0] = SUCCESS;

            //随机数种子
            srand((int)time(NULL));

            //随机数生成三个小精灵
            for (int i = 0; i < 3; i++)
            {
                int p = rand() % 8 + 1;
                sendBuf[i + 1] = p;

                //小精灵表项中插入随机生成的小精灵 小精灵等级1 经验0
                mapper.Insert(elf{ 0, stName, p, 1, 0 }, false);
            }

            //清空用户名缓存
            stName = "";
        }

        //用户登录输入用户名
        else if (LOGIN_NAME == recvBuf[0])
        {
            //提取用户名
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            //将用户名转化为string类型（数据库中用户名为string类型）
            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);

            //保存用户名以便下次输入密码时在数据库查找
            stName = stNameBuf;
            std::cout << "log in name: " << stName << "\n";

            //成功
            sendBuf[0] = SUCCESS;
        }

        //用户登录输入密码
        else if (LOGIN_PASSWORD == recvBuf[0])
        {
            //提取密码
            strncpy_s(passwordBuf, recvBuf + 1, maxLength);

            //将密码转化为string类型（数据库中用户名为string类型）
            std::string stPasswordBuf(&passwordBuf[0], &passwordBuf[strlen(passwordBuf)]);
            std::cout << "log in password: " << stPasswordBuf << "\n";

            //在数据库的用户表中查找已有用户名与请求用户名相同的表项
            auto result = mapper.Query(user{})
                .Where(field(userT.userName) == stName)
                .ToVector();

            //未查到该用户
            if (0 == result.size())
            {
                //用户请求失败
                sendBuf[0] = FAILURE;
                sendBuf[1] = INEXISTENCE;//用户名不存在
            }
            //数据库用户表项中存储的密码与用户输入的密码相同
            else if (result[0].passWord == stPasswordBuf)//length
            {
                //该表项用户状态为下线状态
                if (result[0].state == offline)
                {
                    //更新数据库，用户状态改为上线
                    mapper.Update(user{},
                        (field(userT.state) = online),
                        field(userT.userName) == stName);
                    //发送信息 成功登录
                    sendBuf[0] = SUCCESS;
                    //保存更新用户名
                    updateName = stName;
                }
                //用户状态为登录，即用户已经登录
                else
                {
                    sendBuf[0] = FAILURE;
                    sendBuf[1] = ALREADYONLINE;
                }
            }
            //用户密码输入错误
            else
            {
                sendBuf[0] = FAILURE;
                sendBuf[1] = PASSWORDERROR;//密码错误
            }
            //清空用户名缓存（此次用户名无法用来查找）
            stName = "";
        }

        //用户请求登出
        else if (LOGOUT_REQ == recvBuf[0])
        {
            //提取用户名
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            //将用户名转化为string类型（数据库中用户名为string类型）
            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);
            std::cout << "log out name: " << stNameBuf << "\n";


            //在数据库的用户表中查找已有用户名与请求用户名相同的表项
            auto result = mapper.Query(user{})
                .Where(field(userT.userName) == stNameBuf)//string
                .ToVector();

            //未查找到该用户表项
            if (0 == result.size())//length
            {
                sendBuf[0] = FAILURE;
                sendBuf[1] = FAILURE;  //未注册
            }

            //用户在线
            else if (result[0].state == online)
            {
                //更新数据库，用户状态改为下线
                mapper.Update(user{},
                    (field(userT.state) = offline),
                    field(userT.userName) == stNameBuf);
                sendBuf[0] = SUCCESS;

                //将用户名保存到同步用户名
                sychroName = stNameBuf;

                //删除数据库中用户拥有的小精灵的旧数据（用户下线时会同步小精灵数据）
                mapper.Delete(elf{}, field(elfT.userName) == sychroName);
            }
            //用户不在线
            else
            {
                sendBuf[0] = FAILURE;
                sendBuf[1] = OFFLINE;//未登录
            }
        }

        //查询在线用户
        else if (SEARCHUSER_REQ == recvBuf[0])
        {
            //在数据库中查找状态为在线的所有用户
            auto result = mapper.Query(user{})
                .Where(field(userT.state) == online)//string
                .ToVector();

            //不存在在线用户
            if (0 == result.size())
            {
                sendBuf[0] = FAILURE;
            }

            //用户发出请求
            else if (REQUEST == recvBuf[1])
            {
                totalSendTimes = int(result.size());

                //将用户名转为字符数组发送
                strncpy(sendBuf + 1, result[sendTimes].userName.c_str(),
                    result[sendTimes].userName.length());

                //发送次数加一
                sendTimes++;
                sendBuf[0] = SUCCESS;
            }

            //用户收到数据后回应
            else
            {
                //发送完毕
                if (sendTimes == totalSendTimes)
                {
                    sendBuf[0] = 0;
                    sendTimes = 0;
                    totalSendTimes = 0;
                }
                //未发送完毕
                else
                {
                    //将用户名转为字符数组发送
                    sendBuf[0] = SUCCESS;
                    strncpy(sendBuf + 1, result[sendTimes].userName.c_str(),
                        result[sendTimes].userName.length());
                    sendTimes++;
                }
            }
        }//SEARCH ONLINE USER

         //用户请求查询某用户的小精灵
        else if (SEARCHPOKEMON_REQ == recvBuf[0])
        {
            //提取用户名
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            //将用户名转化为string类型（数据库中用户名为string类型）
            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);
            std::cout << "query pokemon of a user: " << stNameBuf << "\n";

            //在数据库的小精灵表中查找用户名与请求用户名相同的表项
            auto result = mapper.Query(elf{})
                .Where(field(elfT.userName) == stNameBuf)//string
                .ToVector();

            //未查到小精灵
            if (0 == result.size())//length
            {
                sendBuf[0] = FAILURE;
            }
            //查到小精灵
            else
            {
                //发送小精灵种类
                sendBuf[0] = SUCCESS;
                for (int i = 0; i < (int)result.size(); i++)
                {
                    sendBuf[i + 1] = result[i].elfKind;
                }
            }
        }//SEARCH POKEMON

         //用户登录后加载小精灵信息
        else if (UPDATE_REQ == recvBuf[0])
        {
            //在数据库的小精灵表中查找用户名与请求用户名相同的表项
            auto result = mapper.Query(elf{})
                .Where(field(elfT.userName) == updateName)//string
                .ToVector();

            //用户发出请求
            if (REQUEST == recvBuf[1])
            {
                //记录小精灵个数
                totalSendTimes = int(result.size());

                //将小精灵信息转化为字符发送
                char toStr[msgLength] = { '\0' };

                toString(toStr, result[sendTimes]);
                strncpy(sendBuf + 1, toStr, strlen(toStr));

                //发送次数计数
                sendTimes++;
                //请求成功
                sendBuf[0] = SUCCESS;
            }
            //用户收到数据后回应
            else
            {
                //发送次数等于总次数，发送完毕 清空计数
                if (sendTimes == totalSendTimes)
                {
                    sendBuf[0] = FAILURE;
                    sendTimes = 0;
                    totalSendTimes = 0;
                }
                //未发送完毕
                else
                {
                    //将小精灵信息转化为字符发送
                    sendBuf[0] = SUCCESS;

                    char toStr[msgLength] = { '\0' };

                    toString(toStr, result[sendTimes]);
                    strncpy(sendBuf + 1, toStr, strlen(toStr));
                    //发送次数加一
                    sendTimes++;
                }
            }
        }//UPDATE_REQ

         //用户请求同步小精灵数据
        else if (SYNCHRONIZATION == recvBuf[0])
        {
            char elfInfo[msgLength] = { '\0' };
            int kind, level, exp;

            //从recfBuf提取小精灵信息,放到elfInfo中
            strncpy(elfInfo, recvBuf + 1, BUF_SIZE - 1);
            readInfo(elfInfo, kind, level, exp);

            //将小精灵信息插入到数据库
            mapper.Insert(elf{ 0, sychroName, kind, level, exp }, false);
        }//SYNCHRONIZATION

         //用户查询某用户胜率
        else if (WINRATE_REQ == recvBuf[0])
        {
            //提取用户名
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            //将用户名转化为string类型（数据库中用户名为string类型）
            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);

            std::cout << "search for win rate: " << stNameBuf << "\n";

            //在数据库的用户表中查找已有用户名与请求用户名相同的表项
            auto result = mapper.Query(user{})
                .Where(field(userT.userName) == stNameBuf)//string
                .ToVector(); //转化为向量

                             //不存在用户  无法返回胜率
            if (0 == result.size())//length
            {
                sendBuf[0] = FAILURE;
            }
            //存在用户
            else
            {
                sendBuf[0] = SUCCESS;

                char toStr[msgLength] = { '\0' };

                //将用户胜率转化为字符发送
                winRateStr(toStr, result[0].winNum, result[0].sumNum, 0);
                strncpy(sendBuf + 1, toStr, strlen(toStr));
            }
        }//WINRATE_REQ

         //用户请求将胜率同步到服务器
        else if (SYNCHROWINRATE == recvBuf[0])
        {
            char winRate[msgLength] = { '\0' };
            int winN, sumN, useless;

            //从recfBuf提取小精灵信息,放到elfInfo中
            strncpy(winRate, recvBuf + 1, BUF_SIZE - 1);
            readInfo(winRate, winN, sumN, useless);

            //更新数据库，修改用户胜率
            mapper.Update(user{},
                (field(userT.winNum) = winN) && (field(userT.sumNum) = sumN),
                field(userT.userName) == sychroName);
        }//SYNCHROWINRATE

         //请求有误
        else if (0 == recvBuf[0])
        {
            std::cout << "断开连接\n";
        }

        //发送信息
        send(sClient, sendBuf, BUF_SIZE, 0);

        //清空发送缓存和接收缓存
        for (int i = 0; i < BUF_SIZE; i++)
        {
            sendBuf[i] = '\0';
            recvBuf[i] = '\0';
        }
    }//while(true)    
}
