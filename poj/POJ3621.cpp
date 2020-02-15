/**
* Number:poj3621
* Title:Sightseeing Cows
* Status:AC
* Tag:[分数规划, spfa, 负环, 二分]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
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

const int MAXN=1e3+10;
const int MAXM=5e3+10;
struct Edge
{
    int from,to,dis,nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to,int dis)
{
    edges[edgeid]={from,to,dis,head[from]};
    head[from]=edgeid++;
}

int f[MAXN];
double mid,dis[MAXN];
bool vis[MAXN];
bool spfa(int u)
{
    vis[u]=true;
    bool ans=false;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        double c=f[e.to]-mid*e.dis;
        if(dis[u]+c>dis[e.to])
        {
            dis[e.to]=dis[u]+c;
            if(vis[e.to] || spfa(e.to))
            {
                ans=true;
                break;
            }
        }
    }
    vis[u]=false;
    return ans;
}
bool check(int n)
{
    fill_n(dis,n+1,0);
    rep(i,1,n)if(spfa(i))return true;
    return false;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    clr(head,-1);
    rep(i,1,n)readi(f[i]);
    repne(i,0,m)
    {
        int u,v,w; readi(u,v,w);
        addedge(u,v,w);
    }
    double lt=0,rt=1e6+10;
    while(rt-lt>1e-6)
    {
        mid=(lt+rt)/2;
        if(check(n))lt=mid;
        else rt=mid;
    }
    printf("%.2f\n",lt);
    return 0;
}