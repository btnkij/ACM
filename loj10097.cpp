/**
* Number:loj10097
* Title:「一本通 3.5 练习 5」和平委员会
* Status:AC
* Tag:[2-sat, tarjan]
* desc: n个党派，2n个代表，2i-1和2i属于一个党派，m对代表不能共存，输出每个党派选一名代表的方案
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

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 8010 * 4;
const int MAXM = 2e6 + 10;
struct Edge
{
    int from, to, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = (Edge){from, to, head[from]};
    head[from] = edgeid++;
}
void addedge2(int u, int v)
{
    addedge(u, v);
    addedge(v, u);
}

int dfn[MAXN], low[MAXN], dfsid; // dfs序，dfs树上可以连接的最小节点
int grp[MAXN], grpid;            // 节点的分组号，是逆拓扑序
stack<int> trace;                // 当前dfs路径
void tarjan(int u)
{
    dfn[u] = low[u] = ++dfsid;
    trace.push(u);
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (!dfn[v])
            tarjan(v); // 如果v没有计算过，先tarjan点v
        if (!grp[v])
            low[u] = min(low[u], low[v]);
    }
    if (dfn[u] == low[u]) // u是强联通分量的根节点
    {
        grp[u] = ++grpid;
        while (trace.top() != u)
        {
            grp[trace.top()] = grpid;
            trace.pop();
        }
        trace.pop();
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    readi(n, m); // 点数，边数
    clr(head, -1);
    repne(i, 0, m)
    {
        int u, v;
        readi(u, v); // u与v有矛盾
        u--, v--;
        // u-选u u^1-选u的对立面
        // u->v表示如果选u则一定要选v
        addedge(u, v ^ 1);
        addedge(v, u ^ 1);
    }
    rep(i, 1, n << 1) if (!dfn[i]) tarjan(i);
    rep(i, 1, n << 1)
    {
        if (grp[i] == grp[i ^ 1]) // 矛盾
        {
            printf("NIE");
            return 0;
        }
    }
    rep(i, 1, n << 1) if (grp[i] < grp[i ^ 1])
        // (i^1)->(i)，选了(i^1)就必须选(i)，那么只能选i
        printf("%d\n", i);
    return 0;
}

/**
* Number:loj10097
* Title:「一本通 3.5 练习 5」和平委员会
* Status:AC
* Tag:[2-sat, tarjan]
**/

/*
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

const int MAXN=8010*4;
const int MAXM=2e6+10;
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
void addedge2(int u,int v)
{
    addedge(u,v);
    addedge(v,u);
}

int dfn[MAXN],low[MAXN],dfsid;
int grp[MAXN],grpid;
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
        while(trace.top()!=u)
        {
            grp[trace.top()]=grpid;
            trace.pop();
        }
        trace.pop();
    }
}

int n,m;
inline int peer(int x)
{
    return ((x-1)^1)+1;
}
inline int opp(int x)
{
    return x+(n<<1);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clr(head,-1);
    readi(n,m);
    rep(i,1,n<<1)addedge2(i,opp(peer(i)));
    repne(i,0,m)
    {
        int u,v; readi(u,v);
        addedge(u,opp(v));
        addedge(v,opp(u));
    }
    rep(i,1,n<<1)if(!dfn[i])tarjan(i);
    rep(i,1,n<<1)
    {
        if(grp[i]==grp[opp(i)])
        {
            printf("NIE");
            return 0;
        }
    }
    rep(i,1,n<<1)
    {
        if(grp[i]<grp[opp(i)])
        {
            printf("%d\n",i);
        }
    }
    return 0;
}
*/