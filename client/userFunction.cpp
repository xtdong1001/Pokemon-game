#include"pokemon.h"

//ȫ�ֱ�������
char sendBuf[BUF_SIZE] = { '\0' };  //���ͻ����� ��󳤶�ΪBUF_SIZE
char recvBuf[BUF_SIZE] = { '\0' };  //���ջ����� ��󳤶�ΪBUF_SIZE
int sendRequest = WAIT; //socket������(��ʼʱ�ر�)
int receiveInfo = WAIT; //socket������Ϣ������(��ʼʱ�ر�)
int stop = no;			//���������־
int calWinRate = no;     //����ʤ��

                        //�û��๹�캯��
user::user()
{
    //��ʼ���û��������� ����ΪmaxLength
    for (int i = 0; i < maxLength; i++)
    {
        userName[i] = '\0';
        password[i] = '\0';
    }

    //��ʼ��С����ָ��
    for (int i = 0; i < 30; i++)
    {
        poke[i] = NULL;
    }
    //С������������Ϊ0
    pokemonNum = no;

    winNum = no; //Ӯ�ñ�������Ϊ0
    playNum = no;//�μ���Ϸ����Ϊ0

                //ѫ����������Ϊ0
    for (int i = 0; i < 3; i++)
    {
        NumMedal[i] = no;
        LevelMedal[i] = no;
    }
}

//��������
user::~user()
{

}

//�û�ע��
void user::signUp()
{
    char name[msgLength] = { '\0' };  //�û��������뻺����
    char pword[msgLength] = { '\0' }; //�û��������뻺����
    int ok = no;  //�û�����������ȷ��־

                 //���벻��ȷ��һֱѭ��
    while (!ok)
    {
        //��ʾ��Ϣ
        std::cout << "�û�����(1-14λ��ĸ�����֣��»���):\n";
        while (!ok)
        {
            std::cin >> name;
            //�û��������ж�
            ok = isCorrectName(name);
        }
        //�����������
        sendMessage(SIGNUP_NAME, name);

        //�ȴ�������Ӧ��
        while (receiveInfo == WAIT);

        //�û�ע��ʧ�� �û����ظ�
        if (recvBuf[0] == FAILURE)
        {
            std::cout << "���û���̫�ܻ�ӭ,�����һ��!" << std::endl;
            ok = no;

            //��շ��ͽ��ջ�����
            clearBuf();
        }
        //��ס�û��˷���������Ϣ����
        receiveInfo = WAIT;
    }//ok

     //��շ��ͽ��ջ�����
    clearBuf();

    ok = no;
    //�û���������
    std::cout << "���룺(6-14λ��ĸ�����֣�������):\n";
    while (!ok)
    {
        std::cin >> pword;
        //���������ж�
        ok = isCorrectPword(pword);
    }
    //�����������
    sendMessage(SIGNUP_PASSWORD, pword);

    //�ȴ�������Ӧ��
    while (receiveInfo == WAIT);

    //ע����Զ���¼ �״ε�½�������С����
    std::cout << "ע��ɹ���\n�״ε�¼�����:\n";
    for (int i = 0; i < 3; i++)
    {
        switch (recvBuf[i])
        {
        case BULBASAUR:  poke[i] = new bulbasaur;  std::cout << "�������� "; break;
        case CHARMANDER: poke[i] = new charmander; std::cout << "С���� ";   break;
        case SQUIRTLE:   poke[i] = new squirtle;   std::cout << "����� ";   break;
        case PIKACHU:    poke[i] = new pikachu;    std::cout << "Ƥ�� ";     break;
        case MANKEY:     poke[i] = new mankey;     std::cout << "��� ";     break;
        case SNORLAX:    poke[i] = new snorlax;    std::cout << "С������ "; break;
        case CROBAT:	 poke[i] = new crobat;     std::cout << "������ ";   break;
        case SHUCKLE:	 poke[i] = new shuckle;    std::cout << "���� ";     break;

        default:break;
        }
    }
    std::cout << '\n';

    //ע��ɹ�������û�����Ϣ ���û����������뱣�����û�����
    for (int i = 0; i < maxLength; i++)
    {
        userName[i] = name[i];
        password[i] = pword[i];
    }
    //С�������
    pokemonNum = 3;

    //��շ��ͽ��ջ����� ����
    clearBuf();
    receiveInfo = WAIT;
}

//�û���¼
void user::logIn()
{
    char name[msgLength] = { '\0' };  //�û��������뻺����
    char pword[msgLength] = { '\0' }; //�û��������뻺����

    int ok = no; //�û�����������ȷ��־

                //��ʾ�û������û���
    std::cout << "�û�����\n";
    while (!ok)
    {
        std::cin >> name;
        //�û��������ж�
        ok = isCorrectName(name);
    }
    //�����������
    sendMessage(LOGIN_NAME, name);
    //�ȴ�������Ӧ��
    while (receiveInfo == WAIT);

    //��շ��ͽ��ջ����� ����
    receiveInfo = WAIT;
    clearBuf();

    //��ʾ�û���������
    ok = no;
    std::cout << "���룺\n";
    while (!ok)
    {
        std::cin >> pword;
        //���������ж�
        ok = isCorrectPword(pword);
    }
    //�������������Ϣ
    sendMessage(LOGIN_PASSWORD, pword);

    //�ȴ�������Ӧ��
    while (receiveInfo == WAIT);

    //��¼ʧ��
    if (FAILURE == recvBuf[0])
    {
        //�û���������
        if (INEXISTENCE == recvBuf[1])
        {
            std::cout << "�û���������" << std::endl;
        }
        //�������
        if (PASSWORDERROR == recvBuf[1])
        {
            std::cout << "�������" << std::endl;
        }
        //��ǰΪ��¼״̬
        else if (ONLINE == recvBuf[1])
        {
            std::cout << "���Ѿ���¼" << std::endl;
        }
    }
    //��¼�ɹ�
    else
    {
        std::cout << "��¼�ɹ���\n";
        //��¼�ɹ�������û�����Ϣ ���û����������뱣�����û�����
        for (int i = 0; i < maxLength; i++)
        {
            userName[i] = name[i];
            password[i] = pword[i];
        }

        //�ӷ���������С��������
        std::cout << "�����û�������,���Ժ򡭡�\n";

        //��շ��ͽ��ջ����� ����
        receiveInfo = WAIT;
        clearBuf();

        /*****�û�����ʤ��ͬ��*****/
        //���Ͳ�������
        sendMessage(WINRATE_REQ, name);

        //�ȴ���������Ӧ
        while (receiveInfo == WAIT);

        char winRateInfo[msgLength] = { '\0' };

        int winN = no, sumN = no, useless = no;
        //��recvBuf����ȡ��Ϣ����winRateInfo��
        strncpy(winRateInfo, recvBuf + 1, msgLength);

        //�����Ϣ winNΪ�û�ʤ������ sumNΪ�����ܴ���
        readInfo(winRateInfo, winN, sumN, useless);

        //���浽����
        winNum = winN;
        playNum = sumN;

        //��շ��ͽ��ջ����� ����
        receiveInfo = WAIT;
        clearBuf();

        /*****�û�����С����ͬ��*****/
        //�û�������Ϣ
        char in[msgLength] = { '\0' };
        in[0] = yes;

        int pokeNum = no; //С��������
        char elfInfo[msgLength] = { '\0' }; //С������Ϣ

                                            //�������С��������
        sendMessage(UPDATE_REQ, in);

        //�ȴ�������Ӧ��
        while (receiveInfo == WAIT);

        //��Ӧ����������Ϣ
        in[0] = no;

        //��ȡС�������Ϣ ����������������ѭ��
        while (recvBuf[0])
        {
            int eKind, eExp, eLevel;
            //��recvBuf����ȡ��Ϣ����elfInfo��
            strncpy(elfInfo, recvBuf + 1, msgLength);
            //�����Ϣ eKindΪС�������� eLevelΪС����ȼ� eExpΪС���龭��ֵ
            readInfo(elfInfo, eKind, eLevel, eExp);

            //����һ������ΪeKind��1��С����
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
            //����С������Ϣ
            poke[pokeNum]->exp = eExp;
            poke[pokeNum]->level = eLevel;
            //С�������Ϊelevel��С����
            poke[pokeNum]->promoteLevel();
            //С����������һ
            pokeNum++;

            //��շ��ͽ��ջ����� ����
            receiveInfo = WAIT;
            clearBuf();

            //������������
            sendMessage(UPDATE_REQ, in);

            //�ȴ��ظ�
            while (receiveInfo == WAIT);
        }
        //����С��������
        pokemonNum = pokeNum;
    }//��½�ɹ�

     //��շ��ͽ��ջ����� ����
    receiveInfo = WAIT;
    clearBuf();
}

//�û��ǳ�
void user::logOut()
{
    char name[msgLength] = { '\0' }; //�û��������뻺����

                                     //���û����ȡ�û�����
    for (int i = 0; i < maxLength; i++)
    {
        name[i] = userName[i];
    }

    //�����û��ǳ�������û���
    sendMessage(LOGOUT_REQ, name);

    //�ȴ�������Ӧ��
    while (receiveInfo == WAIT);

    //�ǳ�ʧ��
    if (!recvBuf[0])
    {
        //δ��¼
        if (recvBuf[1])
        {
            std::cout << "�û���ǰδ��¼��\n" << std::endl;
        }
        //�������û�
        else
        {
            std::cout << "�û�δע�ᣡ\n" << std::endl;
        }
    }
    //�ǳ��ɹ�
    else
    {
        //��շ��ͽ��ջ����� ����
        receiveInfo = WAIT;
        clearBuf();

        //����ͬ����Ϣ��������
        synchron();

        std::cout << "�ǳ��ɹ���" << std::endl;
    }
    //��շ��ͽ��ջ����� ����
    receiveInfo = WAIT;
    clearBuf();

    for (int i = 0; i < pokemonNum; i++)
    {
        poke[i] = NULL;
    }
    pokemonNum = 0;

    //ѫ����������Ϊ0
    for (int i = 0; i < 3; i++)
    {
        NumMedal[i] = no;
        LevelMedal[i] = no;
    }
}

//��ѯ�����û�
void user::searchOnlineUser()
{
    //������Ϣ ����1��ʾ�����ѯ ����0��ʾ�ظ��յ��������������
    char in[msgLength] = { '\0' };
    in[0] = yes;

    //�����û�����
    int userNum = no;
    //�����û��û���
    char onlineUser[maxLength] = { '\0' };

    //��������
    sendMessage(SEARCHUSER_REQ, in);

    //�ȴ�������Ӧ��
    while (receiveInfo == WAIT);
    in[0] = no;

    std::cout << "�����û�:\n";
    //�����ѯ���
    while (recvBuf[0])
    {
        //��recvBuf����ȡ�û�����Ϣ������onlineUser��
        strncpy(onlineUser, recvBuf + 1, maxLength);
        std::cout << onlineUser << std::endl;
        //�����û�������һ
        userNum++;

        //��շ��ͽ��ջ����� ����
        receiveInfo = WAIT;
        clearBuf();

        //�ظ���ʾ�յ��������������
        sendMessage(SEARCHUSER_REQ, in);

        //�ȴ���������Ӧ
        while (receiveInfo == WAIT);
    }
    //��շ��ͽ��ջ����� ����
    receiveInfo = WAIT;

    //��ӡ���
    std::cout << "\n��ǰ�����û�����" << userNum << "��\n";
    clearBuf();
}

//��ѯע���û��ľ���
void user::searchPokemon()
{
    char userNameBuf[msgLength] = { '\0' };

    std::cout << "Ҫ���ҵ��û�����\n" << std::endl;
    std::cin >> userNameBuf;

    //���Ͳ�������
    sendMessage(SEARCHPOKEMON_REQ, userNameBuf);

    //�ȴ���������Ӧ
    while (receiveInfo == WAIT);

    //����ʧ��
    if (recvBuf[0] == FAILURE)
    {
        std::cout << "Ҫ���ҵ��û������ڣ�\n";
        clearBuf();
    }
    //���ҳɹ�
    else
    {
        //������
        std::cout << "Ҫ���ҵ��û�ӵ�У�\n";
        for (int i = 1; recvBuf[i] != '\0'; i++)
        {
            switch (recvBuf[i])
            {
            case BULBASAUR:  std::cout << "�������� "; break;
            case CHARMANDER: std::cout << "С���� "; break;
            case SQUIRTLE:	 std::cout << "����� "; break;
            case PIKACHU:	 std::cout << "Ƥ�� "; break;
            case MANKEY:	 std::cout << "��� "; break;
            case SNORLAX:	 std::cout << "С������ "; break;
            case CROBAT:	 std::cout << "������ "; break;
            case SHUCKLE:	 std::cout << "���� "; break;
            default:break;
            }
        }
        std::cout << '\n';
    }
    //��շ��ͽ��ջ����� ����
    receiveInfo = WAIT;
    clearBuf();
}

//��ѯĳ�û���ʤ��
void user::searchWinRate()
{
    char userNameBuf[msgLength] = { '\0' };

    std::cout << "Ҫ���ҵ��û�����\n" << std::endl;
    std::cin >> userNameBuf;

    //���Ͳ�������
    sendMessage(WINRATE_REQ, userNameBuf);

    //�ȴ���������Ӧ
    while (receiveInfo == WAIT);

    //����ʧ��
    if (recvBuf[0] == FAILURE)
    {
        std::cout << "Ҫ���ҵ��û������ڣ�\n";
        clearBuf();
    }
    //���ҳɹ�
    else
    {
        char winRateInfo[msgLength] = { '\0' };
        //������
        std::cout << "���û���ʤ��Ϊ��";

        int winN, sumN, useless;
        //��recvBuf����ȡ��Ϣ����winRateInfo��
        strncpy(winRateInfo, recvBuf + 1, msgLength);
        //�����Ϣ eKindΪС�������� eLevelΪС����ȼ� eExpΪС���龭��ֵ
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
    //��շ��ͽ��ջ����� ����
    receiveInfo = WAIT;
    clearBuf();
}

//С����ս�� ����competitorA competitorB�ֱ�Ϊ�û�С����ͶԷ�С����
int user::fighting(pokemon* competitorA, pokemon* competitorB)
{
    int win = no;   //�û�С�����ʤ����
    int time = no;  //ս����ʱ
    int death = no; //С����������־
                   //˫��С������ٶȣ��������ԣ�����ֵ
    int sp1 = 0, sp2 = 0, attr1 = 0, attr2 = 0, def1 = 0, def2 = 0;

    //���С������ٶȣ��������Ժͷ���ֵ
    sp1 = competitorA->getSpeed();
    sp2 = competitorB->getSpeed();
    attr1 = competitorA->getAttr();
    attr2 = competitorB->getAttr();
    def1 = competitorA->getDef();
    def2 = competitorB->getDef();

    //˫����С��������
    while (!death)
    {
        //��ʱ��
        time++;
        //�ֵ�С����A����
        if (time%sp1 == 0)
        {
            death = competitorB->damage(competitorA->attack(attr2, def2));
            //С����B���� С����Aʤ�� �˴�ģ��ս������
            if (death == yes)
            {
                win = yes;
                break;
            }
        }
        //�ֵ�С����B����
        if (time%sp2 == 0)
        {
            death = competitorA->damage(competitorB->attack(attr1, def1));
        }
    }
    //���㾭��
    competitorA->promote(competitorA->cal_exp(competitorB->level));
    competitorB->promote(competitorB->cal_exp(competitorA->level));
    //��ӡС������Ϣ
    competitorA->print();
    competitorB->print();
    //��������
    time = 0;
    //����ս�����
    return win;
}

//������
void user::upgrade()
{
    //����С����
    int upgradePoke;

    //�û���С����
    if (pokemonNum > 0)
    {
        std::cout << "�����ӵ�е�С������ѡ��һ������������\n";
        //��ӡС������Ϣ���û�ѡ��
        for (int i = 0; i < pokemonNum; i++)
        {
            std::cout << i << ":\n";
            poke[i]->print();
        }

        std::cin >> upgradePoke;
    }
    //�û�û��С����
    else
    {
        //1-8֮�������
        std::cout << "���Ѿ���������е�С���飬ϵͳ�������������һ��\n";
        int p = rand() % 8 + 1;

        //ϵͳ�������һ��1��С����
        switch (p)
        {
        case BULBASAUR:  poke[0] = new bulbasaur;  std::cout << "�������� "; break;
        case CHARMANDER: poke[0] = new charmander; std::cout << "С���� ";   break;
        case SQUIRTLE:   poke[0] = new squirtle;   std::cout << "����� ";   break;
        case PIKACHU:    poke[0] = new pikachu;    std::cout << "Ƥ�� ";    break;
        case MANKEY:     poke[0] = new mankey;     std::cout << "��� ";     break;
        case SNORLAX:    poke[0] = new snorlax;    std::cout << "С������ ";   break;
        case CROBAT:	 poke[0] = new crobat;     std::cout << "������ "; break;
        case SHUCKLE:	 poke[0] = new shuckle;    std::cout << "���� "; break;
        default:break;
        }
        //�û�С����Ϊ��0��С����
        upgradePoke = 0;
        std::cout << "\n";
        //��ӡС������Ϣ
        poke[0]->print();
    }

    //ѡ�����
    std::cout << "���С�����б�����ѡ��һ������������\n";
    std::cout << "�����ͣ� 1-���     2-С����\n";
    std::cout << "����ͣ� 3-С������  4-��������\n";
    std::cout << "�����ͣ� 5-�����   6-����\n";
    std::cout << "�ٶ��ͣ� 7-Ƥ��     8-������\n";

    int comp = 0; //����С��������
    std::cin >> comp;

    //��������С����
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

    int opp_level; //����С����ȼ�
    std::cout << "������С����ȼ���1-15��\n";
    std::cin >> opp_level;

    //���¶Է�С������Ϣ
    competitor->level = opp_level;
    competitor->promoteLevel();
    //��ӡ����С������Ϣ
    competitor->print();

    //���㱾������ʤ��
    int k = poke[upgradePoke]->kind;
    int l = poke[upgradePoke]->level;
    CalWinRate(competitor, k, l);

    //ս��������־
    int end = no;

    //�û���Ҫ��ս��������һֱѭ��
    while (!end)
    {
        playNum++;

        //С����ս��
        int w = fighting(poke[upgradePoke], competitor);

        if (w == yes)
        {
            winNum++;
        }

        std::cout << "�Ƿ������1-������0-����\n";
        std::cin >> end;

        //˫��С�������ƻ�Ѫ
        poke[upgradePoke]->recover();
        competitor->recover();
    }
    //�ͷ�С������Դ
    delete competitor;
}

//������
void user::duel()
{
    //����С����
    int upgradePoke;
    //�û���С����
    if (pokemonNum > 0)
    {
        //��ӡС������Ϣ���û�ѡ��
        std::cout << "�����ӵ�е�С������ѡ��һ�����о�����\n";
        for (int i = 0; i < pokemonNum; i++)
        {
            std::cout << i << ":\n";
            poke[i]->print();
        }
        std::cin >> upgradePoke;
    }
    //�û�û��С����
    else
    {
        //1-8֮�������
        std::cout << "���Ѿ���������е�С���飬ϵͳ�������һ��\n";
        int p = rand() % 8 + 1;
        //ϵͳ�������һ��1��С����
        switch (p)
        {
        case BULBASAUR:  poke[0] = new bulbasaur;  std::cout << "�������� "; break;
        case CHARMANDER: poke[0] = new charmander; std::cout << "С���� ";   break;
        case SQUIRTLE:   poke[0] = new squirtle;   std::cout << "����� ";   break;
        case PIKACHU:    poke[0] = new pikachu;    std::cout << "Ƥ�� ";   break;
        case MANKEY:     poke[0] = new mankey;     std::cout << "��� ";     break;
        case SNORLAX:    poke[0] = new snorlax;    std::cout << "С������ ";   break;
        case CROBAT:	 poke[0] = new crobat;     std::cout << "������ "; break;
        case SHUCKLE:	 poke[0] = new shuckle;    std::cout << "���� "; break;
        default:break;
        }
        std::cout << "\n";
        //�û�С����Ϊ��0��С����
        upgradePoke = 0;
        //��ӡС������Ϣ
        poke[0]->print();
    }
    //ѡ�����
    std::cout << "���С�����б�����ѡ��һ�����о�����\n";
    std::cout << "�����ͣ� 1-���     2-С����\n";
    std::cout << "����ͣ� 3-С������ 4-��������\n";
    std::cout << "�����ͣ� 5-�����   6-����\n";
    std::cout << "�ٶ��ͣ� 7-Ƥ��    8-������\n";

    //����С��������
    int comp = 0;
    std::cin >> comp;

    //����С����
    pokemon *competitor = NULL;

    //��ǰ�����û����ܻ�õ�С������Դ
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
    //����С����ȼ�
    int opp_level;
    std::cout << "������С����ȼ���1-15��\n";
    std::cin >> opp_level;

    //���¶Է�С������Ϣ��ӡ
    competitor->level = opp_level;
    competitor->promoteLevel();
    competitor->print();

    //����ʤ��
    int k = poke[upgradePoke]->kind;
    int l = poke[upgradePoke]->level;
    CalWinRate(competitor, k, l);

    //С����ս��
    int win = fighting(poke[upgradePoke], competitor);

    //�û�ʤ�� ��öԷ�С����
    if (win == SUCCESS && pokemonNum < 30)
    {
        playNum++;
        winNum++;

        //С�������ƻ�Ѫ
        poke[upgradePoke]->recover();

        std::cout << "ս��ʤ����Ӯ��һ��С����\n";
        //��ӡ��õ�С������Ϣ
        competitor->print();

        //�û����һ��С����
        poke[pokemonNum]->level = competitor->level;
        poke[pokemonNum]->exp = competitor->exp;
        poke[pokemonNum]->promoteLevel();

        //С����������һ
        pokemonNum++;
        std::cout << "��ϲ����������" << pokemonNum << "��С����\n";
    }

    //�û�ʧ�� �ͳ�һ��С����
    else if (win == FAILURE)
    {
        playNum++;

        //�ͷ���ǰ����Ľ�Ҫ��õ�С������Դ
        delete poke[pokemonNum];

        int give;//�ͳ���С����

                 //�û���������С������С����
        if (pokemonNum <= 3)
        {
            std::cout << "�������С������ѡ��һ���ͳ���\n";
            //��ӡҪ�ͳ���С������Ϣ
            for (int i = 0; i < pokemonNum; i++)
            {
                std::cout << i << ":\n";
                poke[i]->print();
            }
            std::cin >> give;
        }
        //��������С����
        else
        {
            //���ѡ��3��С����
            std::cout << "������С���������ѡ����������ѡ��һ���ͳ���\n";
            int p[3] = { 0,0,0 };  //���ѡ������С����
            p[0] = rand() % pokemonNum;
            p[1] = rand() % pokemonNum;

            //����С���鲻����ͬһ��
            while (p[1] == p[0])
            {
                p[1] = rand() % pokemonNum;
            }
            p[2] = rand() % pokemonNum;
            //����С���鲻������ͬ��
            while (p[2] == p[0] || p[2] == p[1])
            {
                p[2] = rand() % pokemonNum;
            }
            //��ӡ����С�������Ϣ���û�ѡ��
            for (int i = 0; i < 3; i++)
            {
                std::cout << p[i] << ":\n";
                poke[p[i]]->print();
            }

            //�û�ѡ��
            std::cin >> give;
        }
        //�ͳ����С����
        delete poke[give];

        //С�������ȱ
        for (int i = give; i < pokemonNum; i++)
        {
            poke[i] = poke[i + 1];
        }

        //С����������һ
        pokemonNum--;
        std::cout << "��ʧȥ��һ��С���飬���ڻ�ʣ" << pokemonNum << "��С����\n";
    }
    else
    {
        std::cout << "�û�С���������ﵽ����\n";
    }
    //�ͷŶ���С������Դ
    delete competitor;
}

//2v2�ֶ�С����������
void user::upgrade2v2()
{
    //����С��������
    int uPoke[2];
    //�û��г�������С���飬�����û�ѡ������С�������
    if (pokemonNum > 2)
    {
        //��ӡС������Ϣ���û�ѡ��
        for (int i = 0; i < pokemonNum; i++)
        {
            std::cout << i << ":\n";
            poke[i]->print();
        }
        std::cout << "�����ӵ�е�С������ѡ���������о�����\n";
        std::cin >> uPoke[0];
        std::cin >> uPoke[1];
    }
    //�û�������С���飬��������С����μӱ���
    else if (pokemonNum == 2)
    {
        //��ӡС������Ϣ
        std::cout << "���ĳ�սС����Ϊ��\n";
        for (int i = 0; i <= 1; i++)
        {
            poke[i]->print();
        }
    }
    //�û�ֻ��һ��С���飬���С�������������ϵͳ�������һ��С����
    else if (pokemonNum == 1)
    {
        //��ӡ�û��е�С����
        std::cout << "���ĳ�սС����Ϊ��\n";
        poke[0]->print();

        //ϵͳ�������
        std::cout << "ϵͳ�������һ��1��С���飺\n";
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
        //�û�С����
        uPoke[0] = 0;
        uPoke[1] = 1;

        //��ӡС������Ϣ
        poke[1]->print();
    }
    //�û�û��С���� ϵͳ�����������С����
    else
    {
        std::cout << "���Ѿ���������е�С���飬ϵͳ�����������\n";

        for (int i = 0; i <= 1; i++)
        {
            int p = rand() % 8 + 1;
            //ϵͳ�������һ��1��С����
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
    //ѡ�����
    std::cout << "���С�����б�����ѡ��2�����о�����\n";
    std::cout << "�����ͣ� 1-���     2-С����\n";
    std::cout << "����ͣ� 3-С������ 4-��������\n";
    std::cout << "�����ͣ� 5-�����   6-����\n";
    std::cout << "�ٶ��ͣ� 7-Ƥ��    8-������\n";

    //����С��������
    int comp[2];
    std::cin >> comp[0];
    std::cin >> comp[1];

    //����С����
    pokemon *competitor[2];
    for (int i = 0; i <= 1; i++)
    {
        switch (comp[i])
        {
        case BULBASAUR:  competitor[i] = new bulbasaur;  std::cout << "�������� "; break;
        case CHARMANDER: competitor[i] = new charmander; std::cout << "С���� ";   break;
        case SQUIRTLE:   competitor[i] = new squirtle;   std::cout << "����� ";   break;
        case PIKACHU:    competitor[i] = new pikachu;    std::cout << "Ƥ�� ";   break;
        case MANKEY:     competitor[i] = new mankey;     std::cout << "��� ";     break;
        case SNORLAX:    competitor[i] = new snorlax;    std::cout << "С������ ";   break;
        case CROBAT:	 competitor[i] = new crobat;     std::cout << "������ "; break;
        case SHUCKLE:	 competitor[i] = new shuckle;    std::cout << "���� "; break;
        default:break;
        }

        int opp_level;
        std::cout << "\n�������һ��С����ĵȼ���1-15��\n";
        std::cin >> opp_level;

        //����С������Ϣ��ӡ
        //�ֶ������Ӵ��Ѷ� С����ȼ���һ
        competitor[i]->level = opp_level + 1;
        competitor[i]->promoteLevel();
        competitor[i]->print();
    }

    int win = 0; //win=2��ʾ�û�Ӯ
    int lose = 0;//lose=2��ʾ�û���
    int time = 0;//��ʱ
    int death[4] = { 0,0,0,0 };//������־
    int sp[4], attr[4], def[4];//С��������

                               //����ĸ�С������ٶȣ��������Ժͷ���ֵ
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

    //˫����С��������
    while (win != 2 && lose != 2)
    {
        //��ʱ��
        time++;

        //�ֵ�����һ��С�������
        if (time%sp[2] == 0 && death[2] == no)
        {
            int at = -1;//����Ŀ�꣨1��2��

                        //�Է�һ��С�������� ����Ҫѡ�� ֱ�ӹ����Է�����С����
            if (death[0] == yes)
            {
                at = 2;
            }
            //�Է�����С�������� ����Ҫѡ�� ֱ�ӹ����Է�һ��С����
            else if (death[1] == yes)
            {
                at = 1;
            }
            //��ǰС���鲻��Ⱥ�幥������ �ҶԷ�����С���鶼û������ 
            //�����û�ѡ�񹥻��ĸ�С����
            else if (poke[uPoke[0]]->atk_kind != 2)
            {
                std::cout << "��ѡ��һ��С����Ҫ������С����(1��2��:\n";
                std::cin >> at;
            }
            //��ǰС����ΪȺ��С�����ҶԷ�û��С��������
            if (at == -1)
            {
                death[0] = competitor[0]->damage(poke[uPoke[0]]->attack(attr[0], def[0]));
                death[1] = competitor[1]->damage(poke[uPoke[0]]->attack(attr[1], def[1]));
                //�Է�һ��С��������
                if (death[0] == yes)
                {
                    win++;
                }
                //����С��������
                if (death[1] == yes)
                {
                    win++;
                }
            }
            //�Է���һ��С��������
            else
            {
                death[at - 1] = competitor[at - 1]->damage(poke[uPoke[0]]->attack(attr[at - 1], def[at - 1]));
                if (death[at - 1] == yes)
                {
                    win++;
                }
            }
            //�Է�����С���鶼������ս������
            if (win == 2)
            {
                break;
            }
        }

        //�ֵ���������С�������
        if (time%sp[3] == 0 && death[3] == no)
        {
            int at = -1;//����Ŀ�꣨1��2��

                        //�Է�һ��С�������� ����Ҫѡ�� ֱ�ӹ����Է�����С����
            if (death[0] == yes)
            {
                at = 2;
            }
            //�Է�����С�������� ����Ҫѡ�� ֱ�ӹ����Է�һ��С����
            else if (death[1] == yes)
            {
                at = 1;
            }
            //��ǰС���鲻��Ⱥ�幥������ �ҶԷ�����С���鶼û������ 
            //�����û�ѡ�񹥻��ĸ�С����
            else if (poke[uPoke[1]]->atk_kind != 2)
            {
                std::cout << "��ѡ�����С����Ҫ������С����(1��2��:\n";
                std::cin >> at;
            }
            //��ǰС����ΪȺ��С�����ҶԷ�û��С��������
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
            //�Է���һ��С��������
            else
            {
                death[at - 1] = competitor[at - 1]->damage(poke[uPoke[1]]->attack(attr[at - 1], def[at - 1]));
                if (death[at - 1] == yes)
                {
                    win++;
                }
            }
            //�Է�����С���鶼������ս������
            if (win == 2)
            {
                break;
            }
        }
        //�ֵ�����һ��С�������
        if (time%sp[0] == 0 && death[0] == 0)
        {
            int at = -1;
            //�Է�һ��С�������� ����Ҫѡ�� ֱ�ӹ����Է�����С����
            if (death[2] == yes)
            {
                at = 1;
            }
            //�Է�����С�������� ����Ҫѡ�� ֱ�ӹ����Է�һ��С����
            else if (death[3] == yes)
            {
                at = 0;
            }
            //��ǰС���鲻��Ⱥ�幥������ �ҶԷ�����С���鶼û������ 
            //�����ѡ�񹥻��ĸ�С����
            else if (competitor[0]->atk_kind != 2)
            {
                at = rand() % 2;
            }

            //��ǰС����ΪȺ��С�����ҶԷ�û��С��������
            if (at == -1)
            {
                death[2] = poke[uPoke[0]]->damage(competitor[0]->attack(attr[2], def[2]));
                death[3] = poke[uPoke[1]]->damage(competitor[0]->attack(attr[3], def[3]));
                //�Է�һ��С��������
                if (death[2] == yes)
                {
                    lose++;
                }
                //�Է�����С��������
                if (death[3] == yes)
                {
                    lose++;
                }
            }
            //�Է���һ��С��������
            else
            {
                death[at + 2] = poke[uPoke[at]]->damage(competitor[0]->attack(attr[at + 2], def[at + 2]));
                if (death[at + 2] == yes)
                {
                    lose++;
                }
            }
            //�Է�����С���鶼������ս������
            if (lose == 2)
            {
                break;
            }
        }
        //�ֵ���������С�������
        if (time%sp[1] == 0 && death[1] == yes)
        {
            int at = -1;
            //�Է�һ��С�������� ����Ҫѡ�� ֱ�ӹ����Է�����С����
            if (death[2] == yes)
            {
                at = 1;
            }
            //�Է�����С�������� ����Ҫѡ�� ֱ�ӹ����Է�һ��С����
            else if (death[3] == yes)
            {
                at = 0;
            }
            //��ǰС���鲻��Ⱥ�幥������ �ҶԷ�����С���鶼û������ 
            //�����ѡ�񹥻��ĸ�С����
            else if (competitor[1]->atk_kind != 2)
            {
                at = rand() % 2;
            }
            //��ǰС����ΪȺ��С�����ҶԷ�û��С��������
            if (at == -1)
            {
                death[2] = poke[uPoke[0]]->damage(competitor[1]->attack(attr[2], def[2]));
                death[3] = poke[uPoke[1]]->damage(competitor[1]->attack(attr[3], def[3]));
                //�Է�һ��С��������
                if (death[2] == yes)
                {
                    lose++;
                }
                //�Է�����С��������
                if (death[3] == yes)
                {
                    lose++;
                }
            }
            //�Է���һ��С��������
            else
            {
                death[at + 2] = poke[uPoke[at]]->damage(competitor[1]->attack(attr[at + 2], def[at + 2]));
                if (death[at + 2] == yes)
                {
                    lose++;
                }
            }
            //�Է�����С���鶼������ս������
            if (lose == 2)
            {
                break;
            }
        }//end if (time%sp[1] == 0)
    }//end while (win != 2 && lose != 2)

     //�û�ʤ��
    if (win == 2)
    {
        playNum++;
        winNum++;
        std::cout << "��ϲ������С��������ʤ��!\n\n";
    }
    //�û�ʧ��
    else
    {
        playNum++;
        std::cout << "̫�ź��ˣ�����С��������!\n\n";
    }

    //���㾭��
    poke[uPoke[0]]->
        promote(poke[uPoke[0]]->
            cal_exp((competitor[0]->level + competitor[1]->level) / 2));
    poke[uPoke[1]]->
        promote(poke[uPoke[1]]->
            cal_exp((competitor[0]->level + competitor[1]->level) / 2));

    //С�����Ѫ
    poke[uPoke[0]]->recover();
    poke[uPoke[1]]->recover();
    //��ӡС������Ϣ
    poke[uPoke[0]]->print();
    poke[uPoke[1]]->print();

    //�ͷ���Դ
    delete competitor[0];
    delete competitor[1];
}

//ͳ��ѫ������
void user::medal()
{
    //С�������ѫ��
    //С������������8������ø߼�����ѫ��
    if (pokemonNum >= 8)
    {
        NumMedal[0] = yes;
        std::cout << "����С������������8������ø߼�����ѫ��һö��\n";
    }
    //С������������6������ø߼�����ѫ��
    if (pokemonNum >= 6)
    {
        NumMedal[1] = yes;
        std::cout << "��������С������������6��������м�����ѫ��һö��\n";
    }
    //С������������4������ø߼�����ѫ��
    if (pokemonNum >= 4)
    {
        NumMedal[2] = yes;
        std::cout << "��������С������������4������õͼ�����ѫ��һö��\n";
    }

    //����С����ѫ��
    int fullLevelNum = no;
    for (int i = 0; i < pokemonNum; i++)
    {
        if (poke[i]->level == maxLevel)
        {
            fullLevelNum++;
        }
    }
    //����С������������5������ø߼�����ѫ��
    if (fullLevelNum >= 5)
    {
        LevelMedal[0] = yes;
        std::cout << "��������С������������5������ø߼�����ѫ��һö��\n";
    }
    //����С������������3��������м�����ѫ��
    if (fullLevelNum >= 3)
    {
        LevelMedal[1] = 1;
        std::cout << "��������С������������3��������м�����ѫ��һö��\n";
    }
    //����С������������1������õͼ�����ѫ��
    if (fullLevelNum >= 1)
    {
        LevelMedal[2] = yes;
        std::cout << "��������С������������1������õͼ�����ѫ��һö��\n";
    }
}

//��������
void user::terminate()
{
    char name[msgLength] = { '\0' }; //�û���������

                                     //���û������û���
    for (int i = 0; i < maxLength; i++)
    {
        name[i] = userName[i];
    }
    //���͵ǳ�������û���
    sendMessage(LOGOUT_REQ, name);

    //�ȴ�������Ӧ��
    while (receiveInfo == WAIT);

    //�û���ʱΪ����״̬
    if (recvBuf[0])
    {
        //��շ��ͽ��ջ����� ����
        receiveInfo = WAIT;
        clearBuf();

        //����Ϣͬ����������
        synchron();
        std::cout << "�ǳ��ɹ���" << std::endl;
    }
    //��շ��ͽ��ջ����� ����
    receiveInfo = WAIT;
    clearBuf();

    //��������
    stop = yes;
}

//���û���ʤ�ʺ�С������Ϣͬ����������
void user::synchron()
{
    //ͬ��ʤ��
    char chWinRate[msgLength] = { '\0' }; //������Ϣ

                                          //�����ַ���ʽʤ��
    toString(chWinRate, winNum, playNum, 0);

    //��������
    sendMessage(SYNCHROWINRATE, chWinRate);

    //�ȴ�������Ӧ��
    while (receiveInfo == WAIT);

    //��շ��ͽ��ջ����� ����
    receiveInfo = WAIT;
    clearBuf();

    //��pokemonNum��С���� ѭ��pokemonNum��
    for (int i = 0; i < pokemonNum; i++)
    {
        char toStr[msgLength] = { '\0' }; //������Ϣ
                                          //���췢����Ϣ
        toString(toStr, poke[i]->kind, poke[i]->level, poke[i]->exp);

        //��������
        sendMessage(SYNCHRONIZATION, toStr);

        //�ȴ�������Ӧ��
        while (receiveInfo == WAIT);

        //��շ��ͽ��ջ����� ����
        receiveInfo = WAIT;
        clearBuf();
    }

    //�ͷ��û�����С������Դ
    for (int i = 0; i < pokemonNum; i++)
    {
        delete poke[i];
    }
}
