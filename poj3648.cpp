/**
* Number:poj3648
* Title:Wedding
* Status:AC
* Tag:[2-sat, tarjan]
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

const int MAXN=110*2;
const int MAXM=MAXN*MAXN;

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

int dfsid,dfn[MAXN],low[MAXN];
int grpid,grp[MAXN];
stack<int> trace;
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
        grp[u]=++grpid;
        while(trace.top()!=u)grp[trace.top()]=grpid,trace.pop();
        trace.pop();
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m;
    while(readi(n,m)!=EOF && (n|m))
    {
        clr(head,-1); edgeid=0;
        addedge(0,1);
        repne(i,0,m)
        {
            int u,v; char u1,v1;
            scanf("%d%c %d%c",&u,&u1,&v,&v1);
            u=u1=='w'?u<<1:u<<1|1;
            v=v1=='w'?v<<1:v<<1|1;
            addedge(u,v^1);
            addedge(v,u^1);
        }
        clr(dfn,0); clr(grp,0); dfsid=grpid=0;
        repne(i,0,n<<1)if(!dfn[i])tarjan(i);
        bool ok=true;
        for(int i=0;i<(n<<1);i+=2)
        {
            if(grp[i]==grp[i^1])
            {
                ok=false;
                break;
            }
        }
        if(!ok)puts("bad luck");
        else
        {
            repne(i,2,n<<1)
            {
                if(grp[i]>grp[i^1])
                {
                    printf("%d%c ",i>>1,(i&1)==0?'w':'h');
                }
            }
            puts("");
        }
    }
    return 0;
}