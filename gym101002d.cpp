/**
* Number:gym101002d
* Title:Programming Team
* Status:AC
* Tag:[二分, 树型依赖背包]
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

struct Edge
{
    int from,to,nxt;
}edges[10000];
int head[5000],edge_id;
void addedge(int from,int to)
{
    edges[edge_id]=(Edge){from,to,head[from]};
    head[from]=edge_id++;
}

int k,n;
int s[5000],p[5000];
double w[5000];
double dp[2510][2510];
int sz[2510],pos[2510],tot;
void dfs(int u,int pre)
{
    sz[u]=1;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs(v,u);
        sz[u]+=sz[v];
    }
    pos[++tot]=u;
}
bool check(double mid,int C)
{
    rep(i,1,tot)w[i]=p[i]-mid*s[i];
    // rep2(i,0,tot,j,1,C)dp[i][j]=-INF;
    fill((double*)dp,(double*)(dp+2510),-INF);
    rep(i,0,tot)dp[i][0]=0;
    for(int i=1;i<=tot;i++)
    {
        int x=pos[i];
        for(int j=1;j<=C;j++)
        {
            dp[i][j]=max(dp[i-1][j-1]+w[x],dp[i-sz[x]][j]);
        }
    }
    return dp[tot][C]<=0;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clr(head,-1);
    readi(k,n);
    rep(i,1,n)
    {
        int pa; readi(s[i],p[i],pa);
        addedge(i,pa); addedge(pa,i);
    }
    dfs(0,-1);
    double lt=0, rt=1e4+10;
    while(rt-lt>1e-6)
    {
        double mid=(lt+rt)/2;
        if(check(mid,k+1))rt=mid;
        else lt=mid;
    }
    printf("%.3lf\n",lt);
    return 0;
}