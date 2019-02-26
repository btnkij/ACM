/**
* Number:ybt1203
* Title:扩号匹配问题
* Status:AC
* Tag:[栈]
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

struct Node
{
    char ch;
    int idx;
} nodes[110];
int tot;
char s[110];
char ans[110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while (scanf("%s", s) != EOF)
    {
        tot = 0;
        int len = strlen(s);
        for (int i = 0; i < len; i++)
        {
            ans[i] = ' ';
            if (s[i] == '(')
            {
                nodes[tot].ch = '$';
                nodes[tot].idx = i;
                tot++;
            }
            else if (s[i] == ')')
            {
                if (tot > 0 && nodes[tot - 1].ch == '$')
                    tot--;
                else
                {
                    nodes[tot].ch = '?';
                    nodes[tot].idx = i;
                    tot++;
                }
            }
        }
        for (int i = 0; i < tot; i++)
        {
            ans[nodes[i].idx] = nodes[i].ch;
        }
        ans[len] = '\0';
        printf("%s\n%s\n", s, ans);
    }
    return 0;
}