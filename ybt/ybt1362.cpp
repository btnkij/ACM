/**
* Number:ybt1362
* Title:家庭问题(family)
* Status:AC
* Tag:[并查集]
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

int ufs[104];
int rel[104];
int find(int x)
{
    return x == ufs[x] ? x : ufs[x] = find(ufs[x]);
}
bool merge(int x, int y)
{
    int rx = find(x);
    int ry = find(y);
    if (rx == ry)
        return false;
    ufs[rx] = ry;
    rel[ry] += rel[rx];
    return true;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        ufs[i] = i;
        rel[i] = 1;
    }
    while (k--)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        merge(a, b);
    }
    int cnt = 0;
    int maxmem = -INF;
    for (int i = 1; i <= n; i++)
    {
        int r = find(i);
        if (rel[r])
        {
            cnt++;
            maxmem = max(maxmem, rel[r]);
            rel[r] = 0;
        }
    }
    printf("%d %d\n", cnt, maxmem);
    return 0;
}