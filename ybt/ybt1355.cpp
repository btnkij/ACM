/**
* Number:ybt1355
* Title:字符串匹配问题(strs)
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
int ord[128];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ord['{'] = 1;
    ord['}'] = -1;
    ord['['] = 2;
    ord[']'] = -2;
    ord['('] = 3;
    ord[')'] = -3;
    ord['<'] = 4;
    ord['>'] = -4;
    int T;
    scanf("%d", &T);
    while (T--)
    {
        stack<int> S;
        scanf("%s", expr);
        bool ans = true;
        for (char *p = expr; *p != '\0'; p++)
        {
            int n = ord[*p & 0xFF];
            if (n > 0 && (S.empty() || S.top() <= n))
            {
                S.push(n);
            }
            else if (n < 0 && !S.empty() && S.top() == -n)
            {
                S.pop();
            }
            else
            {
                ans = false;
                break;
            }
        }
        ans = ans && S.empty();
        printf("%s\n", ans ? "YES" : "NO");
    }
    return 0;
}