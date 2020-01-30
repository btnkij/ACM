/**
* Number:ybt1336
* Title:找树根和孩子
* Status:AC
* Tag:[树]
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

int adj[1004][204];
int indeg[1004];
int outdeg[1004];
bool exist[1004];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    scanf("%d %d", &n, &m);
    int node = -1;
    int maxout = 0;
    while (m--)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        exist[x] = exist[y] = true;
        outdeg[x]++;
        indeg[y]++;
        adj[x][0]++;
        adj[x][adj[x][0]] = y;
        if (outdeg[x] > maxout)
        {
            maxout = outdeg[x];
            node = x;
        }
    }
    for (int i = 0; i < 1004; i++)
    {
        if (!exist[i])
            continue;
        if (indeg[i] == 0)
        {
            printf("%d\n", i);
            break;
        }
    }
    printf("%d\n", node);
    sort(&adj[node][1], &adj[node][adj[node][0] + 1]);
    for (int i = 1; i <= adj[node][0]; i++)
    {
        printf("%d ", adj[node][i]);
    }
    return 0;
}