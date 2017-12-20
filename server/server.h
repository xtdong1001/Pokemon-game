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

const int BUF_SIZE = 64;  //socket���ͻ�������С
const int maxLength = 14; //�û�����������󳤶�
const int msgLength = 63; //���͵���Ϣ��󳤶�

//�û�״̬
const int online = 1;  //�û�����
const int offline = 0; //�û�������

//�û�����
const int SIGNUP_NAME = 1;       //������ע���û���
const int SIGNUP_PASSWORD = 2;   //������ע������
const int LOGIN_NAME = 3;        //�����͵�¼�û���
const int LOGIN_PASSWORD = 4;    //�����͵�¼����
const int LOGOUT_REQ = 5;        //����ǳ�
const int SEARCHUSER_REQ = 6;    //���������û���Ϣ
const int SEARCHPOKEMON_REQ = 7; //�����û�С������Ϣ
const int UPDATE_REQ = 8;        //���±�������
const int SYNCHRONIZATION = 9;   //��������ͬ����������
const int WINRATE_REQ = 10;      //��ѯĳ�û�ʤ��
const int SYNCHROWINRATE = 11;   //����ʤ��ͬ����������

const int SUCCESS = 1;       //����ɹ�
const int FAILURE = 0;       //����ʧ��
const int PASSWORDERROR = 0; //�������
const int ALREADYONLINE = 1; //�Ѿ���¼
const int INEXISTENCE = 2;   //�û���������
const int REQUEST = 1;       //����
const int OFFLINE = 1;       //�û�δ��¼


//���ݿ��û��ṹ
struct user
{
    std::string userName;//�û��� primary key
    std::string passWord;//����
    int state;			 //�û�״̬
    int winNum;          //ʤ��--Ӯ�Ĵ���
    int sumNum;			 //ʤ��--�ܴ���
    ORMAP("user", userName, passWord, state, winNum, sumNum);
    //�����ݿ��д����û�����
};

struct elf
{
    int primaryKey;
    std::string userName;//�����û���
    int elfKind;   //����
    int level;     //�ȼ�
    int exp;	   //���� 
    ORMAP("elf", primaryKey, userName, elfKind, level, exp);//�����ݿ��д���С�������
};


int server(LPVOID);			//socket��������
void toString(char*, elf);  //��С������Ϣת��Ϊ�ַ�����				
void winRateStr(char*, int, int, int);  //���û�ʤ��ת��Ϊ�ַ���
void readInfo(char*, int&, int&, int&); //��ȡС������Ϣ
void toChar(int, char*, int&);			//������ת��Ϊ�ַ���
