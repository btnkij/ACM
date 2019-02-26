/**
* Number:noi8465
* Title:逆波兰表达式
* Status:AC
* Tag:[递归]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

char s[100];
double eval()
{
    scanf("%s",s);
    switch(s[0])
    {
        case '+':
        return eval()+eval();
        break;
        case '-':
        return eval()-eval();
        break;
        case '*':
        return eval()*eval();
        break;
        case '/':
        return eval()/eval();
        break;
        default:
        return atof(s);
    }
}
int main()
{
    printf("%.6lf\n",eval());
    return 0;
}