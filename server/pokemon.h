#pragma once
#pragma warning (disable : 4996)
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>  
#include <winsock.h>
#include <winbase.h>
#pragma comment (lib,"ws2_32.lib")


const int BUF_SIZE = 64;  //socket发送缓冲区大小
const int maxLength = 14; //用户名和密码最大长度
const int msgLength = 63; //发送的消息最大长度
const int SUCCESS = 1;    //用户请求成功
const int FAILURE = 0;    //用户请求失败
const int maxLevel = 15;  //最大等级

const int sucexp = 6; //战斗胜利获得的经验参数
const int faiexp = 3; //战斗失败获得的经验参数
const int upexp = 7;  //升级所需的经验参数

const int atkdenomi = 308;  //攻击计算公式分母
const int singlnumer = 350; //单体小精灵攻击系数
const int groupnumer = 200; //群体小精灵攻击系数

const int atkmod = 20; //小精灵攻击不确定范围
const int atkrange = 10; //小精灵攻击不确定范围

const int yes = 1; //是
const int no = 0;  //否

//用户请求
const int SIGNUP = 1;			//用户注册
const int LOGIN = 2;			//用户登录
const int LOGOUT = 3;			//用户登出
const int SEARCHONLINEUSER = 4; //查询在线用户
const int SEARCHPOKEMON = 5;    //查询某注册用户的小精灵
const int UPGRADE = 6;			//1v1升级赛
const int DUEL = 7;			    //1v1决斗赛
const int MEDAL = 8;			//勋章查看
const int STOP = 0;			    //终止
const int DOUBLE_UPGRADE = 9;   //2v2升级赛
const int SEARCHWINRATE = 10;   //查询某用户胜率

//socket发送锁取值
const int SEND = 1;
const int RECV = 1;
const int WAIT = 0;

//登录错误信息
const int PASSWORDERROR = 0; //用户密码错误
const int ONLINE = 1;        //用户已在线
const int INEXISTENCE = 2;   //用户名不存在

//服务器请求
const int SIGNUP_NAME = 1;      //请求发送注册用户名
const int SIGNUP_PASSWORD = 2;  //请求发送注册密码
const int LOGIN_NAME = 3;       //请求发送登录用户名
const int LOGIN_PASSWORD = 4;   //请求发送登录密码
const int LOGOUT_REQ = 5;       //请求登出
const int SEARCHUSER_REQ = 6;   //请求在线用户信息
const int SEARCHPOKEMON_REQ = 7;//请求用户小精灵信息
const int UPDATE_REQ = 8;       //更新本地数据
const int SYNCHRONIZATION = 9;  //请求将数据同步到服务器
const int WINRATE_REQ = 10;     //查询某用户胜率
const int SYNCHROWINRATE = 11;  //请求将胜率同步到服务器

//全局变量
extern char sendBuf[BUF_SIZE]; //发送缓冲区
extern char recvBuf[BUF_SIZE]; //接受缓冲区
extern int sendRequest;		   //发送锁
extern int receiveInfo;		   //读取接受信息锁
extern int stop;			   //程序结束
extern int calWinRate;		   //是否计算赢得比赛的概率

//KIND
const int BULBASAUR = 4;  //妙蛙种子 
const int CHARMANDER = 2; //小火龙
const int SQUIRTLE = 5;   //杰尼龟
const int PIKACHU = 7;    //皮丘
const int MANKEY = 1;     //猴怪  
const int SNORLAX = 3;    //小卡比兽
const int CROBAT = 8;     //超音蝠
const int SHUCKLE = 6;    //壶壶

//小精灵属性
const int ini_level = 1;     //初始等级
const int ini_exp = 0;       //初始经验值
const int ini_crit = 30;     //暴击几率 
const int ini_dodge = 10;    //闪避几率 
const double addition = 1.3; //属性相克加成 
const double crit_dmg = 1.5; //暴击伤害
const double recovery = 0.2; //妙蛙种子自身恢复


//力量型初始属性值
const int stren_speed = 11; //力量型小精灵初始速度：11
//猴怪
const int mankey_atk = 200; //猴怪初始攻击：200
const int mankey_HP = 750;  //猴怪初始生命：750
const int mankey_def = 42;  //猴怪初始防御：42
//小火龙
const int charmander_atk = 160; //小火龙初始攻击：160
const int charmander_HP = 1000; //小火龙初始生命：1000
const int charmander_def = 70;  //小火龙初始防御：70

//肉盾型初始属性
const int tank_def = 100;  //肉盾小精灵初始防御：100
const int tank_speed = 14; //肉盾小精灵初始速度：14
const int tank_dodge = 5;  //肉盾小精灵初始闪避：5%
//卡比兽
const int snorlax_atk = 100; //卡比兽初始攻击：100
const int snorlax_HP = 1800; //卡比兽初始生命：1800
//妙蛙种子
const int bulbasaur_atk = 105; //妙蛙种子初始攻击：105
const int bulbasaur_HP = 1500; //妙蛙种子初始生命：1500

//防御型初始属性
const int defence_dodge = 5; //防御型小精灵初始闪避：5%
//杰尼龟
const int squirtle_def = 260;  //杰尼龟初始防御：260
const int squirtle_speed = 13; //杰尼龟初始速度：13
const int squirtle_atk = 120;  //杰尼龟初始攻击：120
const int squirtle_HP = 1000;  //杰尼龟初始生命：1000
//壶壶
const int shuckle_def = 310;  //壶壶初始防御：310
const int shuckle_speed = 15; //壶壶初始速度：15
const int shuckle_atk = 90;   //壶壶初始攻击：90
const int shuckle_HP = 1000;  //壶壶初始生命：1000

//速度型初始属性
const int quick_atk = 110; //速度小精灵初始攻击：110
const int quick_HP = 700;  //速度小精灵初始生命：700
const int quick_def = 60;  //速度小精灵初始防御：60
//皮丘
const int pikachu_speed = 7; //皮丘初始速度：7
//超音蝠
const int crobat_speed = 8; //超音蝠初始速度：8

//小精灵攻击属性
const int WATER = 1;    //水
const int FIRE = 2;		//火
const int GRASS = 3;	//草
const int ELECTRIC = 4; //电
const int FIGHT = 5;	//格斗
const int NORMAL = 6;	//普通
const int BUG = 7;		//虫
const int FLY = 8;		//飞行

//ATK_KIND
const int SINGLE = 1;  //单体攻击
const int GROUP = 2;   //群体攻击
const int TANK = 3;	   //T

//升级属性增长比例
const double high_rate = 1.07; //高增长率
const double mid_rate = 1.04;  //中增长率
const double low_rate = 1.01;  //低增长率

//用户类声明
class user;

//小精灵类定义
class pokemon
{
public:
    pokemon();						//构造函数
    ~pokemon();						//析构函数
    friend class user;			    //用户类为友元
    virtual void promote(int) {};   //升级函数 
    virtual void promoteLevel() {}; //将小精灵升到某级
    virtual int attack(int, int) { return 0; }; //虚函数 小精灵攻击方式
    int damage(int);	//伤害
    int cal_exp(int);	//计算经验值
    int getAttr();		//获得攻击属性
    int getDef();		//获得面板防御
    int getSpeed();		//获得面板速度
    int getLevel();		//获得当前血量
    int getTotalHp();	//获得总血量
    int getExp();		//获得当前经验值
    int getAtk();		//获得面板攻击值
    int getCrit();		//获得暴击几率
    int getDodge();		//获得闪避几率
    void setLevel(int);	//设置小精灵等级
    void print();		//打印小精灵信息
    void recover();		//小精灵血量恢复

protected:
    int kind;      //种类 
    int atk_attribute; //属性
    int level;     //等级
    int total_HP;  //总生命值
    int HP;		   //生命 
    int exp;	   //经验 
    int def;       //防御 
    int atk;	   //攻击
    int atk_kind;  //攻击类型 
    int speed;     //速度
    int crit;	   //暴击几率（暴击伤害为普攻的150%） 
    int dodge;	   //闪避几率
};

/*力量型精灵*/
class strength :public pokemon
{
public:
    strength();
    ~strength();
    void promote(int);
    void promoteLevel();
};

/*力量型1:单体输出 猴怪*/
class mankey :public strength
{
public:
    mankey();
    ~mankey();
    int attack(int, int); //攻击函数
};

/*力量型2:群体输出小火龙*/
class charmander :public strength
{
public:
    charmander();
    ~charmander();
    int attack(int, int); //攻击函数
};

/*肉盾型精灵*/
class tank :public pokemon
{
public:
    tank();
    ~tank();
    void promote(int);
    void promoteLevel();
};

/*高生命1:T 小卡比兽*/
class snorlax :public tank
{
public:
    snorlax();
    ~snorlax();
    int attack(int, int); //攻击函数
};

/*高生命2:自身恢复 妙蛙种子*/
class bulbasaur :public tank
{
public:
    bulbasaur();
    ~bulbasaur();
    int attack(int, int); //攻击函数
};

/*防御型精灵*/
class defence :public pokemon
{
public:
    defence();
    ~defence();
    void promote(int);
    void promoteLevel();
};

/*防御1：杰尼龟*/
class squirtle :public defence
{
public:
    squirtle();
    ~squirtle();
    int attack(int, int); //攻击函数
};

/*防御2：壶壶*/
class shuckle :public defence
{
public:
    shuckle();
    ~shuckle();
    int attack(int, int); //攻击函数
};


/*速度型精灵*/
class quick :public pokemon
{
public:
    quick();
    ~quick();
    void promote(int);
    void promoteLevel();
};

/*速度1:皮丘*/
class pikachu :public quick
{
public:
    pikachu();
    ~pikachu();
    int attack(int, int); //攻击函数
};

/*速度2:超音蝠*/
class crobat :public quick
{
public:
    crobat();
    ~crobat();
    int attack(int, int); //攻击函数
};

//用户类 
class user
{
public:
    user();
    ~user();
    void signUp();  //用户注册 
    void logIn();   //用户登录 
    void logOut();	//用户登出 
    void searchOnlineUser();	//查询在线用户 
    void searchPokemon();		//查询某注册用户的小精灵 
    void searchWinRate();       //查询某用户的胜率
    void upgrade();				//升级赛
    void duel();				//决斗赛
    void medal();				//用户勋章发放	
    void upgrade2v2();			//2v2手动升级赛
    void terminate();			//终止 
private:
    char userName[maxLength];	//用户名
    char password[maxLength];	//密码
    pokemon *poke[30];			//用户拥有的小精灵
    int pokemonNum;				//小精灵个数
    int NumMedal[3];			//小精灵个数勋章
    int LevelMedal[3];			//满级小精灵勋章
    void synchron();			//同步信息到服务器
    int winNum;					//赢的次数
    int playNum;				//总次数
    int fighting(pokemon*, pokemon*); //小精灵打架
};


int client();						        //用户端socket通信
void clearBuf();							//清空发送接收缓冲区
void sendMessage(char, char*);				//生成发送信息
int isCorrectPword(char *);					//判断密码格式是否正确
int isCorrectName(char *);					//判断用户名格式是否正确
void readInfo(char*, int&, int&, int&);		//获得小精灵信息
void CalWinRate(pokemon *, int, int);		//计算胜率
double simuFight(pokemon*, pokemon*);		//模拟战斗
void toString(char*, int, int, int);		//生成发送信息
void toChar(int, char*, int&);