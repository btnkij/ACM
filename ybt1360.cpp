/**
* Number:ybt1360
* Title:奇怪的电梯(lift)
* Status:AC
* Tag:[bfs]
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

int mincnt[204];
int d[204];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &d[i]);
    }
    memset(mincnt, INF, sizeof(mincnt));
    queue<int> Q;
    Q.push(a);
    mincnt[a] = 0;
    while (!Q.empty())
    {
        int t = Q.front();
        Q.pop();
        if (t == b)
            break;
        int cnt = mincnt[t] + 1;
        int nextt = t - d[t];
        if (nextt > 0 && cnt < mincnt[nextt])
        {
            mincnt[nextt] = cnt;
            Q.push(nextt);
        }
        nextt = t + d[t];
        if (nextt <= n && cnt < mincnt[nextt])
        {
            mincnt[nextt] = cnt;
            Q.push(nextt);
        }
    }
    printf("%d\n", mincnt[b] == INF ? -1 : mincnt[b]);
    return 0;
}