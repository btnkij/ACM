/**
* Number:uva1146
* Title:Now or later
* Status:AC
* Tag:[2-sat, tarjan, 二分]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
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

const int MAXN=2010;

struct Edge
{
    int from,to,nxt;
}edges[MAXN*MAXN*4];
int head[MAXN*2],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int dfsid,dfn[MAXN*2],low[MAXN*2];
int grpid,grp[MAXN*2];
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

int t[MAXN*2];
bool check(int n,int mid)
{
    clr(head,-1); edgeid=0;
    clr(dfn,0); clr(grp,0); dfsid=grpid=0;
    repne2(i,0,n,j,0,i)
    {
        if(abs(t[i<<1]-t[j<<1])<mid)
        {
            addedge(i<<1,j<<1|1);
            addedge(j<<1,i<<1|1);
        }
        if(abs(t[i<<1]-t[j<<1|1])<mid)
        {
            addedge(i<<1,j<<1);
            addedge(j<<1|1,i<<1|1);
        }
        if(abs(t[i<<1|1]-t[j<<1])<mid)
        {
            addedge(i<<1|1,j<<1|1);
            addedge(j<<1,i<<1);
        }
        if(abs(t[i<<1|1]-t[j<<1|1])<mid)
        {
            addedge(i<<1|1,j<<1);
            addedge(j<<1|1,i<<1);
        }
    }
    repne(i,0,n<<1)if(!dfn[i])tarjan(i);
    repne(i,0,n)if(grp[i<<1]==grp[i<<1|1])return false;
    return true;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF)
    {
        repne(i,0,n)readi(t[i<<1],t[i<<1|1]);
        int lt=0,rt=10000000;
        while(lt<rt)
        {
            int mid=(lt+rt+1)>>1;
            if(check(n,mid))lt=mid;
            else rt=mid-1;
        }
        printf("%d\n",lt);
    }
    return 0;
}