/**
* Number:uva1391
* Title:Astronauts
* Status:评测有毒?
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
#include <list>
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

const int MAXN=100010;
const int MAXM=400010;

list<int> edges[MAXM];
void addedge(int from,int to)
{
    edges[from].push_back(to);
}

int dfsid,dfn[MAXN*2],low[MAXN*2];
int grpid,grp[MAXN*2];
stack<int> trace;
void tarjan(int u)
{
    dfn[u]=low[u]=++dfsid;
    trace.push(u);
    for(int v:edges[u])
    {
        if(!dfn[v])tarjan(v);
        if(!grp[v])low[u]=min(low[u],low[v]);
    }
    if(dfn[u]==low[u])
    {
        // printf("# %d",(u&1)?(u>>1)+16+1:(u>>1)+1);
        grp[u]=++grpid;
        while(trace.top()!=u)
        {
            int v=trace.top();
            grp[v]=grpid;
            // printf(" %d",(v&1)?(v>>1)+16+1:(v>>1)+1);
            trace.pop();
        }
        // printf("\n# grp %d\n",grpid);
        trace.pop();
    }
}

int age[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m;
    while(readi(n,m)!=EOF && n && m)
    {
        int sum=0;
        repne(i,0,n)
        {
            readi(age[i]);
            sum+=age[i];
        }
        repne(i,0,n)age[i]=int(age[i]*n>=sum);
        repne(i,0,n<<1)edges[i].clear();
        repne(i,0,m)
        {
            int u,v; readi(u,v);
            u--,v--;
            if(age[u]==age[v])
            {
                addedge(u<<1,v<<1|1);
                addedge(v<<1,u<<1|1);
                addedge(u<<1|1,v<<1);
                addedge(v<<1|1,u<<1);
            }
            else
            {
                addedge(u<<1|1,v<<1);
                addedge(v<<1|1,u<<1);
            }
        }
        clr(dfn,0); clr(grp,0); dfsid=grpid=0;
        repne(i,0,n<<1)if(!dfn[i])tarjan(i);
        // repne(i,0,n<<1)printf("%d\n",grp[i]);
        bool ok=true;
        repne(i,0,n)
        {
            if(grp[i<<1]==grp[i<<1|1])
            {
                ok=false;
                break;
            }
        }
        if(!ok)puts("No solution.");
        else
        {
            repne(i,0,n)
            {
                if(grp[i<<1]<grp[i<<1|1])printf("%c\n",age[i]?'A':'B');
                else puts("C");
            }
        }
    }
    return 0;
}