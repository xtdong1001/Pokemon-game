#include"pokemon.h"

//全局变量定义
char sendBuf[BUF_SIZE] = { '\0' };  //发送缓冲器 最大长度为BUF_SIZE
char recvBuf[BUF_SIZE] = { '\0' };  //接收缓冲器 最大长度为BUF_SIZE
int sendRequest = WAIT; //socket发送锁(开始时关闭)
int receiveInfo = WAIT; //socket接收消息处理锁(开始时关闭)
int stop = no;			//结束程序标志
int calWinRate = no;     //计算胜率

                        //用户类构造函数
user::user()
{
    //初始化用户名和密码 长度为maxLength
    for (int i = 0; i < maxLength; i++)
    {
        userName[i] = '\0';
        password[i] = '\0';
    }

    //初始化小精灵指针
    for (int i = 0; i < 30; i++)
    {
        poke[i] = NULL;
    }
    //小精灵数量设置为0
    pokemonNum = no;

    winNum = no; //赢得比赛次数为0
    playNum = no;//参加游戏次数为0

                //勋章数量设置为0
    for (int i = 0; i < 3; i++)
    {
        NumMedal[i] = no;
        LevelMedal[i] = no;
    }
}

//析构函数
user::~user()
{

}

//用户注册
void user::signUp()
{
    char name[msgLength] = { '\0' };  //用户姓名输入缓冲区
    char pword[msgLength] = { '\0' }; //用户密码输入缓冲区
    int ok = no;  //用户名和密码正确标志

                 //输入不正确则一直循环
    while (!ok)
    {
        //提示信息
        std::cout << "用户名：(1-14位字母，数字，下划线):\n";
        while (!ok)
        {
            std::cin >> name;
            //用户名输入判断
            ok = isCorrectName(name);
        }
        //向服务器发送
        sendMessage(SIGNUP_NAME, name);

        //等待服务器应答
        while (receiveInfo == WAIT);

        //用户注册失败 用户名重复
        if (recvBuf[0] == FAILURE)
        {
            std::cout << "此用户名太受欢迎,请更换一个!" << std::endl;
            ok = no;

            //清空发送接收缓冲区
            clearBuf();
        }
        //锁住用户端分析接受信息程序
        receiveInfo = WAIT;
    }//ok

     //清空发送接收缓冲区
    clearBuf();

    ok = no;
    //用户输入密码
    std::cout << "密码：(6-14位字母，数字，标点符号):\n";
    while (!ok)
    {
        std::cin >> pword;
        //密码输入判断
        ok = isCorrectPword(pword);
    }
    //向服务器发送
    sendMessage(SIGNUP_PASSWORD, pword);

    //等待服务器应答
    while (receiveInfo == WAIT);

    //注册后自动登录 首次登陆获得三个小精灵
    std::cout << "注册成功！\n首次登录，获得:\n";
    for (int i = 0; i < 3; i++)
    {
        switch (recvBuf[i])
        {
        case BULBASAUR:  poke[i] = new bulbasaur;  std::cout << "妙蛙种子 "; break;
        case CHARMANDER: poke[i] = new charmander; std::cout << "小火龙 ";   break;
        case SQUIRTLE:   poke[i] = new squirtle;   std::cout << "杰尼龟 ";   break;
        case PIKACHU:    poke[i] = new pikachu;    std::cout << "皮丘 ";     break;
        case MANKEY:     poke[i] = new mankey;     std::cout << "猴怪 ";     break;
        case SNORLAX:    poke[i] = new snorlax;    std::cout << "小卡比兽 "; break;
        case CROBAT:	 poke[i] = new crobat;     std::cout << "超音蝠 ";   break;
        case SHUCKLE:	 poke[i] = new shuckle;    std::cout << "壶壶 ";     break;

        default:break;
        }
    }
    std::cout << '\n';

    //注册成功后更新用户类信息 将用户姓名和密码保存在用户类中
    for (int i = 0; i < maxLength; i++)
    {
        userName[i] = name[i];
        password[i] = pword[i];
    }
    //小精灵个数
    pokemonNum = 3;

    //清空发送接收缓冲区 上锁
    clearBuf();
    receiveInfo = WAIT;
}

//用户登录
void user::logIn()
{
    char name[msgLength] = { '\0' };  //用户姓名输入缓冲区
    char pword[msgLength] = { '\0' }; //用户密码输入缓冲区

    int ok = no; //用户名和密码正确标志

                //提示用户输入用户名
    std::cout << "用户名：\n";
    while (!ok)
    {
        std::cin >> name;
        //用户名输入判断
        ok = isCorrectName(name);
    }
    //向服务器发送
    sendMessage(LOGIN_NAME, name);
    //等待服务器应答
    while (receiveInfo == WAIT);

    //清空发送接收缓冲区 上锁
    receiveInfo = WAIT;
    clearBuf();

    //提示用户输入密码
    ok = no;
    std::cout << "密码：\n";
    while (!ok)
    {
        std::cin >> pword;
        //密码输入判断
        ok = isCorrectPword(pword);
    }
    //向服务器发送信息
    sendMessage(LOGIN_PASSWORD, pword);

    //等待服务器应答
    while (receiveInfo == WAIT);

    //登录失败
    if (FAILURE == recvBuf[0])
    {
        //用户名不存在
        if (INEXISTENCE == recvBuf[1])
        {
            std::cout << "用户名不存在" << std::endl;
        }
        //密码错误
        if (PASSWORDERROR == recvBuf[1])
        {
            std::cout << "密码错误" << std::endl;
        }
        //当前为登录状态
        else if (ONLINE == recvBuf[1])
        {
            std::cout << "您已经登录" << std::endl;
        }
    }
    //登录成功
    else
    {
        std::cout << "登录成功！\n";
        //登录成功后更新用户类信息 将用户姓名和密码保存在用户类中
        for (int i = 0; i < maxLength; i++)
        {
            userName[i] = name[i];
            password[i] = pword[i];
        }

        //从服务器加载小精灵数据
        std::cout << "加载用户数据中,请稍候……\n";

        //清空发送接收缓冲器 上锁
        receiveInfo = WAIT;
        clearBuf();

        /*****用户请求胜率同步*****/
        //发送查找请求
        sendMessage(WINRATE_REQ, name);

        //等待服务器相应
        while (receiveInfo == WAIT);

        char winRateInfo[msgLength] = { '\0' };

        int winN = no, sumN = no, useless = no;
        //从recvBuf中提取信息放在winRateInfo中
        strncpy(winRateInfo, recvBuf + 1, msgLength);

        //解读信息 winN为用户胜利次数 sumN为比赛总次数
        readInfo(winRateInfo, winN, sumN, useless);

        //保存到本地
        winNum = winN;
        playNum = sumN;

        //清空发送接收缓冲器 上锁
        receiveInfo = WAIT;
        clearBuf();

        /*****用户请求小精灵同步*****/
        //用户请求消息
        char in[msgLength] = { '\0' };
        in[0] = yes;

        int pokeNum = no; //小精灵数量
        char elfInfo[msgLength] = { '\0' }; //小精灵信息

                                            //请求加载小精灵数据
        sendMessage(UPDATE_REQ, in);

        //等待服务器应答
        while (receiveInfo == WAIT);

        //回应服务器的消息
        in[0] = no;

        //获取小精灵的信息 服务器发送完后结束循环
        while (recvBuf[0])
        {
            int eKind, eExp, eLevel;
            //从recvBuf中提取信息放在elfInfo中
            strncpy(elfInfo, recvBuf + 1, msgLength);
            //解读信息 eKind为小精灵种类 eLevel为小精灵等级 eExp为小精灵经验值
            readInfo(elfInfo, eKind, eLevel, eExp);

            //创建一个种类为eKind的1级小精灵
            switch (eKind)
            {
            case BULBASAUR:  poke[pokeNum] = new bulbasaur;  break;
            case CHARMANDER: poke[pokeNum] = new charmander; break;
            case SQUIRTLE:   poke[pokeNum] = new squirtle;   break;
            case PIKACHU:    poke[pokeNum] = new pikachu;    break;
            case MANKEY:     poke[pokeNum] = new mankey;     break;
            case SNORLAX:    poke[pokeNum] = new snorlax;    break;
            case CROBAT:	 poke[pokeNum] = new crobat;     break;
            case SHUCKLE:	 poke[pokeNum] = new shuckle;    break;
            default:break;
            }
            //更新小精灵信息
            poke[pokeNum]->exp = eExp;
            poke[pokeNum]->level = eLevel;
            //小精灵更新为elevel级小精灵
            poke[pokeNum]->promoteLevel();
            //小精灵数量加一
            pokeNum++;

            //清空发送接收缓冲器 上锁
            receiveInfo = WAIT;
            clearBuf();

            //继续发送请求
            sendMessage(UPDATE_REQ, in);

            //等待回复
            while (receiveInfo == WAIT);
        }
        //更新小精灵数量
        pokemonNum = pokeNum;
    }//登陆成功

     //清空发送接收缓冲器 上锁
    receiveInfo = WAIT;
    clearBuf();
}

//用户登出
void user::logOut()
{
    char name[msgLength] = { '\0' }; //用户姓名输入缓冲区

                                     //从用户类获取用户姓名
    for (int i = 0; i < maxLength; i++)
    {
        name[i] = userName[i];
    }

    //发送用户登出请求和用户名
    sendMessage(LOGOUT_REQ, name);

    //等待服务器应答
    while (receiveInfo == WAIT);

    //登出失败
    if (!recvBuf[0])
    {
        //未登录
        if (recvBuf[1])
        {
            std::cout << "用户当前未登录！\n" << std::endl;
        }
        //不存在用户
        else
        {
            std::cout << "用户未注册！\n" << std::endl;
        }
    }
    //登出成功
    else
    {
        //清空发送接收缓冲器 上锁
        receiveInfo = WAIT;
        clearBuf();

        //请求同步信息到服务器
        synchron();

        std::cout << "登出成功！" << std::endl;
    }
    //清空发送接收缓冲器 上锁
    receiveInfo = WAIT;
    clearBuf();

    for (int i = 0; i < pokemonNum; i++)
    {
        poke[i] = NULL;
    }
    pokemonNum = 0;

    //勋章数量设置为0
    for (int i = 0; i < 3; i++)
    {
        NumMedal[i] = no;
        LevelMedal[i] = no;
    }
}

//查询在线用户
void user::searchOnlineUser()
{
    //发送信息 发送1表示请求查询 发送0表示回复收到并请求继续发送
    char in[msgLength] = { '\0' };
    in[0] = yes;

    //在线用户数量
    int userNum = no;
    //在线用户用户名
    char onlineUser[maxLength] = { '\0' };

    //发送请求
    sendMessage(SEARCHUSER_REQ, in);

    //等待服务器应答
    while (receiveInfo == WAIT);
    in[0] = no;

    std::cout << "在线用户:\n";
    //输出查询结果
    while (recvBuf[0])
    {
        //从recvBuf中提取用户名信息，放入onlineUser中
        strncpy(onlineUser, recvBuf + 1, maxLength);
        std::cout << onlineUser << std::endl;
        //在线用户数量加一
        userNum++;

        //清空发送接收缓冲器 上锁
        receiveInfo = WAIT;
        clearBuf();

        //回复表示收到并请求继续发送
        sendMessage(SEARCHUSER_REQ, in);

        //等待服务器相应
        while (receiveInfo == WAIT);
    }
    //清空发送接收缓冲器 上锁
    receiveInfo = WAIT;

    //打印结果
    std::cout << "\n当前在线用户共有" << userNum << "人\n";
    clearBuf();
}

//查询注册用户的精灵
void user::searchPokemon()
{
    char userNameBuf[msgLength] = { '\0' };

    std::cout << "要查找的用户名：\n" << std::endl;
    std::cin >> userNameBuf;

    //发送查找请求
    sendMessage(SEARCHPOKEMON_REQ, userNameBuf);

    //等待服务器相应
    while (receiveInfo == WAIT);

    //查找失败
    if (recvBuf[0] == FAILURE)
    {
        std::cout << "要查找的用户不存在！\n";
        clearBuf();
    }
    //查找成功
    else
    {
        //输出结果
        std::cout << "要查找的用户拥有：\n";
        for (int i = 1; recvBuf[i] != '\0'; i++)
        {
            switch (recvBuf[i])
            {
            case BULBASAUR:  std::cout << "妙蛙种子 "; break;
            case CHARMANDER: std::cout << "小火龙 "; break;
            case SQUIRTLE:	 std::cout << "杰尼龟 "; break;
            case PIKACHU:	 std::cout << "皮丘 "; break;
            case MANKEY:	 std::cout << "猴怪 "; break;
            case SNORLAX:	 std::cout << "小卡比兽 "; break;
            case CROBAT:	 std::cout << "超音蝠 "; break;
            case SHUCKLE:	 std::cout << "壶壶 "; break;
            default:break;
            }
        }
        std::cout << '\n';
    }
    //清空发送接收缓冲器 上锁
    receiveInfo = WAIT;
    clearBuf();
}

//查询某用户的胜率
void user::searchWinRate()
{
    char userNameBuf[msgLength] = { '\0' };

    std::cout << "要查找的用户名：\n" << std::endl;
    std::cin >> userNameBuf;

    //发送查找请求
    sendMessage(WINRATE_REQ, userNameBuf);

    //等待服务器相应
    while (receiveInfo == WAIT);

    //查找失败
    if (recvBuf[0] == FAILURE)
    {
        std::cout << "要查找的用户不存在！\n";
        clearBuf();
    }
    //查找成功
    else
    {
        char winRateInfo[msgLength] = { '\0' };
        //输出结果
        std::cout << "该用户的胜率为：";

        int winN, sumN, useless;
        //从recvBuf中提取信息放在winRateInfo中
        strncpy(winRateInfo, recvBuf + 1, msgLength);
        //解读信息 eKind为小精灵种类 eLevel为小精灵等级 eExp为小精灵经验值
        readInfo(winRateInfo, winN, sumN, useless);

        if (sumN == no)
        {
            std::cout << "0\n";
        }
        else
        {
            double winr = (double)(winN) / sumN;
            std::cout << winr << "\n";
        }
    }
    //清空发送接收缓冲器 上锁
    receiveInfo = WAIT;
    clearBuf();
}

//小精灵战斗 参数competitorA competitorB分别为用户小精灵和对方小精灵
int user::fighting(pokemon* competitorA, pokemon* competitorB)
{
    int win = no;   //用户小精灵获胜次数
    int time = no;  //战斗计时
    int death = no; //小精灵死亡标志
                   //双方小精灵的速度，攻击属性，防御值
    int sp1 = 0, sp2 = 0, attr1 = 0, attr2 = 0, def1 = 0, def2 = 0;

    //获得小精灵的速度，攻击属性和防御值
    sp1 = competitorA->getSpeed();
    sp2 = competitorB->getSpeed();
    attr1 = competitorA->getAttr();
    attr2 = competitorB->getAttr();
    def1 = competitorA->getDef();
    def2 = competitorB->getDef();

    //双方无小精灵死亡
    while (!death)
    {
        //计时器
        time++;
        //轮到小精灵A出招
        if (time%sp1 == 0)
        {
            death = competitorB->damage(competitorA->attack(attr2, def2));
            //小精灵B死亡 小精灵A胜利 此次模拟战斗结束
            if (death == yes)
            {
                win = yes;
                break;
            }
        }
        //轮到小精灵B出招
        if (time%sp2 == 0)
        {
            death = competitorA->damage(competitorB->attack(attr1, def1));
        }
    }
    //计算经验
    competitorA->promote(competitorA->cal_exp(competitorB->level));
    competitorB->promote(competitorB->cal_exp(competitorA->level));
    //打印小精灵信息
    competitorA->print();
    competitorB->print();
    //计数清零
    time = 0;
    //返回战斗结果
    return win;
}

//升级赛
void user::upgrade()
{
    //本方小精灵
    int upgradePoke;

    //用户有小精灵
    if (pokemonNum > 0)
    {
        std::cout << "请从您拥有的小精灵中选择一个进行升级赛\n";
        //打印小精灵信息供用户选择
        for (int i = 0; i < pokemonNum; i++)
        {
            std::cout << i << ":\n";
            poke[i]->print();
        }

        std::cin >> upgradePoke;
    }
    //用户没有小精灵
    else
    {
        //1-8之间随机数
        std::cout << "您已经输光了所有的小精灵，系统将给您随机分配一个\n";
        int p = rand() % 8 + 1;

        //系统随机分配一个1级小精灵
        switch (p)
        {
        case BULBASAUR:  poke[0] = new bulbasaur;  std::cout << "妙蛙种子 "; break;
        case CHARMANDER: poke[0] = new charmander; std::cout << "小火龙 ";   break;
        case SQUIRTLE:   poke[0] = new squirtle;   std::cout << "杰尼龟 ";   break;
        case PIKACHU:    poke[0] = new pikachu;    std::cout << "皮丘 ";    break;
        case MANKEY:     poke[0] = new mankey;     std::cout << "猴怪 ";     break;
        case SNORLAX:    poke[0] = new snorlax;    std::cout << "小卡比兽 ";   break;
        case CROBAT:	 poke[0] = new crobat;     std::cout << "超音蝠 "; break;
        case SHUCKLE:	 poke[0] = new shuckle;    std::cout << "壶壶 "; break;
        default:break;
        }
        //用户小精灵为第0个小精灵
        upgradePoke = 0;
        std::cout << "\n";
        //打印小精灵信息
        poke[0]->print();
    }

    //选择对手
    std::cout << "请从小精灵列表中中选择一个进行升级赛\n";
    std::cout << "力量型： 1-猴怪     2-小火龙\n";
    std::cout << "肉盾型： 3-小卡比兽  4-妙蛙种子\n";
    std::cout << "防御型： 5-杰尼龟   6-壶壶\n";
    std::cout << "速度型： 7-皮丘     8-超音蝠\n";

    int comp = 0; //对手小精灵种类
    std::cin >> comp;

    //创建对手小精灵
    pokemon *competitor = NULL;

    switch (comp)
    {
    case BULBASAUR:  competitor = new bulbasaur;  break;
    case CHARMANDER: competitor = new charmander; break;
    case SQUIRTLE:   competitor = new squirtle;   break;
    case PIKACHU:    competitor = new pikachu;    break;
    case MANKEY:     competitor = new mankey;     break;
    case SNORLAX:    competitor = new snorlax;    break;
    case CROBAT:	 competitor = new crobat;     break;
    case SHUCKLE:	 competitor = new shuckle;    break;
    default:break;
    }

    int opp_level; //对手小精灵等级
    std::cout << "请输入小精灵等级（1-15）\n";
    std::cin >> opp_level;

    //更新对方小精灵信息
    competitor->level = opp_level;
    competitor->promoteLevel();
    //打印对手小精灵信息
    competitor->print();

    //计算本场比赛胜率
    int k = poke[upgradePoke]->kind;
    int l = poke[upgradePoke]->level;
    CalWinRate(competitor, k, l);

    //战斗结束标志
    int end = no;

    //用户不要求战斗结束则一直循环
    while (!end)
    {
        playNum++;

        //小精灵战斗
        int w = fighting(poke[upgradePoke], competitor);

        if (w == yes)
        {
            winNum++;
        }

        std::cout << "是否结束？1-结束，0-继续\n";
        std::cin >> end;

        //双方小精灵治疗回血
        poke[upgradePoke]->recover();
        competitor->recover();
    }
    //释放小精灵资源
    delete competitor;
}

//决斗赛
void user::duel()
{
    //本方小精灵
    int upgradePoke;
    //用户有小精灵
    if (pokemonNum > 0)
    {
        //打印小精灵信息供用户选择
        std::cout << "请从您拥有的小精灵中选择一个进行决斗赛\n";
        for (int i = 0; i < pokemonNum; i++)
        {
            std::cout << i << ":\n";
            poke[i]->print();
        }
        std::cin >> upgradePoke;
    }
    //用户没有小精灵
    else
    {
        //1-8之间随机数
        std::cout << "您已经输光了所有的小精灵，系统随机分配一个\n";
        int p = rand() % 8 + 1;
        //系统随机分配一个1级小精灵
        switch (p)
        {
        case BULBASAUR:  poke[0] = new bulbasaur;  std::cout << "妙蛙种子 "; break;
        case CHARMANDER: poke[0] = new charmander; std::cout << "小火龙 ";   break;
        case SQUIRTLE:   poke[0] = new squirtle;   std::cout << "杰尼龟 ";   break;
        case PIKACHU:    poke[0] = new pikachu;    std::cout << "皮丘 ";   break;
        case MANKEY:     poke[0] = new mankey;     std::cout << "猴怪 ";     break;
        case SNORLAX:    poke[0] = new snorlax;    std::cout << "小卡比兽 ";   break;
        case CROBAT:	 poke[0] = new crobat;     std::cout << "超音蝠 "; break;
        case SHUCKLE:	 poke[0] = new shuckle;    std::cout << "壶壶 "; break;
        default:break;
        }
        std::cout << "\n";
        //用户小精灵为第0个小精灵
        upgradePoke = 0;
        //打印小精灵信息
        poke[0]->print();
    }
    //选择对手
    std::cout << "请从小精灵列表中中选择一个进行决斗赛\n";
    std::cout << "力量型： 1-猴怪     2-小火龙\n";
    std::cout << "肉盾型： 3-小卡比兽 4-妙蛙种子\n";
    std::cout << "防御型： 5-杰尼龟   6-壶壶\n";
    std::cout << "速度型： 7-皮丘    8-叉字蝠\n";

    //对手小精灵种类
    int comp = 0;
    std::cin >> comp;

    //创建小精灵
    pokemon *competitor = NULL;

    //提前申请用户可能获得的小精灵资源
    switch (comp)
    {
    case BULBASAUR:  competitor = new bulbasaur;
        poke[pokemonNum] = new bulbasaur; break;
    case CHARMANDER: competitor = new charmander;
        poke[pokemonNum] = new charmander; break;
    case SQUIRTLE:   competitor = new squirtle;
        poke[pokemonNum] = new squirtle;   break;
    case PIKACHU:    competitor = new pikachu;
        poke[pokemonNum] = new pikachu;    break;
    case MANKEY:     competitor = new mankey;
        poke[pokemonNum] = new mankey;     break;
    case SNORLAX:    competitor = new snorlax;
        poke[pokemonNum] = new snorlax;    break;
    case CROBAT:	 competitor = new crobat;
        poke[pokemonNum] = new crobat;     break;
    case SHUCKLE:	 competitor = new shuckle;
        poke[pokemonNum] = new shuckle;    break;
    default:break;
    }
    //对手小精灵等级
    int opp_level;
    std::cout << "请输入小精灵等级（1-15）\n";
    std::cin >> opp_level;

    //更新对方小精灵信息打印
    competitor->level = opp_level;
    competitor->promoteLevel();
    competitor->print();

    //计算胜率
    int k = poke[upgradePoke]->kind;
    int l = poke[upgradePoke]->level;
    CalWinRate(competitor, k, l);

    //小精灵战斗
    int win = fighting(poke[upgradePoke], competitor);

    //用户胜利 获得对方小精灵
    if (win == SUCCESS && pokemonNum < 30)
    {
        playNum++;
        winNum++;

        //小精灵治疗回血
        poke[upgradePoke]->recover();

        std::cout << "战斗胜利！赢得一个小精灵\n";
        //打印获得的小精灵信息
        competitor->print();

        //用户获得一个小精灵
        poke[pokemonNum]->level = competitor->level;
        poke[pokemonNum]->exp = competitor->exp;
        poke[pokemonNum]->promoteLevel();

        //小精灵数量加一
        pokemonNum++;
        std::cout << "恭喜！您现在有" << pokemonNum << "个小精灵\n";
    }

    //用户失败 送出一个小精灵
    else if (win == FAILURE)
    {
        playNum++;

        //释放提前申请的将要获得的小精灵资源
        delete poke[pokemonNum];

        int give;//送出的小精灵

                 //用户有三个或小于三个小精灵
        if (pokemonNum <= 3)
        {
            std::cout << "请从您的小精灵中选出一个送出！\n";
            //打印要送出的小精灵信息
            for (int i = 0; i < pokemonNum; i++)
            {
                std::cout << i << ":\n";
                poke[i]->print();
            }
            std::cin >> give;
        }
        //多于三个小精灵
        else
        {
            //随机选出3个小精灵
            std::cout << "从您的小精灵中随机选出三个，请选出一个送出！\n";
            int p[3] = { 0,0,0 };  //随机选出三个小精灵
            p[0] = rand() % pokemonNum;
            p[1] = rand() % pokemonNum;

            //两个小精灵不能是同一个
            while (p[1] == p[0])
            {
                p[1] = rand() % pokemonNum;
            }
            p[2] = rand() % pokemonNum;
            //三个小精灵不能有相同的
            while (p[2] == p[0] || p[2] == p[1])
            {
                p[2] = rand() % pokemonNum;
            }
            //打印三个小精灵的信息供用户选择
            for (int i = 0; i < 3; i++)
            {
                std::cout << p[i] << ":\n";
                poke[p[i]]->print();
            }

            //用户选择
            std::cin >> give;
        }
        //送出这个小精灵
        delete poke[give];

        //小精灵填补空缺
        for (int i = give; i < pokemonNum; i++)
        {
            poke[i] = poke[i + 1];
        }

        //小精灵数量减一
        pokemonNum--;
        std::cout << "您失去了一个小精灵，现在还剩" << pokemonNum << "个小精灵\n";
    }
    else
    {
        std::cout << "用户小精灵数量达到上限\n";
    }
    //释放对手小精灵资源
    delete competitor;
}

//2v2手动小精灵升级赛
void user::upgrade2v2()
{
    //本方小精灵种类
    int uPoke[2];
    //用户有超过两个小精灵，则由用户选出两个小精灵比赛
    if (pokemonNum > 2)
    {
        //打印小精灵信息供用户选择
        for (int i = 0; i < pokemonNum; i++)
        {
            std::cout << i << ":\n";
            poke[i]->print();
        }
        std::cout << "请从您拥有的小精灵中选择两个进行决斗赛\n";
        std::cin >> uPoke[0];
        std::cin >> uPoke[1];
    }
    //用户有两个小精灵，则这两个小精灵参加比赛
    else if (pokemonNum == 2)
    {
        //打印小精灵信息
        std::cout << "您的出战小精灵为：\n";
        for (int i = 0; i <= 1; i++)
        {
            poke[i]->print();
        }
    }
    //用户只有一个小精灵，这个小精灵比赛，此外系统随机分配一个小精灵
    else if (pokemonNum == 1)
    {
        //打印用户有的小精灵
        std::cout << "您的出战小精灵为：\n";
        poke[0]->print();

        //系统随机分配
        std::cout << "系统随机分配一个1级小精灵：\n";
        int p = rand() % 8 + 1;

        switch (p)
        {
        case BULBASAUR:  poke[1] = new bulbasaur;  break;
        case CHARMANDER: poke[1] = new charmander; break;
        case SQUIRTLE:   poke[1] = new squirtle;   break;
        case PIKACHU:    poke[1] = new pikachu;    break;
        case MANKEY:     poke[1] = new mankey;     break;
        case SNORLAX:    poke[1] = new snorlax;    break;
        case CROBAT:	 poke[1] = new crobat;     break;
        case SHUCKLE:	 poke[1] = new shuckle;    break;
        default:break;
        }
        //用户小精灵
        uPoke[0] = 0;
        uPoke[1] = 1;

        //打印小精灵信息
        poke[1]->print();
    }
    //用户没有小精灵 系统随机分配两个小精灵
    else
    {
        std::cout << "您已经输光了所有的小精灵，系统随机分配两个\n";

        for (int i = 0; i <= 1; i++)
        {
            int p = rand() % 8 + 1;
            //系统随机分配一个1级小精灵
            switch (p)
            {
            case BULBASAUR:  poke[i] = new bulbasaur;  break;
            case CHARMANDER: poke[i] = new charmander; break;
            case SQUIRTLE:   poke[i] = new squirtle;   break;
            case PIKACHU:    poke[i] = new pikachu;    break;
            case MANKEY:     poke[i] = new mankey;     break;
            case SNORLAX:    poke[i] = new snorlax;    break;
            case CROBAT:	 poke[i] = new crobat;     break;
            case SHUCKLE:	 poke[i] = new shuckle;    break;
            default:break;
            }
            poke[i]->print();
        }
        uPoke[0] = 0;
        uPoke[1] = 1;
    }
    //选择对手
    std::cout << "请从小精灵列表中中选择2个进行决斗赛\n";
    std::cout << "力量型： 1-猴怪     2-小火龙\n";
    std::cout << "肉盾型： 3-小卡比兽 4-妙蛙种子\n";
    std::cout << "防御型： 5-杰尼龟   6-壶壶\n";
    std::cout << "速度型： 7-皮丘    8-叉字蝠\n";

    //对手小精灵种类
    int comp[2];
    std::cin >> comp[0];
    std::cin >> comp[1];

    //创建小精灵
    pokemon *competitor[2];
    for (int i = 0; i <= 1; i++)
    {
        switch (comp[i])
        {
        case BULBASAUR:  competitor[i] = new bulbasaur;  std::cout << "妙蛙种子 "; break;
        case CHARMANDER: competitor[i] = new charmander; std::cout << "小火龙 ";   break;
        case SQUIRTLE:   competitor[i] = new squirtle;   std::cout << "杰尼龟 ";   break;
        case PIKACHU:    competitor[i] = new pikachu;    std::cout << "皮丘 ";   break;
        case MANKEY:     competitor[i] = new mankey;     std::cout << "猴怪 ";     break;
        case SNORLAX:    competitor[i] = new snorlax;    std::cout << "小卡比兽 ";   break;
        case CROBAT:	 competitor[i] = new crobat;     std::cout << "超音蝠 "; break;
        case SHUCKLE:	 competitor[i] = new shuckle;    std::cout << "壶壶 "; break;
        default:break;
        }

        int opp_level;
        std::cout << "\n请输入第一个小精灵的等级（1-15）\n";
        std::cin >> opp_level;

        //更新小精灵信息打印
        //手动操作加大难度 小精灵等级加一
        competitor[i]->level = opp_level + 1;
        competitor[i]->promoteLevel();
        competitor[i]->print();
    }

    int win = 0; //win=2表示用户赢
    int lose = 0;//lose=2表示用户输
    int time = 0;//计时
    int death[4] = { 0,0,0,0 };//死亡标志
    int sp[4], attr[4], def[4];//小精灵属性

                               //获得四个小精灵的速度，攻击属性和防御值
    sp[0] = competitor[0]->getSpeed();
    sp[1] = competitor[1]->getSpeed();
    sp[2] = poke[uPoke[0]]->getSpeed();
    sp[3] = poke[uPoke[1]]->getSpeed();
    attr[0] = competitor[0]->getAttr();
    attr[1] = competitor[1]->getAttr();
    attr[2] = poke[uPoke[0]]->getAttr();
    attr[3] = poke[uPoke[1]]->getAttr();
    def[0] = competitor[0]->getDef();
    def[1] = competitor[1]->getDef();
    def[2] = poke[uPoke[0]]->getDef();
    def[3] = poke[uPoke[1]]->getDef();

    //双方无小精灵死亡
    while (win != 2 && lose != 2)
    {
        //计时器
        time++;

        //轮到本方一号小精灵出招
        if (time%sp[2] == 0 && death[2] == no)
        {
            int at = -1;//攻击目标（1或2）

                        //对方一号小精灵死亡 则不需要选择 直接攻击对方二号小精灵
            if (death[0] == yes)
            {
                at = 2;
            }
            //对方二号小精灵死亡 则不需要选择 直接攻击对方一号小精灵
            else if (death[1] == yes)
            {
                at = 1;
            }
            //当前小精灵不是群体攻击类型 且对方两个小精灵都没有死亡 
            //则由用户选择攻击哪个小精灵
            else if (poke[uPoke[0]]->atk_kind != 2)
            {
                std::cout << "请选择一号小精灵要攻击的小精灵(1或2）:\n";
                std::cin >> at;
            }
            //当前小精灵为群攻小精灵且对方没有小精灵死亡
            if (at == -1)
            {
                death[0] = competitor[0]->damage(poke[uPoke[0]]->attack(attr[0], def[0]));
                death[1] = competitor[1]->damage(poke[uPoke[0]]->attack(attr[1], def[1]));
                //对方一号小精灵死亡
                if (death[0] == yes)
                {
                    win++;
                }
                //二号小精灵死亡
                if (death[1] == yes)
                {
                    win++;
                }
            }
            //对方有一个小精灵死亡
            else
            {
                death[at - 1] = competitor[at - 1]->damage(poke[uPoke[0]]->attack(attr[at - 1], def[at - 1]));
                if (death[at - 1] == yes)
                {
                    win++;
                }
            }
            //对方两个小精灵都死亡，战斗结束
            if (win == 2)
            {
                break;
            }
        }

        //轮到本方二号小精灵出招
        if (time%sp[3] == 0 && death[3] == no)
        {
            int at = -1;//攻击目标（1或2）

                        //对方一号小精灵死亡 则不需要选择 直接攻击对方二号小精灵
            if (death[0] == yes)
            {
                at = 2;
            }
            //对方二号小精灵死亡 则不需要选择 直接攻击对方一号小精灵
            else if (death[1] == yes)
            {
                at = 1;
            }
            //当前小精灵不是群体攻击类型 且对方两个小精灵都没有死亡 
            //则由用户选择攻击哪个小精灵
            else if (poke[uPoke[1]]->atk_kind != 2)
            {
                std::cout << "请选择二号小精灵要攻击的小精灵(1或2）:\n";
                std::cin >> at;
            }
            //当前小精灵为群攻小精灵且对方没有小精灵死亡
            if (at == -1)
            {
                death[0] = competitor[0]->damage(poke[uPoke[1]]->attack(attr[0], def[0]));
                death[1] = competitor[1]->damage(poke[uPoke[1]]->attack(attr[1], def[1]));
                if (death[0] == yes)
                {
                    win++;
                }
                if (death[1] == yes)
                {
                    win++;
                }
            }
            //对方有一个小精灵死亡
            else
            {
                death[at - 1] = competitor[at - 1]->damage(poke[uPoke[1]]->attack(attr[at - 1], def[at - 1]));
                if (death[at - 1] == yes)
                {
                    win++;
                }
            }
            //对方两个小精灵都死亡，战斗结束
            if (win == 2)
            {
                break;
            }
        }
        //轮到本方一号小精灵出招
        if (time%sp[0] == 0 && death[0] == 0)
        {
            int at = -1;
            //对方一号小精灵死亡 则不需要选择 直接攻击对方二号小精灵
            if (death[2] == yes)
            {
                at = 1;
            }
            //对方二号小精灵死亡 则不需要选择 直接攻击对方一号小精灵
            else if (death[3] == yes)
            {
                at = 0;
            }
            //当前小精灵不是群体攻击类型 且对方两个小精灵都没有死亡 
            //则随机选择攻击哪个小精灵
            else if (competitor[0]->atk_kind != 2)
            {
                at = rand() % 2;
            }

            //当前小精灵为群攻小精灵且对方没有小精灵死亡
            if (at == -1)
            {
                death[2] = poke[uPoke[0]]->damage(competitor[0]->attack(attr[2], def[2]));
                death[3] = poke[uPoke[1]]->damage(competitor[0]->attack(attr[3], def[3]));
                //对方一号小精灵死亡
                if (death[2] == yes)
                {
                    lose++;
                }
                //对方二号小精灵死亡
                if (death[3] == yes)
                {
                    lose++;
                }
            }
            //对方有一个小精灵死亡
            else
            {
                death[at + 2] = poke[uPoke[at]]->damage(competitor[0]->attack(attr[at + 2], def[at + 2]));
                if (death[at + 2] == yes)
                {
                    lose++;
                }
            }
            //对方两个小精灵都死亡，战斗结束
            if (lose == 2)
            {
                break;
            }
        }
        //轮到本方二号小精灵出招
        if (time%sp[1] == 0 && death[1] == yes)
        {
            int at = -1;
            //对方一号小精灵死亡 则不需要选择 直接攻击对方二号小精灵
            if (death[2] == yes)
            {
                at = 1;
            }
            //对方二号小精灵死亡 则不需要选择 直接攻击对方一号小精灵
            else if (death[3] == yes)
            {
                at = 0;
            }
            //当前小精灵不是群体攻击类型 且对方两个小精灵都没有死亡 
            //则随机选择攻击哪个小精灵
            else if (competitor[1]->atk_kind != 2)
            {
                at = rand() % 2;
            }
            //当前小精灵为群攻小精灵且对方没有小精灵死亡
            if (at == -1)
            {
                death[2] = poke[uPoke[0]]->damage(competitor[1]->attack(attr[2], def[2]));
                death[3] = poke[uPoke[1]]->damage(competitor[1]->attack(attr[3], def[3]));
                //对方一号小精灵死亡
                if (death[2] == yes)
                {
                    lose++;
                }
                //对方二号小精灵死亡
                if (death[3] == yes)
                {
                    lose++;
                }
            }
            //对方有一个小精灵死亡
            else
            {
                death[at + 2] = poke[uPoke[at]]->damage(competitor[1]->attack(attr[at + 2], def[at + 2]));
                if (death[at + 2] == yes)
                {
                    lose++;
                }
            }
            //对方两个小精灵都死亡，战斗结束
            if (lose == 2)
            {
                break;
            }
        }//end if (time%sp[1] == 0)
    }//end while (win != 2 && lose != 2)

     //用户胜利
    if (win == 2)
    {
        playNum++;
        winNum++;
        std::cout << "恭喜！您的小精灵获得了胜利!\n\n";
    }
    //用户失败
    else
    {
        playNum++;
        std::cout << "太遗憾了！您的小精灵输了!\n\n";
    }

    //计算经验
    poke[uPoke[0]]->
        promote(poke[uPoke[0]]->
            cal_exp((competitor[0]->level + competitor[1]->level) / 2));
    poke[uPoke[1]]->
        promote(poke[uPoke[1]]->
            cal_exp((competitor[0]->level + competitor[1]->level) / 2));

    //小精灵回血
    poke[uPoke[0]]->recover();
    poke[uPoke[1]]->recover();
    //打印小精灵信息
    poke[uPoke[0]]->print();
    poke[uPoke[1]]->print();

    //释放资源
    delete competitor[0];
    delete competitor[1];
}

//统计勋章数量
void user::medal()
{
    //小精灵个数勋章
    //小精灵数量超过8个，获得高级数量勋章
    if (pokemonNum >= 8)
    {
        NumMedal[0] = yes;
        std::cout << "您的小精灵数量超过8个，获得高级数量勋章一枚！\n";
    }
    //小精灵数量超过6个，获得高级数量勋章
    if (pokemonNum >= 6)
    {
        NumMedal[1] = yes;
        std::cout << "您的满级小精灵数量超过6个，获得中级数量勋章一枚！\n";
    }
    //小精灵数量超过4个，获得高级数量勋章
    if (pokemonNum >= 4)
    {
        NumMedal[2] = yes;
        std::cout << "您的满级小精灵数量超过4个，获得低级数量勋章一枚！\n";
    }

    //满级小精灵勋章
    int fullLevelNum = no;
    for (int i = 0; i < pokemonNum; i++)
    {
        if (poke[i]->level == maxLevel)
        {
            fullLevelNum++;
        }
    }
    //满级小精灵数量超过5个，获得高级满级勋章
    if (fullLevelNum >= 5)
    {
        LevelMedal[0] = yes;
        std::cout << "您的满级小精灵数量超过5个，获得高级满级勋章一枚！\n";
    }
    //满级小精灵数量超过3个，获得中级满级勋章
    if (fullLevelNum >= 3)
    {
        LevelMedal[1] = 1;
        std::cout << "您的满级小精灵数量超过3个，获得中级满级勋章一枚！\n";
    }
    //满级小精灵数量超过1个，获得低级满级勋章
    if (fullLevelNum >= 1)
    {
        LevelMedal[2] = yes;
        std::cout << "您的满级小精灵数量超过1个，获得低级满级勋章一枚！\n";
    }
}

//结束程序
void user::terminate()
{
    char name[msgLength] = { '\0' }; //用户名缓冲区

                                     //从用户类获得用户名
    for (int i = 0; i < maxLength; i++)
    {
        name[i] = userName[i];
    }
    //发送登出请求和用户名
    sendMessage(LOGOUT_REQ, name);

    //等待服务器应答
    while (receiveInfo == WAIT);

    //用户此时为在线状态
    if (recvBuf[0])
    {
        //清空发送接收缓冲器 上锁
        receiveInfo = WAIT;
        clearBuf();

        //将信息同步到服务器
        synchron();
        std::cout << "登出成功！" << std::endl;
    }
    //清空发送接收缓冲器 上锁
    receiveInfo = WAIT;
    clearBuf();

    //结束程序
    stop = yes;
}

//将用户的胜率和小精灵信息同步到服务器
void user::synchron()
{
    //同步胜率
    char chWinRate[msgLength] = { '\0' }; //发送信息

                                          //构造字符形式胜率
    toString(chWinRate, winNum, playNum, 0);

    //发送请求
    sendMessage(SYNCHROWINRATE, chWinRate);

    //等待服务器应答
    while (receiveInfo == WAIT);

    //清空发送接收缓冲器 上锁
    receiveInfo = WAIT;
    clearBuf();

    //有pokemonNum个小精灵 循环pokemonNum次
    for (int i = 0; i < pokemonNum; i++)
    {
        char toStr[msgLength] = { '\0' }; //发送信息
                                          //构造发送信息
        toString(toStr, poke[i]->kind, poke[i]->level, poke[i]->exp);

        //发送请求
        sendMessage(SYNCHRONIZATION, toStr);

        //等待服务器应答
        while (receiveInfo == WAIT);

        //清空发送接收缓冲器 上锁
        receiveInfo = WAIT;
        clearBuf();
    }

    //释放用户所有小精灵资源
    for (int i = 0; i < pokemonNum; i++)
    {
        delete poke[i];
    }
}
