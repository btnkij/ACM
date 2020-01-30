/**
* Number:ybt1220
* Title:单词接龙
* Status:AC
* Tag:[dfs]
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

int adj[24][24];
int n;
char word[24][24];
int len[24];
int vis[24];
bool match(int i, int j, int offset)
{
    char *p1 = &word[i][offset];
    char *p2 = &word[j][0];
    while (*p1 == *p2)
        p1++, p2++;
    return *p1 == '\0';
}
int ans;
void dfs(int pre, int curlen)
{
    ans = max(ans, curlen);
    for (int i = 0; i < n; i++)
    {
        if (vis[i] < 2 && adj[pre][i])
        {
            vis[i]++;
            dfs(i, curlen + adj[pre][i]);
            vis[i]--;
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", word + i);
        len[i] = strlen(word[i]);
        for (int j = 0; j < len[i]; j++)
        {
            word[i][j] |= 0x20;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int lb = max(len[i] + 1 - len[j], 1);
            int ub = len[i] - 1;
            for (int k = ub; k >= lb; k--)
            {
                if (match(i, j, k))
                {
                    adj[i][j] = len[j] - (len[i] - k);
                    break;
                }
            }
        }
    }
    char head[4];
    scanf("%s", head);
    head[0] |= 0x20;
    ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (word[i][0] == head[0])
        {
            vis[i]++;
            dfs(i, len[i]);
            vis[i]--;
        }
    }
    printf("%d\n", ans);
    return 0;
}