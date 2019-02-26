/**
* Number:ybt1354
* Title:括弧匹配检验
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
#define PI acos(-1)
typedef long long ll;

char expr[300];
int main()
{
    stack<char> S;
    gets(expr);
    bool ans = true;
    for (char *p = expr; *p != '\0'; p++)
    {
        if (*p == '(' || *p == '[')
            S.push(*p);
        else if (*p == ')')
        {
            if (S.empty() || S.top() != '(')
            {
                ans = false;
                break;
            }
            S.pop();
        }
        else if (*p == ']')
        {
            if (S.empty() || S.top() != '[')
            {
                ans = false;
                break;
            }
            S.pop();
        }
    }
    if (!S.empty())
        ans = false;
    printf("%s\n", ans ? "OK" : "Wrong");
    return 0;
}