/**
* Number:ybt1353
* Title:表达式括号匹配(stack)
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
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    stack<char> S;
    gets(expr);
    bool ans = true;
    for (char *p = expr; *p != '@'; p++)
    {
        if (*p == '(')
            S.push('(');
        else if (*p == ')')
        {
            if (S.empty() || S.top() != '(')
            {
                ans = false;
                break;
            }
            S.pop();
        }
    }
    if (!S.empty())
        ans = false;
    printf("%s\n", ans ? "YES" : "NO");
    return 0;
}