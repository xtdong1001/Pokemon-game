#include"pokemon.h"
using namespace std;

/*С�������*/
//���캯�� �ȼ�1 ����0 
pokemon::pokemon()
{
    level = ini_level;
    exp = ini_exp;
}
//�˺����� ��������������1 ���򷵻�0 
int pokemon::damage(int dmg)
{
    //����һ��һ�����ڵ����������ȷ���Ƿ�����
    int p;
    p = rand();
    p = p % 100;

    //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
    if (calWinRate == no)
    {
        switch (kind)
        {
        case BULBASAUR:  cout << "��������"; break;
        case CHARMANDER: cout << "С����"; break;
        case SQUIRTLE:	 cout << "�����"; break;
        case PIKACHU:	 cout << "Ƥ��"; break;
        case MANKEY:	 cout << "���"; break;
        case SNORLAX:	 cout << "С������"; break;
        case CROBAT:	 cout << "������"; break;
        case SHUCKLE:	 cout << "����"; break;
        default:break;
        }
    }
    //�����С�����ܼ��� ��С��������
    if (p < dodge)
    {
        dmg = 0;
        if (calWinRate == no)
            cout << "����,";
    }
    //��������ڵ������ܼ��� ������
    else
    {
        if (calWinRate == no)
            cout << "�ܵ���" << dmg << "���˺�,";
    }

    //Ѫ��-�˺�
    HP -= dmg;
    //Ѫ��
    if (HP <= 0)
    {
        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
            cout << "����\n\n";
        HP = 0;
        //С�������� Ѫ��Ϊ0 ����1
        return yes;
    }
    //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
    //�������С����ʣ��Ѫ��
    else if (calWinRate == no)
    {
        cout << "ʣ��Ѫ��Ϊ" << HP << "\n\n";
    }
    //С����δ���� ����0
    return no;
}

//����ս����þ��麯�� С�����õľ����ɶ��ֵĵȼ�����
//����Ϊ���ֵȼ�
int pokemon::cal_exp(int opp_level)
{
    //С����Ѫ��Ϊ0 ˵��С����ս��ʧ��
    if (HP == 0)
    {
        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        //�������С�����þ���
        if (calWinRate == no)
        {
            switch (kind)
            {
            case BULBASAUR:  cout << "��������"; break;
            case CHARMANDER: cout << "С����"; break;
            case SQUIRTLE:	 cout << "�����"; break;
            case PIKACHU:	 cout << "Ƥ��"; break;
            case MANKEY:	 cout << "���"; break;
            case SNORLAX:	 cout << "С������"; break;
            case CROBAT:	 cout << "������"; break;
            case SHUCKLE:	 cout << "����"; break;
            default:break;
            }
            cout << "���" << opp_level*(opp_level + faiexp) << "�㾭��\n";
        }
        //С����ʧ�� ���õľ���exp=���ֵȼ�*�����ֵȼ�+faiexp��
        return opp_level*(opp_level + faiexp);
    }
    //С������ʤ��
    else
    {
        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        //�������С�����þ���
        if (calWinRate == no)
        {
            switch (kind)
            {
            case BULBASAUR:  cout << "��������"; break;
            case CHARMANDER: cout << "С����"; break;
            case SQUIRTLE:	 cout << "�����"; break;
            case PIKACHU:	 cout << "Ƥ��"; break;
            case MANKEY:	 cout << "���"; break;
            case SNORLAX:	 cout << "С������"; break;
            case CROBAT:	 cout << "������"; break;
            case SHUCKLE:	 cout << "����"; break;
            default:break;
            }
            cout << "���" << opp_level*(opp_level + sucexp) << "�㾭��\n";
        }
        //С����ʧ�� ���õľ���exp=���ֵȼ�*�����ֵȼ�+sucexp��
        return opp_level*(opp_level + sucexp);
    }
}

//���С�������� 
int pokemon::getAttr()
{
    return atk_attribute;
}
//���С����������
int pokemon::getDef()
{
    return def;
}
//���С��������ٶ� 
int pokemon::getSpeed()
{
    return speed;
}
//���С����ȼ�
int pokemon::getLevel()
{
    return level;
}
//���С������Ѫ��
int pokemon::getTotalHp()
{
    return total_HP;
}
//���С���龭��
int pokemon::getExp()
{
    return exp;
}
//���С������幥��
int pokemon::getAtk()
{
    return atk;
}
//���С���鱩������
int pokemon::getCrit()
{
    return crit;
}
//���С�������ܸ���
int pokemon::getDodge()
{
    return dodge;
}

//���С������Ϣ 
void pokemon::print()
{
    cout << "����:";
    switch (kind)
    {
    case BULBASAUR:  cout << "��������\n"; break;
    case CHARMANDER: cout << "С����\n"; break;
    case SQUIRTLE:	 cout << "�����\n"; break;
    case PIKACHU:	 cout << "Ƥ��\n"; break;
    case MANKEY:	 cout << "���\n"; break;
    case SNORLAX:	 cout << "С������\n"; break;
    case CROBAT:	 cout << "������\n"; break;
    case SHUCKLE:	 cout << "����\n"; break;
    default:break;
    }
    cout << "�ȼ�:" << level << endl;
    cout << "����:" << HP << endl;
    cout << "����:" << exp << endl;
    cout << "����:" << atk << endl;
    cout << "����:" << def << endl;
    cout << "�ٶ�:" << speed << endl;
    cout << "��������:" << crit << "%" << endl;
    cout << "���ܼ���:" << dodge << "%" << endl;
    cout << "\n";
}
//С����Ѫ���ָ� 
void pokemon::recover()
{
    HP = total_HP;
}
//����С����ȼ�
void pokemon::setLevel(int l)
{
    level = l;
}
//�������� 
pokemon::~pokemon()
{}

//�������๹�캯�� 
/*������С���飺��� С����
�ٶȣ�11
�������ʣ�30%
���ܼ��ʣ�10%*/
strength::strength() :pokemon()
{
    speed = stren_speed;
    crit = ini_crit;
    dodge = ini_dodge;
}
//���������������� 
strength::~strength()
{}

//���������������� 
/*ÿ������exp=level*(level+upexp) ָ��������
������С���飺
�����ͱ�������ÿ��������Ϊhigh rate
Ѫ��ÿ��������Ϊmiddle rate
����ÿ��������Ϊmiddle rate
�ٶȡ����ܲ�����*/
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
        //С����������ʾ
        if (kind == MANKEY)
        {
            cout << "��ϲ�����ĺ�������ˣ�\n";
        }
        else if (kind == CHARMANDER)
        {
            cout << "��ϲ������С���������ˣ�\n";
        }

        //С������������̬����
        if (level == maxLevel)
        {
            //��ֽ���Ϊ�𱬺�
            if (kind == MANKEY)
            {
                cout << "��ϲ�����ĺ��������������Ϊ������̬�𱬺\n";
            }
            //С��������Ϊ�����
            else if (kind == CHARMANDER)
            {
                cout << "��ϲ������С����������������Ϊ������̬�������\n";
            }
        }//end of if (level == maxLevel)
    }//end of while (exp >= level*(level + upexp) && level<maxLevel)
    if (level == maxLevel)
    {
        exp = ini_exp;
    }
}

//��С����������level�ȼ�����������һ������С���飩
//�������ʺ�promote������ͬ
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

//���������ࣺ��� ���캯�� 
/*���һ����
������mankey_atk
Ѫ����mankey_HP
������mankey_def
�������ࣺ���幥��
�������ԣ�����*/
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

//����������� 
mankey::~mankey()
{}

//��ֹ������� ����Ϊ�Է���������attri�ͷ���ֵopp_def
int mankey::attack(int attri, int opp_def)
{
    //�˺�
    int atk_n = 0;

    //����һ�����ڵ������ ͨ������������Ƿ񱩻�
    int p = rand() % 100;

    //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
    if (calWinRate == no)
    {
        cout << "���";
    }

    //���� 
    if (p <= crit)
    {
        //�����˺�Ϊ��ͨ�˺���150%
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);
        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }
    else
    {
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)
        atk_n = atk * singlnumer / (atkdenomi + opp_def);
        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }
    //������˼ӳ� 
    //�Է�����Ϊ��ͨ �򹥻��ӳ�addition130%
    if (attri == NORMAL)
    {
        atk_n = int(addition*atk_n);
    }
    //�Է�����Ϊ���л�� ������Ϊԭ����10/13
    else if (attri == FLY || attri == BUG)
    {
        atk_n = int(atk_n / addition);
    }

    //���������Χ���� �����ΧΪ-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //�����˺�
    return atk_n;
}


//���������ࣺС���� ���캯�� 
/*С����һ����
������charmander_atk
Ѫ����charmander_HP
������charmander_def
�������ࣺȺ�幥��
�������ԣ�����*/
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
//С������������ 
charmander::~charmander()
{}
//С������������ 
int charmander::attack(int attri, int opp_def)
{
    //�˺�
    int atk_n = 0;

    //����һ�����ڵ������ ͨ������������Ƿ񱩻�
    int p = rand() % 100;

    //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
    if (calWinRate == no)
        cout << "С����";

    //���� 
    if (p <= crit)
    {
        //�����˺�Ϊ��ͨ�˺���150%
        //atk_n=��幥��atk*groupnumer/(atkdenomi+�Է�����opp_def)*150%
        atk_n = int(atk * groupnumer / (atkdenomi + opp_def)*crit_dmg);
        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }
    else
    {
        //atk_n=��幥��atk*groupnumer/(atkdenomi+�Է�����opp_def)
        atk_n = atk * groupnumer / (atkdenomi + opp_def);
        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }

    //������˼ӳ� 
    //�Է�����Ϊ�� �򹥻��ӳ�addition130%
    if (attri == GRASS)
    {
        atk_n = int(addition*atk_n);
    }
    //�Է�����Ϊˮ ������Ϊԭ����10/13
    else if (attri == WATER)
    {
        atk_n = int(atk_n / addition);
    }

    //���������Χ���� �����ΧΪ-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;
    //�����˺�
    return atk_n;
}

//����;��� ���캯�� 
/*�����С���飺С������ ��������
������tank_def
�ٶȣ�tank_speed
�������ʣ�30%
���ܼ��ʣ�5%*/
tank::tank() :pokemon()
{
    def = tank_def;
    speed = tank_speed;
    crit = ini_crit;
    dodge = tank_dodge;
}

//�������� 
tank::~tank()
{}

//����;����������� 
/*ÿ������exp=level*(level+upexp) ָ��������
�����С���飺
�����ͱ�������ÿ��������Ϊlow rate
Ѫ��ÿ��������Ϊhigh rate
����ÿ��������Ϊmiddle rate
�ٶȡ����ܲ�����*/
void tank::promote(int add_exp)
{
    //����add_expΪ�����ľ���
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
        //С����������ʾ
        if (kind == SNORLAX)
        {
            cout << "��ϲ������С�����������ˣ�\n";
        }
        else if (kind == BULBASAUR)
        {
            cout << "��ϲ�������������������ˣ�\n";
        }
        //С������������̬����
        if (level == maxLevel)
        {
            //С�����޽���Ϊ������
            if (kind == SNORLAX)
            {
                cout << "��ϲ������С������������������Ϊ������̬�����ޣ�\n";
            }
            //�������ӽ���Ϊ���ܻ�
            else if (kind == BULBASAUR)
            {
                cout << "��ϲ��������������������������Ϊ������̬���ܻ���\n";
            }
        }
    }//end of while (exp >= level*(level + upexp) && level<maxLevel)

    if (level == maxLevel)
    {
        exp = ini_exp;
    }
}

//��С����������level�ȼ�����������һ������С���飩
//�������ʺ�promote������ͬ
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

//С������ ���캯�� 
/*С������һ����
������snorlax_atk
Ѫ����snorlax_HP
�������ࣺ���幥��
�������ԣ���ͨ��*/
snorlax::snorlax() :tank()
{
    atk = snorlax_atk;
    HP = snorlax_HP;
    total_HP = HP;
    kind = SNORLAX;
    atk_kind = SINGLE;
    atk_attribute = NORMAL;
}
//С�������������� 
snorlax::~snorlax()
{}
//С�����޹������� ����Ϊ�Է���������attri�ͷ���ֵopp_def
int snorlax::attack(int attri, int opp_def)
{
    //�˺�
    int atk_n;

    //����һ�����ڵ������ ͨ������������Ƿ񱩻�
    int p = rand() % 100;

    //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
    if (calWinRate == no)
    {
        cout << "С������";
    }

    //����
    if (p <= crit)
    {
        //�����˺�Ϊ��ͨ�˺���150%
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);
        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }
    //��ͨ����
    else
    {
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)
        atk_n = atk * singlnumer / (atkdenomi + opp_def);
        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }

    //���������Χ���� �����ΧΪ-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //�����˺�
    return atk_n;
}

//�������ӹ��캯�� 
/*��������һ����
������bulbasaur_atk
Ѫ����bulbasaur_HP
�������ࣺ���幥�� ����ʱ����ָ�������20%
�������ԣ���*/
bulbasaur::bulbasaur() :tank()
{
    atk = bulbasaur_atk;
    HP = bulbasaur_HP;
    total_HP = HP;
    kind = BULBASAUR;
    atk_kind = SINGLE;
    atk_attribute = GRASS;
}

//�������� 
bulbasaur::~bulbasaur()
{}

//�������ӹ������� ����Ϊ�Է���������attri�ͷ���ֵopp_def
int bulbasaur::attack(int attri, int opp_def)
{
    //�˺�
    int atk_n;

    //����һ�����ڵ������ ͨ������������Ƿ񱩻�
    int p = rand() % 100;

    //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
    if (calWinRate == no)
    {
        cout << "��������";
    }

    //���� 
    if (p <= crit)
    {
        //�����˺�Ϊ��ͨ�˺���150%
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);
        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }
    //��ͨ����
    else
    {
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def));
        if (calWinRate == no)
            cout << "��������\n";
    }

    //������˼ӳ� 
    //�Է�����Ϊˮ �򹥻��ӳ�addition130%
    if (attri == WATER)
    {
        atk_n = int(addition*atk_n);
    }
    //�Է�����Ϊ�� ������Ϊԭ����10/13
    else if (attri == FIRE)
    {
        atk_n = int(atk_n / addition);
    }

    //���������Χ���� //���������Χ���� �����ΧΪ-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //��������Ѫ���ָ�������recovery
    HP += int(atk_n*recovery);
    int rec;
    rec = int(atk_n*recovery);
    //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
    if (calWinRate == no)
    {
        cout << "�������ӻָ�" << rec << "��Ѫ\n";
    }

    //��Ѫ�� �򲻼�Ѫ
    if (HP>total_HP)
    {
        HP = total_HP;
    }
    //�����˺�
    return atk_n;
}

//������С���� ���캯�� 
/*������С���飺����� ����
�������ʣ�30%
���ܼ��ʣ�5%*/
defence::defence()
{
    crit = ini_crit;
    dodge = defence_dodge;
}

//�������� 
defence::~defence()
{}

//�������� 
/*ÿ������exp=level*(level+upexp) ָ��������
������С���飺
�����ͱ�������ÿ��������Ϊlow rate
Ѫ��ÿ��������Ϊmid rate
����������ÿ��������Ϊhigh rate
�ٶȡ����ܲ�����*/
//����add_expΪ�����ľ���
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
        //С����������ʾ
        if (kind == SQUIRTLE)
        {
            cout << "��ϲ�����Ľ���������ˣ�\n";
        }
        else if (kind == SHUCKLE)
        {
            cout << "��ϲ�����ĺ��������ˣ�\n";
        }
        //С������������̬����
        if (level == maxLevel)
        {
            //��������Ϊˮ����
            if (kind == SQUIRTLE)
            {
                cout << "��ϲ�����Ľ����������������Ϊ������̬ˮ���꣡\n";
            }
            //����������
            else if (kind == SHUCKLE)
            {
                cout << "��ϲ�����ĺ�����������\n";
            }
        }
    }//end of while (exp >= level*(level + upexp) && level<maxLevel)

    if (level == maxLevel)
    {
        exp = ini_exp;
    }
}

//��С����������level�ȼ�����������һ������С���飩
//�������ʺ�promote������ͬ
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

//����� ���캯�� 
/*�����һ����
������squirtle_atk
Ѫ����squirtle_HP
������squirtle_def
�ٶȣ�squirtle_speed
�������ࣺ���幥��
�������ԣ�ˮ*/
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

//���������������
squirtle::~squirtle()
{}

//����깥������ ����Ϊ�Է��Ĺ�������attri�ͷ���ֵopp_def
int squirtle::attack(int attri, int opp_def)
{
    //�˺�
    int atk_n;
    //����һ�����ڵ������ ͨ������������Ƿ񱩻�
    int p = rand() % 100;

    //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
    if (calWinRate == no)
    {
        cout << "�����";
    }

    //���� 
    if (p <= crit)
    {
        //�����˺�Ϊ��ͨ�˺���150%
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);

        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }
    //��ͨ����
    else
    {
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)
        atk_n = atk * singlnumer / (atkdenomi + opp_def);
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }

    //������˼ӳ� 
    //�Է�����Ϊ�� �򹥻��ӳ�addition130%
    if (attri == FIRE)
    {
        atk_n = int(addition*atk_n);
    }
    //�Է�����Ϊ�ݻ�� ������Ϊԭ����10/13
    else if (attri == GRASS || attri == ELECTRIC)
    {
        atk_n = int(atk_n / addition);
    }

    //���������Χ����  �����ΧΪ-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //�����˺�����ֵ
    return atk_n;
}

//���� ���캯�� 
/*����һ����
������shuckle_atk
Ѫ����shuckle_HP
������shuckle_def
�ٶȣ�shuckle_speed
�������ࣺ���幥��
�������ԣ���*/
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

//������������ 
shuckle::~shuckle()
{}

//�������� ����Ϊ�Է��Ĺ�������attri�ͷ���ֵopp_def
int shuckle::attack(int attri, int opp_def)
{
    //�˺�
    int atk_n;

    //����һ�����ڵ������ ͨ������������Ƿ񱩻�
    int p = rand() % 100;

    //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
    if (!calWinRate)
    {
        cout << "����";
    }

    //����
    if (p <= crit)
    {
        //�����˺�Ϊ��ͨ�˺���150%
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);

        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }
    //��ͨ����
    else
    {
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)
        atk_n = atk * singlnumer / (atkdenomi + opp_def);

        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }
    //������˼ӳ� 
    //�Է�����Ϊ�� �򹥻��ӳ�addition130%
    if (attri == GRASS)
    {
        atk_n = int(addition*atk_n);
    }
    //�Է�����Ϊ�𡢷��л�� ������Ϊԭ����10/13
    else if (attri == FIRE || attri == FLY || attri == FIGHT)
    {
        atk_n = int(atk_n / addition);
    }

    //���������Χ����  �����ΧΪ-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //�����˺�
    return atk_n;
}

//�ٶ��� 
/*�ٶ���С���飺Ƥ�� ������
������quick_atk
������quick_HP
������quick_def
�������ʣ�30%
���ܼ��ʣ�10%*/
quick::quick() :pokemon()
{
    atk = quick_atk;
    HP = quick_HP;
    total_HP = HP;
    def = quick_def;
    crit = ini_crit;
    dodge = ini_dodge;
}

//����
quick::~quick()
{}

//�ٶ������������� 
/*ÿ������exp=level*(level+upexp) ָ��������
�ٶ���С���飺
���ܺͱ�������ÿ��������Ϊhigh rate
Ѫ��������ÿ��������Ϊlow rate
����ÿ��������Ϊmiddle rate
�ٶȲ�����*/
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

        //С����������ʾ
        if (kind == PIKACHU)
        {
            cout << "��ϲ������Ƥ�������ˣ�\n";
        }
        else if (kind == CROBAT)
        {
            cout << "��ϲ�����ĳ����������ˣ�\n";
        }
        //С������������̬����
        if (level == maxLevel)
        {
            //Ƥ�����Ϊ����
            if (kind == PIKACHU)
            {
                cout << "��ϲ������Ƥ��������������Ϊ������̬����\n";
            }
            //���������Ϊ������
            else if (kind == CROBAT)
            {
                cout << "��ϲ�����ĳ�����������������Ϊ������̬������\n";
            }
        }
    }//end of while (exp >= level*(level + upexp) && level<maxLevel)

    if (level == maxLevel)
    {
        exp = ini_exp;
    }
}

//��С����������level�ȼ�����������һ������С���飩
//�������ʺ�promote������ͬ
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

//Ƥ���캯�� 
/*Ƥ��һ����
�ٶȣ�7
�������ࣺ���幥��
�������ԣ���*/
pikachu::pikachu() :quick()
{
    speed = pikachu_speed;
    kind = PIKACHU;
    atk_kind = SINGLE;
    atk_attribute = ELECTRIC;
}
//����
pikachu::~pikachu()
{}
//Ƥ�𹥻�����  ����Ϊ�Է��Ĺ�������attri�ͷ���ֵopp_def
int pikachu::attack(int attri, int opp_def)
{
    //�˺�
    int atk_n;

    //����һ�����ڵ������ ͨ������������Ƿ񱩻�
    int p = rand() % 100;

    //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
    if (calWinRate == no)
    {
        cout << "Ƥ��";
    }

    //����
    if (p <= crit)
    {
        //�����˺�Ϊ��ͨ�˺���150%
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);

        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }
    //��ͨ����
    else
    {
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)
        atk_n = atk * singlnumer / (atkdenomi + opp_def);

        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }
    //������˼ӳ� 
    //�Է�����Ϊˮ �򹥻��ӳ�addition130%
    if (attri == WATER)
    {
        atk_n = int(addition*atk_n);
    }

    //���������Χ���� �����ΧΪ-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //�����˺�
    return atk_n;
}

//�������캯�� 
/*������һ����
�ٶȣ�8
�������ࣺ���幥��
�������ԣ�������*/
crobat::crobat() :quick()
{
    speed = crobat_speed;
    kind = CROBAT;
    atk_kind = SINGLE;
    atk_attribute = FLY;
}

//����
crobat::~crobat()
{}

//�����𹥻����� ����Ϊ�Է��Ĺ�������attri�ͷ���ֵopp_def
int crobat::attack(int attri, int opp_def)
{
    //�˺�
    int atk_n;

    //����һ�����ڵ������ ͨ������������Ƿ񱩻�
    int p = rand() % 100;

    //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
    if (calWinRate == no)
    {
        cout << "������";
    }

    //����
    if (p <= crit)
    {
        //�����˺�Ϊ��ͨ�˺���150%
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)*150%
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);

        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }
    //��ͨ����
    else
    {
        //atk_n=��幥��atk*singlnumer/(atkdenomi+�Է�����opp_def)
        atk_n = atk * singlnumer / (atkdenomi + opp_def);

        //����ǰΪ����ʤ���򲻴�ӡս��ϸ��
        if (calWinRate == no)
        {
            cout << "��������\n";
        }
    }
    //������˼ӳ� 
    //�Է�����Ϊ�桢�񶷻�� �򹥻��ӳ�addition130%
    if (attri == BUG || attri == FIGHT || attri == GRASS)
    {
        atk_n = int(addition*atk_n);
    }

    //���������Χ����  �����ΧΪ-atkrange~atkrange
    p = rand() % atkmod - atkrange;
    atk_n += p;

    //�����˺�
    return atk_n;
}
