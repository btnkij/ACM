/**
* Number:uva1411
* Title:Ants
* Status:AC
* Tag:[分治]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

struct Node
{
    int id;
    int x, y;
    int type;
    double ang;
};
Node nodes[210];
void calc_angle(int left, int right)
{
    nodes[left].ang = 0;
    for (int i = left + 1; i < right; i++)
    {
        double vx = nodes[i].x - nodes[left].x;
        double vy = nodes[i].y - nodes[left].y;
        nodes[i].ang = vx / sqrt(vx * vx + vy * vy);
    }
}
bool comp_by_y(const Node &lhs, const Node &rhs)
{
    return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);
}
bool comp_by_angle(const Node &lhs, const Node &rhs)
{
    return lhs.ang > rhs.ang;
}
int ans[210];
void solve(int left, int right)
{
    if (left >= right)
        return;
    sort(nodes + left, nodes + right, comp_by_y);
    calc_angle(left, right);
    sort(nodes + left + 1, nodes + right, comp_by_angle);
    int cnt = 1;
    Node &refn = nodes[left];
    for (int i = left + 1; i < right; i++)
    {
        if (nodes[i].type == refn.type)
            cnt++;
        else
            cnt--;
        if (cnt == 0)
        {
            if (refn.type == 1)
                ans[refn.id] = nodes[i].id;
            else
                ans[nodes[i].id] = refn.id;
            solve(left + 1, i);
            solve(i + 1, right);
            return;
        }
    }
}
int main()
{
    bool first = true;
    int n;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d %d", &nodes[i].x, &nodes[i].y);
            nodes[i].type = 1;
            nodes[i].id = i + 1;
        }
        for (int i = n; i < (n << 1); i++)
        {
            scanf("%d %d", &nodes[i].x, &nodes[i].y);
            nodes[i].type = 2;
            nodes[i].id = i + 1 - n;
        }
        solve(0, n << 1);
        if (!first)
        {
            printf("\n");
        }
        first = false;
        for (int i = 1; i <= n; i++)
        {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}