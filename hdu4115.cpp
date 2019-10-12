/**
* Number:hdu4115
* Title:Eliminate the Conflict
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

const int MAXN=2e4+10;
const int MAXM=4e4+10;

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
void addedge2(int from,int to)
{
    addedge(from,to);
    addedge(to,from);
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

int bob[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    rep(kase,1,T)
    {
        int n,m; readi(n,m);
        repne(i,0,n)readi(bob[i]),bob[i]--;
        clr(head,-1); edgeid=0;
        repne(i,0,m)
        {
            int a,b,k; readi(a,b,k);
            a--,b--;
            if(k==0)
            {
                if(bob[a]==bob[b])
                {
                    addedge2(a<<1,b<<1);
                    addedge2(a<<1|1,b<<1|1);
                }
                else
                {
                    if((bob[a]+1)%3==bob[b])swap(a,b);
                    addedge(a<<1|1,a<<1);
                    addedge(b<<1,b<<1|1);
                }
            }
            else if(k==1)
            {
                if(bob[a]==bob[b])
                {
                    addedge2(a<<1,b<<1|1);
                    addedge2(b<<1,a<<1|1);
                }
                else
                {
                    if((bob[a]+1)%3==bob[b])swap(a,b);
                    addedge(a<<1,b<<1);
                    addedge(b<<1|1,a<<1|1);
                }
            }
        }
        clr(dfn,0); clr(grp,0); dfsid=grpid=0;
        repne(i,0,n<<1)if(!dfn[i])tarjan(i);
        bool ok=true;
        repne(i,0,n)
        {
            if(grp[i<<1]==grp[i<<1|1])
            {
                ok=false;
                break;
            }
        }
        printf("Case #%d: %s\n",kase,ok?"yes":"no");
    }
    return 0;
}