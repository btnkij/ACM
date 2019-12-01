/**
* Number:loj10091
* Title:「一本通 3.5 例 1」受欢迎的牛
* Status:AC
* Tag:[tarjan, 缩点]
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

const int MAXN=1e4+10;
const int MAXM=5e4+10;
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

int dfn[MAXN],low[MAXN],dfsid;
stack<int> trace;
int grpid,grp[MAXN],rk[MAXN];
void tarjan(int u)
{
    dfn[u]=low[u]=++dfsid;
    trace.push(u);
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(!dfn[v])tarjan(v);
        if(!grp[v])low[u]=min(low[u],low[v]);
    }
    if(dfn[u]==low[u])
    {
        int t;
        ++grpid;
        do
        {
            t=trace.top(); trace.pop();
            grp[t]=grpid, rk[grpid]++;
        } while (t!=u);
    }
}

int outdeg[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    clr(head,-1);
    repne(i,0,m)
    {
        int u,v; readi(u,v);
        addedge(u,v);
    }
    rep(i,1,n)if(!dfn[i])tarjan(i);
    for(int i=0;i<edgeid;i++)
    {
        Edge& e=edges[i];
        int u=grp[e.from],v=grp[e.to];
        if(u==v)continue;
        outdeg[u]++;
    }
    int ans=0,cnt=0;
    rep(i,1,grpid)
    {
        if(outdeg[i]==0)
        {
            ans+=rk[i];
            cnt++;
        }
    }
    if(cnt==1)printf("%d",ans);
    else printf("0");
    return 0;
}