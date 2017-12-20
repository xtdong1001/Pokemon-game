#include"pokemon.h"

//������ ��������û����� ��socket�߳�
int main()
{
    //�򿪿ͻ���socket�߳�
    DWORD ThreadID2 = 0;
    HANDLE hClient = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)client, NULL, 0, &ThreadID2);

    //�û�����
    int request = -1;

    //����һ���û�
    user user1;

    //���������
    srand((int)time(NULL));

    //���û�δҪ���˳���ѭ����������
    while (request != STOP)
    {
        //��ӡ�˵�
        std::cout << "\n��ӭ��������С������Ϸ��" << std::endl;
        std::cout << "�����룺" << std::endl;
        std::cout << "1-ע��" << std::endl;
        std::cout << "2-��¼" << std::endl;
        std::cout << "3-�ǳ�" << std::endl;
        std::cout << "4-��ѯ��ǰ�����û�" << std::endl;
        std::cout << "5-��ѯ�����û�ӵ�еľ���" << std::endl;
        std::cout << "6-�μ�������" << std::endl;
        std::cout << "7-�μӾ�����" << std::endl;
        std::cout << "8-�鿴��ǰѫ��" << std::endl;
        std::cout << "9-�μ�2v2������" << std::endl;
        std::cout << "10-��ѯĳ�û�ʤ��" << std::endl;
        std::cout << "0-�˳�\n" << std::endl;

        //�û���������
        std::cin >> request;

        //���ú���ʵ���û�����
        switch (request)
        {
        case SIGNUP:           user1.signUp();           break;//�û�ע��
        case LOGIN:            user1.logIn();            break;//�û���¼
        case LOGOUT:           user1.logOut();           break;//�û��ǳ�
        case SEARCHONLINEUSER: user1.searchOnlineUser(); break;//��ѯ�����û�
        case SEARCHPOKEMON:    user1.searchPokemon();    break;//��ѯĳע���û���С����
        case STOP:             user1.terminate();        break;//��ֹ
        case UPGRADE:		   user1.upgrade();			 break;//������
        case DUEL:			   user1.duel();			 break;//������
        case MEDAL:			   user1.medal();			 break;//ѫ�²鿴
        case DOUBLE_UPGRADE:   user1.upgrade2v2();       break;//2v2������
        case SEARCHWINRATE:	   user1.searchWinRate();    break;//��ѯĳ�û�ʤ��
        default:break;
        }
    }
    return 0;
}

/*�������󵽷����� ���͵���Ϣ��һλΪ��������type �ڶ�λ֮��Ϊ����
sendMessage��������������������ƴ�� ���򿪿ͻ���socket�ķ�����*/
void sendMessage(char type, char *message)
{
    sendBuf[0] = type;
    strncpy(sendBuf + 1, message, msgLength);

    //�򿪿ͻ���socket�ķ�����
    sendRequest = SEND;
}

//�ж��û��������ʽ�Ƿ���ȷ
int isCorrectName(char *name)
{
    for (int i = 0; i < maxLength; i++)
    {
        //����С�ڵ���14������Ҫ��
        if (name[i] == '\0' && i>0)
        {
            //�û�����ʽ��ȷ
            return SUCCESS;
        }

        //�����к��в�����Ҫ����ַ�
        if (!((name[i] >= '0' && name[i] <= '9')
            || (name[i] >= 'a' && name[i] <= 'z')
            || (name[i] >= 'A' && name[i] <= 'Z')
            || (name[i] == '_')))
        {
            std::cout << "�û�����֧����ĸ�����ֺ��»���" << std::endl;
            //�û�����ʽ����
            return FAILURE;
        }
    }
    //�û������ȳ���14
    return FAILURE;
}

//�ж����������ʽ�Ƿ���ȷ
int isCorrectPword(char *word)
{
    for (int i = 0; i < maxLength; i++)
    {
        //���볤�Ȳ���6 ��ʽ����ȷ
        if (word[i] == '\0' && i <= 5)
        {
            //�����ʾ��Ϣ
            std::cout << "����Ϊ6-14λ" << std::endl;
            //�����ʽ����ȷ
            return FAILURE;
        }

        //���볤�ȴ��ڵ���6С�ڵ���14
        else if (word[i] == '\0' && i > 5)
        {
            //�����ʽ��ȷ
            return SUCCESS;
        }

        //�����к��в�����Ҫ����ַ�
        if (!(word[i] >= 33 && word[i] <= 126))
        {
            std::cout << "�û�����֧����ĸ�����ֺͱ�����" << std::endl;
            //�����ʽ����ȷ
            return FAILURE;
        }
    }
    //���볤�ȳ���14
    return FAILURE;
}

//��շ��ͽ��ջ�����
void clearBuf()
{
    for (int i = 0; i < BUF_SIZE; i++)
    {
        sendBuf[i] = '\0';
        recvBuf[i] = '\0';
    }
}

//���ַ�����info�ж�ȡС������Ϣ������kind��level��exp��
//��ʾС��������࣬�ȼ�������
//info��ʽΪ{kind,level,exp,}
void readInfo(char* info, int& kind, int& level, int& exp)
{
    int i;

    //ʹ��atoi����������ǰ���ַ���ת��Ϊ���ͣ��õ�С��������
    kind = atoi(info);
    //�ҵ���һ���������ڵ��±꣨��һ��ת������ʼƫ�Ƶ�ַ��
    for (i = 0; info[i] != ','; i++);
    i++;

    //ʹ��atoi����������ǰ���ַ���ת��Ϊ���ͣ��õ�С����ȼ���ת������ʼ��ַΪinfo+i��
    level = atoi(info + i);

    //�ҵ��ڶ����������ڵ��±꣨��һ��ת������ʼƫ�Ƶ�ַ��
    for (; info[i] != ','; i++);

    //ʹ��atoi����������ǰ���ַ���ת��Ϊ���ͣ��õ�С���龭��ֵ��ת������ʼ��ַΪinfo+i��
    exp = atoi(info + i + 1);
}

//����С�����ս��ʤ�� AΪ����С���� kind��level�ֱ�Ϊ�Լ�С���������͵ȼ�
void CalWinRate(pokemon *A, int kind, int level)
{
    //ѯ���û��Ƿ���Ҫ����ʤ�� 
    std::cout << "�Ƿ����ʤ�����ʣ�1-�� 0-��\n";
    //�û����󱣴���ȫ�ֱ���calWinRate��
    std::cin >> calWinRate;

    //������ʤ�� ����
    if (calWinRate == no)
    {
        return;
    }
    //�û�С����
    pokemon *pokea = NULL;

    //�����û�С��������ഴ��һ��һ����С����
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

    //����С����ȼ�������һ�����û�С����һ����С����
    pokea->setLevel(level);
    pokea->promoteLevel();
    std::cout << "����С����ʤ���ĸ���Ϊ��";

    //����simuFight����ģ��С����ս�� ����ʤ�� pokeaΪ�û�С���� AΪ����С����
    double winRate = simuFight(pokea, A);
    //������
    std::cout << winRate << "\n";

    //�ͷ���Դ
    delete pokea;
    //����û�����
    calWinRate = 0;
}

//ģ��С����ս��1000 �� ����С����competitorA��ʤ��
double simuFight(pokemon* competitorA, pokemon* competitorB)
{
    int time = 0;  //ս����ʱ
    int end = 0;   //ս��������־
    int death = 0; //С����������־
    int win = 0;   //�û�С�����ʤ����
                   //˫��С������ٶȣ��������ԣ�����ֵ
    int sp1 = 0, sp2 = 0, attr1 = 0, attr2 = 0, def1 = 0, def2 = 0;
    double winRate = 0; //ʤ��

                        //���С������ٶȣ��������Ժͷ���ֵ
    sp1 = competitorA->getSpeed();
    sp2 = competitorB->getSpeed();
    attr1 = competitorA->getAttr();
    attr2 = competitorB->getAttr();
    def1 = competitorA->getDef();
    def2 = competitorB->getDef();

    //ģ��1000��ս��
    for (int i = 0; i < 1000; i++)
    {
        //˫����С��������
        while (!death)
        {
            //��ʱ��
            time++;
            //�ֵ�С����A����
            if (time%sp1 == 0)
            {
                //               B���˺�����            A�Ĺ�������
                death = competitorB->damage(competitorA->attack(attr2, def2));
                //С����B���� С����Aʤ�� �˴�ģ��ս������
                if (death == 1)
                {
                    win++;
                    break;
                }
            }
            //�ֵ�С����B����
            if (time%sp2 == 0)
            {
                death = competitorA->damage(competitorB->attack(attr1, def1));
            }
        }

        //�������� С����������־����
        time = 0;
        death = 0;
        //˫��С�������ƻ�Ѫ
        competitorA->recover();
        competitorB->recover();
    }//1000��

     //����ʤ��
    winRate = double(win / 1000.0);
    return winRate;
}

/*��С������Ϣת��Ϊ�ַ����鱣����a��
  (���ڽ�С������Ϣͬ����������)
  a�ĸ�ʽΪ{kind,level,exp,}
  kΪС��������  lΪС����ȼ� eΪС���龭��*/
void toString(char*a, int k, int l, int e)
{
    //��ʼƫ�Ƶ�ַ
    int count = 0;

    //��С��������ת��Ϊ�ַ��������a��
    toChar(k, a, count);

    //��С����ȼ�ת��Ϊ�ַ��������a��
    toChar(l, a, count);

    //��С���龭��ת��Ϊ�ַ��������a��
    toChar(e, a, count);
}

//������aת��Ϊ�ַ������ͱ�����b��  cΪ�ַ�����ʼƫ�Ƶ�ַ
void toChar(int a, char*b, int& c)
{
    char x[10] = { '\0' };
    //��ʼ���ַ�����x
    for (int i = 0; i < 10; i++)
    {
        x[i] = '\0';
    }
    //����itoa����������ת��Ϊ�ַ�����
    itoa(a, x, 10);

    //���ַ�����x���Ƶ�b�� ��ʼ��ַΪb[c]
    strncpy(b + c, x, strlen(x));
    //�޸�ƫ�Ƶ�ַ �Ա���һ�δ��
    c = c + strlen(x);

    //����֮���ö��Ÿ���
    b[c] = ',';
    c++;
}