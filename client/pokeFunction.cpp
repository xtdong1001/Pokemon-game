#include"pokemon.h"
using namespace std;

/*小精灵基类*/
//构造函数 等级1 经验0 
pokemon::pokemon()
{
    level = ini_level;
    exp = ini_exp;
}
//伤害函数 若精灵死亡返回1 否则返回0 
int pokemon::damage(int dmg)
{
    //生成一个一百以内的随机数用来确定是否闪避
    int p;
    p = rand();
    p = p % 100;

    //若当前为计算胜率则不打印战斗细节
    if (calWinRate == no)
    {
        switch (kind)
        {
        case BULBASAUR:  cout << "妙蛙种子"; break;
        case CHARMANDER: cout << "小火龙"; break;
        case SQUIRTLE:	 cout << "杰尼龟"; break;
        case PIKACHU:	 cout << "皮丘"; break;
        case MANKEY:	 cout << "猴怪"; break;
        case SNORLAX:	 cout << "小卡比兽"; break;
        case CROBAT:	 cout << "超音蝠"; break;
        case SHUCKLE:	 cout << "壶壶"; break;
        default:break;
        }
    }
    //随机数小于闪避几率 则小精灵闪避
    if (p < dodge)
    {
        dmg = 0;
        if (calWinRate == no)
            cout << "闪避,";
    }
    //随机数大于等于闪避几率 不闪避
    else
    {
        if (calWinRate == no)
            cout << "受到了" << dmg << "点伤害,";
    }

    //血量-伤害
    HP -= dmg;
    //血量
    if (HP <= 0)
    {
        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
            cout << "死亡\n\n";
        HP = 0;
        //小精灵死亡 血量为0 返回1
        return yes;
    }
    //若当前为计算胜率则不打印战斗细节
    //否则输出小精灵剩余血量
    else if (calWinRate == no)
    {
        cout << "剩余血量为" << HP << "\n\n";
    }
    //小精灵未死亡 返回0
    return no;
}

//计算战斗获得经验函数 小精灵获得的经验由对手的等级决定
//参数为对手等级
int pokemon::cal_exp(int opp_level)
{
    //小精灵血量为0 说明小精灵战斗失败
    if (HP == 0)
    {
        //若当前为计算胜率则不打印战斗细节
        //否则输出小精灵获得经验
        if (calWinRate == no)
        {
            switch (kind)
            {
            case BULBASAUR:  cout << "妙蛙种子"; break;
            case CHARMANDER: cout << "小火龙"; break;
            case SQUIRTLE:	 cout << "杰尼龟"; break;
            case PIKACHU:	 cout << "皮丘"; break;
            case MANKEY:	 cout << "猴怪"; break;
            case SNORLAX:	 cout << "小卡比兽"; break;
            case CROBAT:	 cout << "超音蝠"; break;
            case SHUCKLE:	 cout << "壶壶"; break;
            default:break;
            }
            cout << "获得" << opp_level*(opp_level + faiexp) << "点经验\n";
        }
        //小精灵失败 则获得的经验exp=对手等级*（对手等级+faiexp）
        return opp_level*(opp_level + faiexp);
    }
    //小精灵获得胜利
    else
    {
        //若当前为计算胜率则不打印战斗细节
        //否则输出小精灵获得经验
        if (calWinRate == no)
        {
            switch (kind)
            {
            case BULBASAUR:  cout << "妙蛙种子"; break;
            case CHARMANDER: cout << "小火龙"; break;
            case SQUIRTLE:	 cout << "杰尼龟"; break;
            case PIKACHU:	 cout << "皮丘"; break;
            case MANKEY:	 cout << "猴怪"; break;
            case SNORLAX:	 cout << "小卡比兽"; break;
            case CROBAT:	 cout << "超音蝠"; break;
            case SHUCKLE:	 cout << "壶壶"; break;
            default:break;
            }
            cout << "获得" << opp_level*(opp_level + sucexp) << "点经验\n";
        }
        //小精灵失败 则获得的经验exp=对手等级*（对手等级+sucexp）
        return opp_level*(opp_level + sucexp);
    }
}

//获得小精灵属性 
int pokemon::getAttr()
{
    return atk_attribute;
}
//获得小精灵面板防御
int pokemon::getDef()
{
    return def;
}
//获得小精灵面板速度 
int pokemon::getSpeed()
{
    return speed;
}
//获得小精灵等级
int pokemon::getLevel()
{
    return level;
}
//获得小精灵总血量
int pokemon::getTotalHp()
{
    return total_HP;
}
//获得小精灵经验
int pokemon::getExp()
{
    return exp;
}
//获得小精灵面板攻击
int pokemon::getAtk()
{
    return atk;
}
//获得小精灵暴击概率
int pokemon::getCrit()
{
    return crit;
}
//获得小精灵闪避概率
int pokemon::getDodge()
{
    return dodge;
}

//输出小精灵信息 
void pokemon::print()
{
    cout << "种类:";
    switch (kind)
    {
    case BULBASAUR:  cout << "妙蛙种子\n"; break;
    case CHARMANDER: cout << "小火龙\n"; break;
    case SQUIRTLE:	 cout << "杰尼龟\n"; break;
    case PIKACHU:	 cout << "皮丘\n"; break;
    case MANKEY:	 cout << "猴怪\n"; break;
    case SNORLAX:	 cout << "小卡比兽\n"; break;
    case CROBAT:	 cout << "超音蝠\n"; break;
    case SHUCKLE:	 cout << "壶壶\n"; break;
    default:break;
    }
    cout << "等级:" << level << endl;
    cout << "生命:" << HP << endl;
    cout << "经验:" << exp << endl;
    cout << "攻击:" << atk << endl;
    cout << "防御:" << def << endl;
    cout << "速度:" << speed << endl;
    cout << "暴击几率:" << crit << "%" << endl;
    cout << "闪避几率:" << dodge << "%" << endl;
    cout << "\n";
}
//小精灵血量恢复 
void pokemon::recover()
{
    HP = total_HP;
}
//设置小精灵等级
void pokemon::setLevel(int l)
{
    level = l;
}
//析构函数 
pokemon::~pokemon()
{}

//力量子类构造函数 
/*力量型小精灵：猴怪 小火龙
速度：11
暴击几率：30%
闪避几率：10%*/
strength::strength() :pokemon()
{
    speed = stren_speed;
    crit = ini_crit;
    dodge = ini_dodge;
}
//力量子类析构函数 
strength::~strength()
{}

//力量子类升级函数 
/*每级经验exp=level*(level+upexp) 指数型增长
力量型小精灵：
攻击和暴击几率每级增长率为high rate
血量每级增长率为middle rate
防御每级增长率为middle rate
速度、闪避不增长*/
void strength::promote(int add_exp)
{

    if (level < maxLevel)
    {
        exp += add_exp;
    }
    while (exp >= level*(level + upexp) && level < maxLevel)
    {
        exp = exp - level*(level + upexp);
        level++;
        atk = int(high_rate*atk);
        total_HP = int(mid_rate*total_HP);
        HP = total_HP;
        def = int(low_rate*def);
        crit = int(high_rate*crit);
        //小精灵升级提示
        if (kind == MANKEY)
        {
            cout << "恭喜！您的猴怪升级了！\n";
        }
        else if (kind == CHARMANDER)
        {
            cout << "恭喜！您的小火龙升级了！\n";
        }

        //小精灵满级后形态进化
        if (level == maxLevel)
        {
            //猴怪进化为火爆猴
            if (kind == MANKEY)
            {
                cout << "恭喜！您的猴怪已满级，进化为最终形态火爆猴！\n";
            }
            //小火龙进化为喷火龙
            else if (kind == CHARMANDER)
            {
                cout << "恭喜！您的小火龙已满级，进化为最终形态喷火龙！\n";
            }
        }//end of if (level == maxLevel)
    }//end of while (exp >= level*(level + upexp) && level<maxLevel)
    if (level == maxLevel)
    {
        exp = ini_exp;
    }
}

//将小精灵升级到level等级（用于生成一个对手小精灵）
//升级比率和promote函数相同
void strength::promoteLevel()
{
    int i;
    for (i = 1; i < level; i++)
    {
        atk = int(high_rate*atk);
        total_HP = int(mid_rate*total_HP);
        def = int(low_rate*def);
        crit = int(high_rate*crit);
    }
    HP = total_HP;
}

//力量类子类：猴怪 构造函数 
/*猴怪一级：
攻击：mankey_atk
血量：mankey_HP
防御：mankey_def
攻击种类：单体攻击
攻击属性：格斗型*/
mankey::mankey() :strength()
{
    atk = mankey_atk;
    total_HP = mankey_HP;
    HP = mankey_HP;
    def = mankey_def;
    kind = MANKEY;
    atk_kind = SINGLE;
    atk_attribute = FIGHT;
}

//猴怪析构函数 
mankey::~mankey()
{}

//猴怪攻击函数 参数为对方攻击属性attri和防御值opp_def
int mankey::attack(int attri, int opp_def)
{
    //伤害
    int atk_n = 0;

    //生成一百以内的随机数 通过随机数决定是否暴击
    int p = rand() % 100;

    //若当前为计算胜率则不打印战斗细节
    if (calWinRate == no)
    {
        cout << "猴怪";
    }

    //暴击 
    if (p <= crit)
    {
        //暴击伤害为普通伤害的150%
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);
        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出暴击\n";
        }
    }
    else
    {
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)
        atk_n = atk * singlnumer / (atkdenomi + opp_def);
        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出攻击\n";
        }
    }
    //属性相克加成 
    //对方属性为普通 则攻击加成addition130%
    if (attri == NORMAL)
    {
        atk_n = int(addition*atk_n);
    }
    //对方属性为飞行或虫 攻击变为原来的10/13
    else if (attri == FLY || attri == BUG)
    {
        atk_n = int(atk_n / addition);
    }

    //攻击随机范围计算 随机范围为-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //返回伤害
    return atk_n;
}


//力量类子类：小火龙 构造函数 
/*小火龙一级：
攻击：charmander_atk
血量：charmander_HP
防御：charmander_def
攻击种类：群体攻击
攻击属性：火型*/
charmander::charmander() :strength()
{
    atk = charmander_atk;
    total_HP = charmander_HP;
    HP = charmander_HP;
    def = charmander_def;
    kind = CHARMANDER;
    atk_kind = GROUP;
    atk_attribute = FIRE;
}
//小火龙析构函数 
charmander::~charmander()
{}
//小火龙攻击函数 
int charmander::attack(int attri, int opp_def)
{
    //伤害
    int atk_n = 0;

    //生成一百以内的随机数 通过随机数决定是否暴击
    int p = rand() % 100;

    //若当前为计算胜率则不打印战斗细节
    if (calWinRate == no)
        cout << "小火龙";

    //暴击 
    if (p <= crit)
    {
        //暴击伤害为普通伤害的150%
        //atk_n=面板攻击atk*groupnumer/(atkdenomi+对方防御opp_def)*150%
        atk_n = int(atk * groupnumer / (atkdenomi + opp_def)*crit_dmg);
        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出暴击\n";
        }
    }
    else
    {
        //atk_n=面板攻击atk*groupnumer/(atkdenomi+对方防御opp_def)
        atk_n = atk * groupnumer / (atkdenomi + opp_def);
        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出攻击\n";
        }
    }

    //属性相克加成 
    //对方属性为草 则攻击加成addition130%
    if (attri == GRASS)
    {
        atk_n = int(addition*atk_n);
    }
    //对方属性为水 攻击变为原来的10/13
    else if (attri == WATER)
    {
        atk_n = int(atk_n / addition);
    }

    //攻击随机范围计算 随机范围为-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;
    //返回伤害
    return atk_n;
}

//肉盾型精灵 构造函数 
/*肉盾型小精灵：小卡比兽 妙蛙种子
防御：tank_def
速度：tank_speed
暴击几率：30%
闪避几率：5%*/
tank::tank() :pokemon()
{
    def = tank_def;
    speed = tank_speed;
    crit = ini_crit;
    dodge = tank_dodge;
}

//析构函数 
tank::~tank()
{}

//肉盾型精灵升级函数 
/*每级经验exp=level*(level+upexp) 指数型增长
肉盾型小精灵：
攻击和暴击几率每级增长率为low rate
血量每级增长率为high rate
防御每级增长率为middle rate
速度、闪避不增长*/
void tank::promote(int add_exp)
{
    //参数add_exp为增长的经验
    if (level < maxLevel)
    {
        exp += add_exp;
    }
    while (exp >= level*(level + upexp) && level<maxLevel)
    {
        exp = int(exp - level*(level + upexp));
        level++;
        atk = int(low_rate*atk);
        total_HP = int(high_rate*total_HP);
        HP = total_HP;
        def = int(mid_rate*def);
        crit = int(low_rate*crit);
        //小精灵升级提示
        if (kind == SNORLAX)
        {
            cout << "恭喜！您的小卡比兽升级了！\n";
        }
        else if (kind == BULBASAUR)
        {
            cout << "恭喜！您的妙蛙种子升级了！\n";
        }
        //小精灵满级后形态进化
        if (level == maxLevel)
        {
            //小卡比兽进化为卡比兽
            if (kind == SNORLAX)
            {
                cout << "恭喜！您的小卡比兽已满级，进化为最终形态卡比兽！\n";
            }
            //妙蛙种子进化为妙蛙花
            else if (kind == BULBASAUR)
            {
                cout << "恭喜！您的妙蛙种子已满级，进化为最终形态妙蛙花！\n";
            }
        }
    }//end of while (exp >= level*(level + upexp) && level<maxLevel)

    if (level == maxLevel)
    {
        exp = ini_exp;
    }
}

//将小精灵升级到level等级（用于生成一个对手小精灵）
//升级比率和promote函数相同
void tank::promoteLevel()
{
    int i;
    for (i = 1; i < level; i++)
    {
        atk = int(low_rate*atk);
        total_HP = int(high_rate*total_HP);
        def = int(mid_rate*def);
        crit = int(low_rate*crit);
    }
    HP = total_HP;
}

//小卡比兽 构造函数 
/*小卡比兽一级：
攻击：snorlax_atk
血量：snorlax_HP
攻击种类：单体攻击
攻击属性：普通型*/
snorlax::snorlax() :tank()
{
    atk = snorlax_atk;
    HP = snorlax_HP;
    total_HP = HP;
    kind = SNORLAX;
    atk_kind = SINGLE;
    atk_attribute = NORMAL;
}
//小卡比兽析构函数 
snorlax::~snorlax()
{}
//小卡比兽攻击函数 参数为对方攻击属性attri和防御值opp_def
int snorlax::attack(int attri, int opp_def)
{
    //伤害
    int atk_n;

    //生成一百以内的随机数 通过随机数决定是否暴击
    int p = rand() % 100;

    //若当前为计算胜率则不打印战斗细节
    if (calWinRate == no)
    {
        cout << "小卡比兽";
    }

    //暴击
    if (p <= crit)
    {
        //暴击伤害为普通伤害的150%
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);
        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出暴击\n";
        }
    }
    //普通攻击
    else
    {
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)
        atk_n = atk * singlnumer / (atkdenomi + opp_def);
        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出攻击\n";
        }
    }

    //攻击随机范围计算 随机范围为-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //返回伤害
    return atk_n;
}

//妙蛙种子构造函数 
/*妙蛙种子一级：
攻击：bulbasaur_atk
血量：bulbasaur_HP
攻击种类：单体攻击 攻击时自身恢复攻击的20%
攻击属性：草*/
bulbasaur::bulbasaur() :tank()
{
    atk = bulbasaur_atk;
    HP = bulbasaur_HP;
    total_HP = HP;
    kind = BULBASAUR;
    atk_kind = SINGLE;
    atk_attribute = GRASS;
}

//析构函数 
bulbasaur::~bulbasaur()
{}

//妙蛙种子攻击函数 参数为对方攻击属性attri和防御值opp_def
int bulbasaur::attack(int attri, int opp_def)
{
    //伤害
    int atk_n;

    //生成一百以内的随机数 通过随机数决定是否暴击
    int p = rand() % 100;

    //若当前为计算胜率则不打印战斗细节
    if (calWinRate == no)
    {
        cout << "妙蛙种子";
    }

    //暴击 
    if (p <= crit)
    {
        //暴击伤害为普通伤害的150%
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);
        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出暴击\n";
        }
    }
    //普通攻击
    else
    {
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def));
        if (calWinRate == no)
            cout << "发出攻击\n";
    }

    //属性相克加成 
    //对方属性为水 则攻击加成addition130%
    if (attri == WATER)
    {
        atk_n = int(addition*atk_n);
    }
    //对方属性为火 攻击变为原来的10/13
    else if (attri == FIRE)
    {
        atk_n = int(atk_n / addition);
    }

    //攻击随机范围计算 //攻击随机范围计算 随机范围为-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //妙蛙种子血量恢复攻击的recovery
    HP += int(atk_n*recovery);
    int rec;
    rec = int(atk_n*recovery);
    //若当前为计算胜率则不打印战斗细节
    if (calWinRate == no)
    {
        cout << "妙蛙种子恢复" << rec << "点血\n";
    }

    //若血满 则不加血
    if (HP>total_HP)
    {
        HP = total_HP;
    }
    //返回伤害
    return atk_n;
}

//防御型小精灵 构造函数 
/*防御型小精灵：杰尼龟 壶壶
暴击几率：30%
闪避几率：5%*/
defence::defence()
{
    crit = ini_crit;
    dodge = defence_dodge;
}

//析构函数 
defence::~defence()
{}

//升级函数 
/*每级经验exp=level*(level+upexp) 指数型增长
防御型小精灵：
攻击和暴击几率每级增长率为low rate
血量每级增长率为mid rate
防御、闪避每级增长率为high rate
速度、闪避不增长*/
//参数add_exp为增长的经验
void defence::promote(int add_exp)
{
    if (level < maxLevel)
    {
        exp += add_exp;
    }
    while (exp >= level*(level + upexp) && level<maxLevel)
    {
        exp = exp - level*(level + upexp);
        level++;
        atk = int(low_rate*atk);
        total_HP = int(mid_rate*total_HP);
        HP = total_HP;
        def = int(high_rate*def);
        crit = int(low_rate*crit);
        dodge = int(high_rate*dodge);
        //小精灵升级提示
        if (kind == SQUIRTLE)
        {
            cout << "恭喜！您的杰尼龟升级了！\n";
        }
        else if (kind == SHUCKLE)
        {
            cout << "恭喜！您的壶壶升级了！\n";
        }
        //小精灵满级后形态进化
        if (level == maxLevel)
        {
            //杰尼龟进化为水箭龟
            if (kind == SQUIRTLE)
            {
                cout << "恭喜！您的杰尼龟已满级，进化为最终形态水箭龟！\n";
            }
            //壶壶不进化
            else if (kind == SHUCKLE)
            {
                cout << "恭喜！您的壶壶已满级！\n";
            }
        }
    }//end of while (exp >= level*(level + upexp) && level<maxLevel)

    if (level == maxLevel)
    {
        exp = ini_exp;
    }
}

//将小精灵升级到level等级（用于生成一个对手小精灵）
//升级比率和promote函数相同
void defence::promoteLevel()
{
    int i;
    for (i = 1; i < level; i++)
    {
        atk = int(mid_rate * atk);
        HP = int(mid_rate * HP);
        def = int(mid_rate * def);
        crit = int(low_rate * crit);
        dodge = int(high_rate * dodge);
    }
    total_HP = HP;
}

//杰尼龟 构造函数 
/*杰尼龟一级：
攻击：squirtle_atk
血量：squirtle_HP
防御：squirtle_def
速度：squirtle_speed
攻击种类：单体攻击
攻击属性：水*/
squirtle::squirtle() :defence()
{
    atk = squirtle_atk;
    HP = squirtle_HP;
    total_HP = HP;
    def = squirtle_def;
    speed = squirtle_speed;
    kind = SQUIRTLE;
    atk_kind = SINGLE;
    atk_attribute = WATER;
}

//杰尼龟类析构函数
squirtle::~squirtle()
{}

//杰尼龟攻击函数 参数为对方的攻击属性attri和防御值opp_def
int squirtle::attack(int attri, int opp_def)
{
    //伤害
    int atk_n;
    //生成一百以内的随机数 通过随机数决定是否暴击
    int p = rand() % 100;

    //若当前为计算胜率则不打印战斗细节
    if (calWinRate == no)
    {
        cout << "杰尼龟";
    }

    //暴击 
    if (p <= crit)
    {
        //暴击伤害为普通伤害的150%
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);

        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出暴击\n";
        }
    }
    //普通攻击
    else
    {
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)
        atk_n = atk * singlnumer / (atkdenomi + opp_def);
        if (calWinRate == no)
        {
            cout << "发出攻击\n";
        }
    }

    //属性相克加成 
    //对方属性为火 则攻击加成addition130%
    if (attri == FIRE)
    {
        atk_n = int(addition*atk_n);
    }
    //对方属性为草或电 攻击变为原来的10/13
    else if (attri == GRASS || attri == ELECTRIC)
    {
        atk_n = int(atk_n / addition);
    }

    //攻击随机范围计算  随机范围为-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //返回伤害计算值
    return atk_n;
}

//壶壶 构造函数 
/*壶壶一级：
攻击：shuckle_atk
血量：shuckle_HP
防御：shuckle_def
速度：shuckle_speed
攻击种类：单体攻击
攻击属性：虫*/
shuckle::shuckle() :defence()
{
    atk = shuckle_atk;
    HP = shuckle_HP;
    total_HP = HP;
    def = shuckle_def;
    speed = shuckle_speed;
    kind = SHUCKLE;
    atk_kind = SINGLE;
    atk_attribute = BUG;
}

//壶壶析构函数 
shuckle::~shuckle()
{}

//攻击函数 参数为对方的攻击属性attri和防御值opp_def
int shuckle::attack(int attri, int opp_def)
{
    //伤害
    int atk_n;

    //生成一百以内的随机数 通过随机数决定是否暴击
    int p = rand() % 100;

    //若当前为计算胜率则不打印战斗细节
    if (!calWinRate)
    {
        cout << "壶壶";
    }

    //暴击
    if (p <= crit)
    {
        //暴击伤害为普通伤害的150%
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);

        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出暴击\n";
        }
    }
    //普通攻击
    else
    {
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)
        atk_n = atk * singlnumer / (atkdenomi + opp_def);

        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出攻击\n";
        }
    }
    //属性相克加成 
    //对方属性为草 则攻击加成addition130%
    if (attri == GRASS)
    {
        atk_n = int(addition*atk_n);
    }
    //对方属性为火、飞行或格斗 攻击变为原来的10/13
    else if (attri == FIRE || attri == FLY || attri == FIGHT)
    {
        atk_n = int(atk_n / addition);
    }

    //攻击随机范围计算  随机范围为-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //返回伤害
    return atk_n;
}

//速度型 
/*速度型小精灵：皮丘 超音蝠
攻击：quick_atk
生命：quick_HP
防御：quick_def
暴击几率：30%
闪避几率：10%*/
quick::quick() :pokemon()
{
    atk = quick_atk;
    HP = quick_HP;
    total_HP = HP;
    def = quick_def;
    crit = ini_crit;
    dodge = ini_dodge;
}

//析构
quick::~quick()
{}

//速度子类升级函数 
/*每级经验exp=level*(level+upexp) 指数型增长
速度型小精灵：
闪避和暴击几率每级增长率为high rate
血量、防御每级增长率为low rate
攻击每级增长率为middle rate
速度不增长*/
void quick::promote(int add_exp)
{
    if (level < maxLevel)
    {
        exp += add_exp;
    }
    while (exp >= level*(level + upexp) && level<maxLevel)
    {
        exp = (int)exp - level*(level + upexp);
        level++;
        atk = int(mid_rate*atk);
        total_HP = int(low_rate*total_HP);
        HP = total_HP;
        def = int(low_rate*def);
        crit = int(high_rate*crit);
        dodge = int(high_rate*dodge);

        //小精灵升级提示
        if (kind == PIKACHU)
        {
            cout << "恭喜！您的皮丘升级了！\n";
        }
        else if (kind == CROBAT)
        {
            cout << "恭喜！您的超音蝠升级了！\n";
        }
        //小精灵满级后形态进化
        if (level == maxLevel)
        {
            //皮丘进化为雷丘
            if (kind == PIKACHU)
            {
                cout << "恭喜！您的皮丘已满级，进化为最终形态雷丘！\n";
            }
            //超音蝠进化为叉字蝠
            else if (kind == CROBAT)
            {
                cout << "恭喜！您的超音蝠已满级，进化为最终形态叉字蝠！\n";
            }
        }
    }//end of while (exp >= level*(level + upexp) && level<maxLevel)

    if (level == maxLevel)
    {
        exp = ini_exp;
    }
}

//将小精灵升级到level等级（用于生成一个对手小精灵）
//升级比率和promote函数相同
void quick::promoteLevel()
{
    int i;
    for (i = 1; i < level; i++)
    {
        atk = int(mid_rate*atk);
        HP = int(low_rate*HP);
        def = int(low_rate*def);
        crit = int(high_rate*crit);
        dodge = int(high_rate*dodge);
    }
    total_HP = HP;
}

//皮丘构造函数 
/*皮丘一级：
速度：7
攻击种类：单体攻击
攻击属性：电*/
pikachu::pikachu() :quick()
{
    speed = pikachu_speed;
    kind = PIKACHU;
    atk_kind = SINGLE;
    atk_attribute = ELECTRIC;
}
//析构
pikachu::~pikachu()
{}
//皮丘攻击函数  参数为对方的攻击属性attri和防御值opp_def
int pikachu::attack(int attri, int opp_def)
{
    //伤害
    int atk_n;

    //生成一百以内的随机数 通过随机数决定是否暴击
    int p = rand() % 100;

    //若当前为计算胜率则不打印战斗细节
    if (calWinRate == no)
    {
        cout << "皮丘";
    }

    //暴击
    if (p <= crit)
    {
        //暴击伤害为普通伤害的150%
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);

        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出暴击\n";
        }
    }
    //普通攻击
    else
    {
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)
        atk_n = atk * singlnumer / (atkdenomi + opp_def);

        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出攻击\n";
        }
    }
    //属性相克加成 
    //对方属性为水 则攻击加成addition130%
    if (attri == WATER)
    {
        atk_n = int(addition*atk_n);
    }

    //攻击随机范围计算 随机范围为-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //返回伤害
    return atk_n;
}

//超音蝠构造函数 
/*超音蝠一级：
速度：8
攻击种类：单体攻击
攻击属性：飞行型*/
crobat::crobat() :quick()
{
    speed = crobat_speed;
    kind = CROBAT;
    atk_kind = SINGLE;
    atk_attribute = FLY;
}

//析构
crobat::~crobat()
{}

//超音蝠攻击函数 参数为对方的攻击属性attri和防御值opp_def
int crobat::attack(int attri, int opp_def)
{
    //伤害
    int atk_n;

    //生成一百以内的随机数 通过随机数决定是否暴击
    int p = rand() % 100;

    //若当前为计算胜率则不打印战斗细节
    if (calWinRate == no)
    {
        cout << "超音蝠";
    }

    //暴击
    if (p <= crit)
    {
        //暴击伤害为普通伤害的150%
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);

        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出暴击\n";
        }
    }
    //普通攻击
    else
    {
        //atk_n=面板攻击atk*singlnumer/(atkdenomi+对方防御opp_def)
        atk_n = atk * singlnumer / (atkdenomi + opp_def);

        //若当前为计算胜率则不打印战斗细节
        if (calWinRate == no)
        {
            cout << "发出攻击\n";
        }
    }
    //属性相克加成 
    //对方属性为虫、格斗或草 则攻击加成addition130%
    if (attri == BUG || attri == FIGHT || attri == GRASS)
    {
        atk_n = int(addition*atk_n);
    }

    //攻击随机范围计算  随机范围为-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //返回伤害
    return atk_n;
}
