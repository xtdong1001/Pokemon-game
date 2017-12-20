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


const int BUF_SIZE = 64;  //socket���ͻ�������С
const int maxLength = 14; //�û�����������󳤶�
const int msgLength = 63; //���͵���Ϣ��󳤶�
const int SUCCESS = 1;    //�û�����ɹ�
const int FAILURE = 0;    //�û�����ʧ��
const int maxLevel = 15;  //���ȼ�

const int sucexp = 6; //ս��ʤ����õľ������
const int faiexp = 3; //ս��ʧ�ܻ�õľ������
const int upexp = 7;  //��������ľ������

const int atkdenomi = 308;  //�������㹫ʽ��ĸ
const int singlnumer = 350; //����С���鹥��ϵ��
const int groupnumer = 200; //Ⱥ��С���鹥��ϵ��

const int atkmod = 20; //С���鹥����ȷ����Χ
const int atkrange = 10; //С���鹥����ȷ����Χ

const int yes = 1; //��
const int no = 0;  //��

//�û�����
const int SIGNUP = 1;			//�û�ע��
const int LOGIN = 2;			//�û���¼
const int LOGOUT = 3;			//�û��ǳ�
const int SEARCHONLINEUSER = 4; //��ѯ�����û�
const int SEARCHPOKEMON = 5;    //��ѯĳע���û���С����
const int UPGRADE = 6;			//1v1������
const int DUEL = 7;			    //1v1������
const int MEDAL = 8;			//ѫ�²鿴
const int STOP = 0;			    //��ֹ
const int DOUBLE_UPGRADE = 9;   //2v2������
const int SEARCHWINRATE = 10;   //��ѯĳ�û�ʤ��

//socket������ȡֵ
const int SEND = 1;
const int RECV = 1;
const int WAIT = 0;

//��¼������Ϣ
const int PASSWORDERROR = 0; //�û��������
const int ONLINE = 1;        //�û�������
const int INEXISTENCE = 2;   //�û���������

//����������
const int SIGNUP_NAME = 1;      //������ע���û���
const int SIGNUP_PASSWORD = 2;  //������ע������
const int LOGIN_NAME = 3;       //�����͵�¼�û���
const int LOGIN_PASSWORD = 4;   //�����͵�¼����
const int LOGOUT_REQ = 5;       //����ǳ�
const int SEARCHUSER_REQ = 6;   //���������û���Ϣ
const int SEARCHPOKEMON_REQ = 7;//�����û�С������Ϣ
const int UPDATE_REQ = 8;       //���±�������
const int SYNCHRONIZATION = 9;  //��������ͬ����������
const int WINRATE_REQ = 10;     //��ѯĳ�û�ʤ��
const int SYNCHROWINRATE = 11;  //����ʤ��ͬ����������

//ȫ�ֱ���
extern char sendBuf[BUF_SIZE]; //���ͻ�����
extern char recvBuf[BUF_SIZE]; //���ܻ�����
extern int sendRequest;		   //������
extern int receiveInfo;		   //��ȡ������Ϣ��
extern int stop;			   //�������
extern int calWinRate;		   //�Ƿ����Ӯ�ñ����ĸ���

//KIND
const int BULBASAUR = 4;  //�������� 
const int CHARMANDER = 2; //С����
const int SQUIRTLE = 5;   //�����
const int PIKACHU = 7;    //Ƥ��
const int MANKEY = 1;     //���  
const int SNORLAX = 3;    //С������
const int CROBAT = 8;     //������
const int SHUCKLE = 6;    //����

//С��������
const int ini_level = 1;     //��ʼ�ȼ�
const int ini_exp = 0;       //��ʼ����ֵ
const int ini_crit = 30;     //�������� 
const int ini_dodge = 10;    //���ܼ��� 
const double addition = 1.3; //������˼ӳ� 
const double crit_dmg = 1.5; //�����˺�
const double recovery = 0.2; //������������ָ�


//�����ͳ�ʼ����ֵ
const int stren_speed = 11; //������С�����ʼ�ٶȣ�11
//���
const int mankey_atk = 200; //��ֳ�ʼ������200
const int mankey_HP = 750;  //��ֳ�ʼ������750
const int mankey_def = 42;  //��ֳ�ʼ������42
//С����
const int charmander_atk = 160; //С������ʼ������160
const int charmander_HP = 1000; //С������ʼ������1000
const int charmander_def = 70;  //С������ʼ������70

//����ͳ�ʼ����
const int tank_def = 100;  //���С�����ʼ������100
const int tank_speed = 14; //���С�����ʼ�ٶȣ�14
const int tank_dodge = 5;  //���С�����ʼ���ܣ�5%
//������
const int snorlax_atk = 100; //�����޳�ʼ������100
const int snorlax_HP = 1800; //�����޳�ʼ������1800
//��������
const int bulbasaur_atk = 105; //�������ӳ�ʼ������105
const int bulbasaur_HP = 1500; //�������ӳ�ʼ������1500

//�����ͳ�ʼ����
const int defence_dodge = 5; //������С�����ʼ���ܣ�5%
//�����
const int squirtle_def = 260;  //������ʼ������260
const int squirtle_speed = 13; //������ʼ�ٶȣ�13
const int squirtle_atk = 120;  //������ʼ������120
const int squirtle_HP = 1000;  //������ʼ������1000
//����
const int shuckle_def = 310;  //������ʼ������310
const int shuckle_speed = 15; //������ʼ�ٶȣ�15
const int shuckle_atk = 90;   //������ʼ������90
const int shuckle_HP = 1000;  //������ʼ������1000

//�ٶ��ͳ�ʼ����
const int quick_atk = 110; //�ٶ�С�����ʼ������110
const int quick_HP = 700;  //�ٶ�С�����ʼ������700
const int quick_def = 60;  //�ٶ�С�����ʼ������60
//Ƥ��
const int pikachu_speed = 7; //Ƥ���ʼ�ٶȣ�7
//������
const int crobat_speed = 8; //�������ʼ�ٶȣ�8

//С���鹥������
const int WATER = 1;    //ˮ
const int FIRE = 2;		//��
const int GRASS = 3;	//��
const int ELECTRIC = 4; //��
const int FIGHT = 5;	//��
const int NORMAL = 6;	//��ͨ
const int BUG = 7;		//��
const int FLY = 8;		//����

//ATK_KIND
const int SINGLE = 1;  //���幥��
const int GROUP = 2;   //Ⱥ�幥��
const int TANK = 3;	   //T

//����������������
const double high_rate = 1.07; //��������
const double mid_rate = 1.04;  //��������
const double low_rate = 1.01;  //��������

//�û�������
class user;

//С�����ඨ��
class pokemon
{
public:
    pokemon();						//���캯��
    ~pokemon();						//��������
    friend class user;			    //�û���Ϊ��Ԫ
    virtual void promote(int) {};   //�������� 
    virtual void promoteLevel() {}; //��С��������ĳ��
    virtual int attack(int, int) { return 0; }; //�麯�� С���鹥����ʽ
    int damage(int);	//�˺�
    int cal_exp(int);	//���㾭��ֵ
    int getAttr();		//��ù�������
    int getDef();		//���������
    int getSpeed();		//�������ٶ�
    int getLevel();		//��õ�ǰѪ��
    int getTotalHp();	//�����Ѫ��
    int getExp();		//��õ�ǰ����ֵ
    int getAtk();		//�����幥��ֵ
    int getCrit();		//��ñ�������
    int getDodge();		//������ܼ���
    void setLevel(int);	//����С����ȼ�
    void print();		//��ӡС������Ϣ
    void recover();		//С����Ѫ���ָ�

protected:
    int kind;      //���� 
    int atk_attribute; //����
    int level;     //�ȼ�
    int total_HP;  //������ֵ
    int HP;		   //���� 
    int exp;	   //���� 
    int def;       //���� 
    int atk;	   //����
    int atk_kind;  //�������� 
    int speed;     //�ٶ�
    int crit;	   //�������ʣ������˺�Ϊ�չ���150%�� 
    int dodge;	   //���ܼ���
};

/*�����;���*/
class strength :public pokemon
{
public:
    strength();
    ~strength();
    void promote(int);
    void promoteLevel();
};

/*������1:������� ���*/
class mankey :public strength
{
public:
    mankey();
    ~mankey();
    int attack(int, int); //��������
};

/*������2:Ⱥ�����С����*/
class charmander :public strength
{
public:
    charmander();
    ~charmander();
    int attack(int, int); //��������
};

/*����;���*/
class tank :public pokemon
{
public:
    tank();
    ~tank();
    void promote(int);
    void promoteLevel();
};

/*������1:T С������*/
class snorlax :public tank
{
public:
    snorlax();
    ~snorlax();
    int attack(int, int); //��������
};

/*������2:����ָ� ��������*/
class bulbasaur :public tank
{
public:
    bulbasaur();
    ~bulbasaur();
    int attack(int, int); //��������
};

/*�����;���*/
class defence :public pokemon
{
public:
    defence();
    ~defence();
    void promote(int);
    void promoteLevel();
};

/*����1�������*/
class squirtle :public defence
{
public:
    squirtle();
    ~squirtle();
    int attack(int, int); //��������
};

/*����2������*/
class shuckle :public defence
{
public:
    shuckle();
    ~shuckle();
    int attack(int, int); //��������
};


/*�ٶ��;���*/
class quick :public pokemon
{
public:
    quick();
    ~quick();
    void promote(int);
    void promoteLevel();
};

/*�ٶ�1:Ƥ��*/
class pikachu :public quick
{
public:
    pikachu();
    ~pikachu();
    int attack(int, int); //��������
};

/*�ٶ�2:������*/
class crobat :public quick
{
public:
    crobat();
    ~crobat();
    int attack(int, int); //��������
};

//�û��� 
class user
{
public:
    user();
    ~user();
    void signUp();  //�û�ע�� 
    void logIn();   //�û���¼ 
    void logOut();	//�û��ǳ� 
    void searchOnlineUser();	//��ѯ�����û� 
    void searchPokemon();		//��ѯĳע���û���С���� 
    void searchWinRate();       //��ѯĳ�û���ʤ��
    void upgrade();				//������
    void duel();				//������
    void medal();				//�û�ѫ�·���	
    void upgrade2v2();			//2v2�ֶ�������
    void terminate();			//��ֹ 
private:
    char userName[maxLength];	//�û���
    char password[maxLength];	//����
    pokemon *poke[30];			//�û�ӵ�е�С����
    int pokemonNum;				//С�������
    int NumMedal[3];			//С�������ѫ��
    int LevelMedal[3];			//����С����ѫ��
    void synchron();			//ͬ����Ϣ��������
    int winNum;					//Ӯ�Ĵ���
    int playNum;				//�ܴ���
    int fighting(pokemon*, pokemon*); //С������
};


int client();						        //�û���socketͨ��
void clearBuf();							//��շ��ͽ��ջ�����
void sendMessage(char, char*);				//���ɷ�����Ϣ
int isCorrectPword(char *);					//�ж������ʽ�Ƿ���ȷ
int isCorrectName(char *);					//�ж��û�����ʽ�Ƿ���ȷ
void readInfo(char*, int&, int&, int&);		//���С������Ϣ
void CalWinRate(pokemon *, int, int);		//����ʤ��
double simuFight(pokemon*, pokemon*);		//ģ��ս��
void toString(char*, int, int, int);		//���ɷ�����Ϣ
void toChar(int, char*, int&);