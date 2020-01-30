/**
* Number:uva1411
* Title:Ants
* Status:AC
* Tag:[二分图, km, 最佳匹配, 完美匹配]
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
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)


const double eps=1e-6;
int n;
double adj[110][110];
int lef[110];
bool visx[110],visy[110];
double lx[110],ly[110];
bool dfs(int u)
{
    visx[u]=true;
    rep(v,1,n)
    {
        if(visy[v] || fabs(lx[u]+ly[v]-adj[u][v])>eps)continue;
        visy[v]=true;
        if(!lef[v] || dfs(lef[v]))
        {
            lef[v]=u;
            return true;
        }
    }
    return false;
}
int update()
{
    double delta=1e100;
    rep(i,1,n)if(visx[i])
        rep(j,1,n)if(!visy[j])
            delta=min(delta,lx[i]+ly[j]-adj[i][j]);
    rep(i,1,n)
    {
        if(visx[i])lx[i]-=delta;
        if(visy[i])ly[i]+=delta;
    }
}
void km()
{
    clr(lef,0); clr(ly,0);
    rep(i,1,n)lx[i]=*max_element(adj[i]+1,adj[i]+n+1);
    rep(i,1,n)
    {
        while(true)
        {
            clr(visx,false); clr(visy,false);
            if(dfs(i))break;
            update();
        }
    }
}

struct Point
{
    int x,y;
}pos1[110],pos2[110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(readi(n)!=EOF)
    {
        rep(i,1,n)readi(pos1[i].x,pos1[i].y);
        rep(i,1,n)readi(pos2[i].x,pos2[i].y);
        rep2(i,1,n,j,1,n)
        {
            Point &p1=pos1[i],&p2=pos2[j];
            adj[j][i]=-sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
        }
        km();
        rep(i,1,n)printf("%d\n",lef[i]);
    }
    return 0;
}


/**
* Number:uva1411
* Title:Ants
* Status:AC
* Tag:[分治]
**/

/*
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
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
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
*/