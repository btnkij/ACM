/**
 * 
 * 输入输出外挂
 * 
**/

#include <cstdio>

// 读非负int
int readu()
{
    int num = 0;
    char ch;
    do{ ch = getchar(); }while(ch < '0' || ch > '9');
    do{ num = num * 10 + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    return num;
}

// 读任意int
int read()
{
    int num = 0;
    char ch;
    bool sign = false;
    do
    {
        ch = getchar();
        if(ch == '-')sign = true;
    }while(ch < '0' || ch > '9');
    do{ num = num * 10 + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    if(sign)num = -num;
    return num;
}