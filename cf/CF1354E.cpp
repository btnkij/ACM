/**
* Number:CF1354E
* Title:Graph Coloring
* Status:AC
* Tag:[二分图, 分组背包]
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

constexpr int MAXN=5010;
constexpr int MAXM=2e5+10;
struct Edge
{
    int from,to,nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int color[MAXN];
int w[MAXN][2],entry[MAXN];
void dfs(int id,int u,int c)
{
    color[u]=c;
    w[id][c-1]++;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(color[v]==0)dfs(id,v,c^3);
        else if(color[v]==c)
        {
            puts("NO");
            exit(0);
        }
    }
}

int dp[MAXN][MAXN],pre[MAXN][MAXN];
int ans[MAXN];
void paint(int u,int c)
{
    if(color[u]==c)ans[u]=2;
    else ans[u]=1;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(ans[v])continue;
        paint(v,c);
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,n1,n2,n3;
    scanf("%d %d %d %d %d",&n,&m,&n1,&n2,&n3);
    fill_n(head,n+1,-1);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        addedge(u,v); addedge(v,u);
    }
    int id=0;
    for(int i=1;i<=n;i++)
    {
        if(!color[i])
        {
            entry[++id]=i;
            dfs(id,i,1);
        }
    }
    dp[0][0]=1;
    for(int i=1;i<=id;i++)
    {
        for(int j=n2;j>=0;j--)
        {
            for(int k=0;k<2;k++)
            {
                if(j-w[i][k]>=0 && dp[i-1][j-w[i][k]])
                {
                    dp[i][j]=1;
                    pre[i][j]=k;
                    break;
                }
            }
        }
    }
    if(dp[id][n2]==0)
    {
        puts("NO");
        exit(0);
    }
    puts("YES");
    for(int i=id,x=n2;i>=1;i--)
    {
        paint(entry[i],pre[i][x]+1);
        x-=w[i][pre[i][x]];
    }
    for(int i=1;i<=n;i++)
    {
        if(ans[i]==1)
        {
            if(n1)
            {
                printf("1");
                n1--;
            }
            else printf("3");
        }
        else printf("2");
    }
    return 0;
}