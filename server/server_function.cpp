#include"server.h"

/*将小精灵信息转化为字符数组保存在a中
  (用于将小精灵信息同步到服务器)
  a的格式为{kind,level,exp,}
  k为小精灵种类  l为小精灵等级 e为小精灵经验*/
void toString(char*a, elf s)
{
    //起始偏移地址
    int count = 0;

    //将小精灵种类转化为字符数组放在a中
    toChar(s.elfKind, a, count);

    //将小精灵等级转化为字符数组放在a中
    toChar(s.level, a, count);

    //将小精灵经验转化为字符数组放在a中
    toChar(s.exp, a, count);
}

//将用户胜率转化为字符串
void winRateStr(char*a, int k, int l, int e)
{
    //起始偏移地址
    int count = 0;

    //将胜利次数转化为字符数组放在a中
    toChar(k, a, count);

    //将总次数转化为字符数组放在a中
    toChar(l, a, count);

    toChar(e, a, count);
}

//将整数a转化为字符串类型保存在b中  c为字符串起始偏移地址
void toChar(int a, char*b, int& c)
{
    char x[10] = { '\0' };
    //初始化字符数组x
    for (int i = 0; i < 10; i++)
    {
        x[i] = '\0';
    }
    //调用itoa函数将整型转化为字符数组
    itoa(a, x, 10);

    //将字符数组x复制到b中 起始地址为b[c]
    strncpy(b + c, x, strlen(x));
    //修改偏移地址 以便下一次存放
    c = c + strlen(x);

    //数字之间用逗号隔开
    b[c] = ',';
    c++;
}

//从字符数组info中读取小精灵信息，存入kind，level，exp中
//表示小精灵的种类，等级，经验
//info格式为{kind,level,exp,}
void readInfo(char* info, int& kind, int& level, int& exp)
{
    int i;

    //使用atoi函数将逗号前的字符串转化为整型，得到小精灵种类
    kind = atoi(info);
    //找到第一个逗号所在的下标（下一次转换的起始偏移地址）
    for (i = 0; info[i] != ','; i++);
    i++;

    //使用atoi函数将逗号前的字符串转化为整型，得到小精灵等级（转换的起始地址为info+i）
    level = atoi(info + i);

    //找到第二个逗号所在的下标（下一次转换的起始偏移地址）
    for (; info[i] != ','; i++);

    //使用atoi函数将逗号前的字符串转化为整型，得到小精灵经验值（转换的起始地址为info+i）
    exp = atoi(info + i + 1);
}