/**
* Number:ybt1253
* Title:抓住那头牛
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d", &i1, &i2, &i3, &i4)

bool vis[200004];
struct Node
{
    int x, t;
};
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, k;
    readi2(n, k);
    int ans;
    queue<Node> Q;
    Q.push((Node){n, 0});
    while (!Q.empty())
    {
        Node node = Q.front();
        Q.pop();
        if (node.x == k)
        {
            ans = node.t;
            break;
        }
        if (vis[node.x])
            continue;
        vis[node.x] = true;
        if (node.x > 0 && !vis[node.x - 1])
            Q.push((Node){node.x - 1, node.t + 1});
        if (node.x < k)
        {
            if (!vis[node.x + 1])
                Q.push((Node){node.x + 1, node.t + 1});
            if (!vis[node.x << 1])
                Q.push((Node){node.x << 1, node.t + 1});
        }
    }
    printf("%d\n", ans);
    return 0;
}