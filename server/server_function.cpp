#include"server.h"

/*��С������Ϣת��Ϊ�ַ����鱣����a��
  (���ڽ�С������Ϣͬ����������)
  a�ĸ�ʽΪ{kind,level,exp,}
  kΪС��������  lΪС����ȼ� eΪС���龭��*/
void toString(char*a, elf s)
{
    //��ʼƫ�Ƶ�ַ
    int count = 0;

    //��С��������ת��Ϊ�ַ��������a��
    toChar(s.elfKind, a, count);

    //��С����ȼ�ת��Ϊ�ַ��������a��
    toChar(s.level, a, count);

    //��С���龭��ת��Ϊ�ַ��������a��
    toChar(s.exp, a, count);
}

//���û�ʤ��ת��Ϊ�ַ���
void winRateStr(char*a, int k, int l, int e)
{
    //��ʼƫ�Ƶ�ַ
    int count = 0;

    //��ʤ������ת��Ϊ�ַ��������a��
    toChar(k, a, count);

    //���ܴ���ת��Ϊ�ַ��������a��
    toChar(l, a, count);

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