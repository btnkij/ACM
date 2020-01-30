/**
* Number:ybt1331
* Title:后缀表达式的值
* Status:AC
* Tag:[stack, 栈]
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
typedef long long ll;

char expr[300];
char *p;
static union {
    ll num;
    char op;
};
int read()
{
    while (*p == ' ')
        p++;
    if (*p == '@')
        return EOF;
    if ('0' <= *p && *p <= '9')
    {
        num = 0;
        while ('0' <= *p && *p <= '9')
        {
            num = num * 10 + (*p & 0xF);
            p++;
        }
        return 1;
    }
    else
    {
        op = *p;
        p++;
        return 2;
    }
}
int main()
{
    gets(expr);
    p = expr;
    int type;
    stack<ll> S;
    while ((type = read()) != EOF)
    {
        if (type == 1)
        {
            S.push(num);
        }
        else if (type == 2)
        {
            ll rhs = S.top();
            S.pop();
            ll lhs = S.top();
            S.pop();
            switch (op)
            {
            case '+':
                S.push(lhs + rhs);
                break;
            case '-':
                S.push(lhs - rhs);
                break;
            case '*':
                S.push(lhs * rhs);
                break;
            case '/':
                S.push(lhs / rhs);
                break;
            }
        }
    }
    printf("%lld\n", S.top());
    return 0;
}