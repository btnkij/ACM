/**
* Number:ybt1361
* Title:产生数(Produce)
* Status:AC
* Tag:[warshall, 传递闭包]
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

bool f[10][10];
int cnt[10];
char n[20];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int k;
    scanf("%s %d", n, &k);
    int len = strlen(n);
    for (int i = 0; i < k; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        f[x][y] = true;
        if (x != 0)
            f[y][x] = true;
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (f[j][i])
            {
                for (int k = 0; k < 10; k++)
                {
                    f[j][k] = f[j][k] || f[i][k];
                }
            }
        }
    }
    for (int i = 0; i < 10; i++)
    {
        f[i][i] = true;
        for (int j = 0; j < 10; j++)
        {
            if (f[i][j])
                cnt[i]++;
        }
    }
    int ans = 1;
    for (int i = 0; i < len; i++)
    {
        // if (i == len - 1 && f[n[i] & 0xF][0])
        // {
        //     cnt[n[i] & 0xF]--;
        // }
        ans *= cnt[n[i] & 0xF];
    }
    printf("%d\n", ans);
    return 0;
}