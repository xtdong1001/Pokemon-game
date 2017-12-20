#pragma once
#pragma warning (disable : 4996)
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<windows.h>  
#include<winsock.h>
#include<winbase.h>
#include"ORMLite.h"
#include"sqlite3.h"
#pragma comment (lib,"ws2_32.lib")

const int BUF_SIZE = 64;  //socket发送缓冲区大小
const int maxLength = 14; //用户名和密码最大长度
const int msgLength = 63; //发送的消息最大长度

//用户状态
const int online = 1;  //用户在线
const int offline = 0; //用户不在线

//用户请求
const int SIGNUP_NAME = 1;       //请求发送注册用户名
const int SIGNUP_PASSWORD = 2;   //请求发送注册密码
const int LOGIN_NAME = 3;        //请求发送登录用户名
const int LOGIN_PASSWORD = 4;    //请求发送登录密码
const int LOGOUT_REQ = 5;        //请求登出
const int SEARCHUSER_REQ = 6;    //请求在线用户信息
const int SEARCHPOKEMON_REQ = 7; //请求用户小精灵信息
const int UPDATE_REQ = 8;        //更新本地数据
const int SYNCHRONIZATION = 9;   //请求将数据同步到服务器
const int WINRATE_REQ = 10;      //查询某用户胜率
const int SYNCHROWINRATE = 11;   //请求将胜率同步到服务器

const int SUCCESS = 1;       //请求成功
const int FAILURE = 0;       //请求失败
const int PASSWORDERROR = 0; //密码错误
const int ALREADYONLINE = 1; //已经登录
const int INEXISTENCE = 2;   //用户名不存在
const int REQUEST = 1;       //请求
const int OFFLINE = 1;       //用户未登录


//数据库用户结构
struct user
{
    std::string userName;//用户名 primary key
    std::string passWord;//密码
    int state;			 //用户状态
    int winNum;          //胜率--赢的次数
    int sumNum;			 //胜率--总次数
    ORMAP("user", userName, passWord, state, winNum, sumNum);
    //在数据库中创建用户表项
};

struct elf
{
    int primaryKey;
    std::string userName;//所属用户名
    int elfKind;   //种类
    int level;     //等级
    int exp;	   //经验 
    ORMAP("elf", primaryKey, userName, elfKind, level, exp);//在数据库中创建小精灵表项
};


int server(LPVOID);			//socket服务器端
void toString(char*, elf);  //将小精灵信息转化为字符数组				
void winRateStr(char*, int, int, int);  //将用户胜率转化为字符串
void readInfo(char*, int&, int&, int&); //读取小精灵信息
void toChar(int, char*, int&);			//将整数转化为字符串
