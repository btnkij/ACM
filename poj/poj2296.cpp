/**
* Number:poj2296
* Title:Map Labeler
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

struct Point
{
    int x,y;
}pos[110];
bool check(int n,int mid)
{
    clr(head,-1); edgeid=0;
    repne2(i,0,n,j,0,i)
    {
        if(abs(pos[i].x-pos[j].x)>=mid)continue;
        if(abs(pos[i].y-pos[j].y)>=(mid<<1))continue;
        int up=i,down=j;
        if(pos[up].y<pos[down].y)swap(down,up);
        if(pos[up].y==pos[down].y)
        {
            addedge(up<<1,down<<1|1);
            addedge(up<<1|1,down<<1);
            addedge(down<<1,up<<1|1);
            addedge(down<<1|1,up<<1);
        }
        else if(pos[up].y-pos[down].y<mid)
        {
            addedge(up<<1|1,up<<1);
            addedge(down<<1,down<<1|1);
        }
        else if(pos[up].y-pos[down].y<mid*2)
        {
            addedge(up<<1|1,down<<1|1);
            addedge(down<<1,up<<1);
        }
    }
    clr(dfn,0); clr(grp,0); dfsid=grpid=0;
    repne(i,0,n<<1)if(!dfn[i])tarjan(i);
    repne(i,0,n)
    {
        if(grp[i<<1]==grp[i<<1|1])
        {
            return false;
        }
    }
    return true;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        repne(i,0,n)readi(pos[i].x,pos[i].y);
        int lt=0,rt=10010;
        while(lt<rt)
        {
            int mid=(lt+rt+1)>>1;
            if(!check(n,mid))rt=mid-1;
            else lt=mid;
        }
        printf("%d\n",lt);
    }
    return 0;
}