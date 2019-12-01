/**
* Number:hdu1011
* Title:Starship Troopers
* Status:WA
* Tag:[]
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
}edges[210];
int head[110],edge_id;
void addedge(int from,int to)
{
    edges[edge_id]=(Edge){from,to,head[from]};
    head[from]=edge_id++;
}

int r[110],w[110];
int dp[110][110];
void dfs(int u,int C,int pre)
{
    for(int i=C;i>=w[u];i--)dp[u][i]=r[u];
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs(v,C,u);
        for(int j=C;j>=w[i];j--)
        {
            for(int k=1;k<=j-w[u];k++)
            {
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
            }
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m;
    while(readi(n,m)!=EOF)
    {
        if(n==-1)break;
        edge_id=0;
        clr(head,-1);
        clr(dp,0);
        clr(r,0);
        clr(w,0);
        rep(i,1,n)
        {
            readi(w[i],r[i]);
            w[i]=(w[i]+19)/20;
        }
        repne(i,1,n)
        {
            int u,v; readi(u,v);
            addedge(u,v); addedge(v,u);
        }
        if(m==0)
        {
            printf("0\n");
            continue;
        }
        dfs(1,m,-1);
        printf("%d\n",dp[1][m]);
    }
    return 0;
}