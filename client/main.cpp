#include"pokemon.h"

//主函数 负责接收用户请求 打开socket线程
int main()
{
    //打开客户端socket线程
    DWORD ThreadID2 = 0;
    HANDLE hClient = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)client, NULL, 0, &ThreadID2);

    //用户请求
    int request = -1;

    //创建一个用户
    user user1;

    //随机数种子
    srand((int)time(NULL));

    //若用户未要求退出则循环接收请求
    while (request != STOP)
    {
        //打印菜单
        std::cout << "\n欢迎来到宠物小精灵游戏！" << std::endl;
        std::cout << "请输入：" << std::endl;
        std::cout << "1-注册" << std::endl;
        std::cout << "2-登录" << std::endl;
        std::cout << "3-登出" << std::endl;
        std::cout << "4-查询当前在线用户" << std::endl;
        std::cout << "5-查询所有用户拥有的精灵" << std::endl;
        std::cout << "6-参加升级赛" << std::endl;
        std::cout << "7-参加决斗赛" << std::endl;
        std::cout << "8-查看当前勋章" << std::endl;
        std::cout << "9-参加2v2升级赛" << std::endl;
        std::cout << "10-查询某用户胜率" << std::endl;
        std::cout << "0-退出\n" << std::endl;

        //用户输入请求
        std::cin >> request;

        //调用函数实现用户请求
        switch (request)
        {
        case SIGNUP:           user1.signUp();           break;//用户注册
        case LOGIN:            user1.logIn();            break;//用户登录
        case LOGOUT:           user1.logOut();           break;//用户登出
        case SEARCHONLINEUSER: user1.searchOnlineUser(); break;//查询在线用户
        case SEARCHPOKEMON:    user1.searchPokemon();    break;//查询某注册用户的小精灵
        case STOP:             user1.terminate();        break;//终止
        case UPGRADE:		   user1.upgrade();			 break;//升级赛
        case DUEL:			   user1.duel();			 break;//决斗赛
        case MEDAL:			   user1.medal();			 break;//勋章查看
        case DOUBLE_UPGRADE:   user1.upgrade2v2();       break;//2v2升级赛
        case SEARCHWINRATE:	   user1.searchWinRate();    break;//查询某用户胜率
        default:break;
        }
    }
    return 0;
}

/*发送请求到服务器 发送的信息第一位为请求类型type 第二位之后为内容
sendMessage函数负责将以上两个内容拼接 并打开客户端socket的发送锁*/
void sendMessage(char type, char *message)
{
    sendBuf[0] = type;
    strncpy(sendBuf + 1, message, msgLength);

    //打开客户端socket的发送锁
    sendRequest = SEND;
}

//判断用户名输入格式是否正确
int isCorrectName(char *name)
{
    for (int i = 0; i < maxLength; i++)
    {
        //长度小于等于14，符合要求
        if (name[i] == '\0' && i>0)
        {
            //用户名格式正确
            return SUCCESS;
        }

        //密码中含有不符合要求的字符
        if (!((name[i] >= '0' && name[i] <= '9')
            || (name[i] >= 'a' && name[i] <= 'z')
            || (name[i] >= 'A' && name[i] <= 'Z')
            || (name[i] == '_')))
        {
            std::cout << "用户名仅支持字母、数字和下划线" << std::endl;
            //用户名格式错误
            return FAILURE;
        }
    }
    //用户名长度超过14
    return FAILURE;
}

//判断密码输入格式是否正确
int isCorrectPword(char *word)
{
    for (int i = 0; i < maxLength; i++)
    {
        //密码长度不足6 格式不正确
        if (word[i] == '\0' && i <= 5)
        {
            //输出提示信息
            std::cout << "密码为6-14位" << std::endl;
            //密码格式不正确
            return FAILURE;
        }

        //密码长度大于等于6小于等于14
        else if (word[i] == '\0' && i > 5)
        {
            //密码格式正确
            return SUCCESS;
        }

        //密码中含有不符合要求的字符
        if (!(word[i] >= 33 && word[i] <= 126))
        {
            std::cout << "用户名仅支持字母，数字和标点符号" << std::endl;
            //密码格式不正确
            return FAILURE;
        }
    }
    //密码长度超过14
    return FAILURE;
}

//清空发送接收缓冲区
void clearBuf()
{
    for (int i = 0; i < BUF_SIZE; i++)
    {
        sendBuf[i] = '\0';
        recvBuf[i] = '\0';
    }
}

//从字符数组info中读取小精灵信息，存入kind，level，exp中
//表示小精灵的种类，等级，经验
//info格式为{kind,level,exp,}
void readInfo(char* info, int& kind, int& level, int& exp)
{
    int i;

    //使用atoi函数将逗号前的字符串转化为整型，得到小精灵种类
    kind = atoi(info);
    //找到第一个逗号所在的下标（下一次转换的起始偏移地址）
    for (i = 0; info[i] != ','; i++);
    i++;

    //使用atoi函数将逗号前的字符串转化为整型，得到小精灵等级（转换的起始地址为info+i）
    level = atoi(info + i);

    //找到第二个逗号所在的下标（下一次转换的起始偏移地址）
    for (; info[i] != ','; i++);

    //使用atoi函数将逗号前的字符串转化为整型，得到小精灵经验值（转换的起始地址为info+i）
    exp = atoi(info + i + 1);
}

//计算小精灵对战的胜率 A为对手小精灵 kind和level分别为自己小精灵的种类和等级
void CalWinRate(pokemon *A, int kind, int level)
{
    //询问用户是否需要计算胜率 
    std::cout << "是否计算胜出概率？1-是 0-否\n";
    //用户请求保存在全局变量calWinRate中
    std::cin >> calWinRate;

    //不计算胜率 结束
    if (calWinRate == no)
    {
        return;
    }
    //用户小精灵
    pokemon *pokea = NULL;

    //根据用户小精灵的种类创建一个一样的小精灵
    switch (kind)
    {
    case BULBASAUR:  pokea = new bulbasaur;  break;
    case CHARMANDER: pokea = new charmander; break;
    case SQUIRTLE:   pokea = new squirtle;   break;
    case PIKACHU:    pokea = new pikachu;    break;
    case MANKEY:     pokea = new mankey;     break;
    case SNORLAX:    pokea = new snorlax;    break;
    case CROBAT:	 pokea = new crobat;     break;
    case SHUCKLE:	 pokea = new shuckle;    break;
    default:break;
    }

    //设置小精灵等级，构造一个和用户小精灵一样的小精灵
    pokea->setLevel(level);
    pokea->promoteLevel();
    std::cout << "您的小精灵胜出的概率为：";

    //调用simuFight函数模拟小精灵战斗 计算胜率 pokea为用户小精灵 A为对手小精灵
    double winRate = simuFight(pokea, A);
    //输出结果
    std::cout << winRate << "\n";

    //释放资源
    delete pokea;
    //清空用户请求
    calWinRate = 0;
}

//模拟小精灵战斗1000 次 计算小精灵competitorA的胜率
double simuFight(pokemon* competitorA, pokemon* competitorB)
{
    int time = 0;  //战斗计时
    int end = 0;   //战斗结束标志
    int death = 0; //小精灵死亡标志
    int win = 0;   //用户小精灵获胜次数
                   //双方小精灵的速度，攻击属性，防御值
    int sp1 = 0, sp2 = 0, attr1 = 0, attr2 = 0, def1 = 0, def2 = 0;
    double winRate = 0; //胜率

                        //获得小精灵的速度，攻击属性和防御值
    sp1 = competitorA->getSpeed();
    sp2 = competitorB->getSpeed();
    attr1 = competitorA->getAttr();
    attr2 = competitorB->getAttr();
    def1 = competitorA->getDef();
    def2 = competitorB->getDef();

    //模拟1000次战斗
    for (int i = 0; i < 1000; i++)
    {
        //双方无小精灵死亡
        while (!death)
        {
            //计时器
            time++;
            //轮到小精灵A出招
            if (time%sp1 == 0)
            {
                //               B的伤害函数            A的攻击函数
                death = competitorB->damage(competitorA->attack(attr2, def2));
                //小精灵B死亡 小精灵A胜利 此次模拟战斗结束
                if (death == 1)
                {
                    win++;
                    break;
                }
            }
            //轮到小精灵B出招
            if (time%sp2 == 0)
            {
                death = competitorA->damage(competitorB->attack(attr1, def1));
            }
        }

        //计数清零 小精灵死亡标志清零
        time = 0;
        death = 0;
        //双方小精灵治疗回血
        competitorA->recover();
        competitorB->recover();
    }//1000次

     //返回胜率
    winRate = double(win / 1000.0);
    return winRate;
}

/*将小精灵信息转化为字符数组保存在a中
  (用于将小精灵信息同步到服务器)
  a的格式为{kind,level,exp,}
  k为小精灵种类  l为小精灵等级 e为小精灵经验*/
void toString(char*a, int k, int l, int e)
{
    //起始偏移地址
    int count = 0;

    //将小精灵种类转化为字符数组放在a中
    toChar(k, a, count);

    //将小精灵等级转化为字符数组放在a中
    toChar(l, a, count);

    //将小精灵经验转化为字符数组放在a中
    toChar(e, a, count);
}

//将整数a转化为字符串类型保存在b中  c为字符串起始偏移地址
void toChar(int a, char*b, int& c)
{
    char x[10] = { '\0' };
    //初始化字符数组x
    for (int i = 0; i < 10; i++)
    {
        x[i] = '\0';
    }
    //调用itoa函数将整型转化为字符数组
    itoa(a, x, 10);

    //将字符数组x复制到b中 起始地址为b[c]
    strncpy(b + c, x, strlen(x));
    //修改偏移地址 以便下一次存放
    c = c + strlen(x);

    //数字之间用逗号隔开
    b[c] = ',';
    c++;
}