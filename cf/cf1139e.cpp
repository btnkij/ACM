/**
* Number:cf1139e
* Title:Maximize Mex
* Status:AC
* Tag:[二分图, hungary]
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
}edges[10010];
int head[5010],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int match[5010];
bool vis[5010];
bool dfs(int u)
{
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(vis[v])continue;
        vis[v]=true;
        if(match[v]==-1 || dfs(match[v]))
        {
            match[v]=u;
            return true;
        }
    }
    return false;
}

int p[5010],c[5010],k[5010];
bool disabled[5010];
int ans[5010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep(i,1,n)readi(p[i]);
    rep(i,1,n)readi(c[i]);
    int d; readi(d);
    rep(i,1,d)readi(k[i]),disabled[k[i]]=true;
    clr(head,-1);
    rep(i,1,n)if(!disabled[i])addedge(p[i],c[i]);
    for(int i=d;i>=1;i--)
    {
        clr(match,-1);
        for(int j=0;;j++)
        {
            clr(vis,false);
            if(!dfs(j))
            {
                ans[i]=j;
                break;
            }
        }
        addedge(p[k[i]],c[k[i]]);
    }
    rep(i,1,d)printf("%d\n",ans[i]);
    return 0;
}