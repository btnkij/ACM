/**
* Number:ybt1198
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
#include <stack>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef long long ll;

char buffer[128];
double calc()
{
    scanf("%s", buffer);
    if ('0' <= buffer[0] && buffer[0] <= '9')
    {
        return atof(buffer);
    }
    switch (buffer[0])
    {
    case '+':
        return calc() + calc();
    case '-':
        return calc() - calc();
    case '*':
        return calc() * calc();
    case '/':
        return calc() / calc();
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    printf("%lf\n", calc());
    return 0;
}