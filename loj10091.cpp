/**
* Number:loj10091
* Title:「一本通 3.5 例 1」受欢迎的牛
* Status:AC
* Tag:[tarjan]
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
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=10010;
const int MAXM=50010;

struct Edge
{
    int from,to,nxt;
}edges[MAXM];
int head[MAXN],edge_id;
void addedge(int from,int to)
{
    edges[++edge_id]=(Edge){from,to,head[from]};
    head[from]=edge_id;
}

int ord[MAXN],low[MAXN],dfs_id;
int grp[MAXN],grp_id;
int rk[MAXN];
stack<int> trace;
void tarjan(int u)
{
    ord[u]=low[u]=++dfs_id;
    trace.push(u);
    for(int i=head[u];i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(!ord[v])tarjan(v);
        if(!grp[v])low[u]=min(low[u],low[v]);
    }
    if(ord[u]==low[u])
    {
        ++grp_id;
        int tmp;
        do
        {
            tmp=trace.top(); trace.pop();
            grp[tmp]=grp_id;
            rk[grp_id]++;
        }while(tmp!=u);
    }
}

bool out[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    repne(i,0,m)
    {
        int a,b; readi(a,b);
        addedge(a,b);
    }
    rep(u,1,n)
    {
        if(!ord[u])tarjan(u);
    }
    rep(u,1,n)
    {
        for(int i=head[u];i;i=edges[i].nxt)
        {
            int v=edges[i].to;
            if(grp[u]!=grp[v])
            {
                out[grp[u]]=true;
            }
        }
    }
    int cnt=0,ans;
    rep(i,1,grp_id)
    {
        if(!out[i])
        {
            ans=rk[i];
            cnt++;
        }
    }
    if(cnt==1)printf("%d",ans);
    else printf("0");
    return 0;
}