#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <unordered_map>
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

struct Edge
{
    int from,to,nxt;
}edges[MAXN*2];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

unordered_map<int,int> tree;
void add(int idx,int delta)
{
    while(idx<=1000000001)
    {
        tree[idx]+=delta;
        idx+=idx&-idx;
    }
}
int query(int idx)
{
    int sum=0;
    while(idx)
    {
        if(tree.count(idx))sum+=tree[idx];
        idx^=idx&-idx;
    }
    return sum;
}

int deg[MAXN],a[MAXN];
ll k,ans;
void dfs(int u,int pre)
{
    int top=1000000000;
    if(a[u] && k/a[u]<top)top=k/a[u];
    ans+=query(top+1);
    add(a[u]+1,1);
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs(v,u);
    }
    add(a[u]+1,-1);
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
        int n; scanf("%d %lld",&n,&k);
        rep(i,1,n)readi(a[i]);
        clr(head,-1); edgeid=0;
        clr(deg,0);
        repne(i,1,n)
        {
            int u,v; readi(u,v);
            addedge(u,v);
            deg[v]++;
        }
        int root=find(deg+1,deg+n+1,0)-deg;
        tree.clear();
        ans=0;
        dfs(root,-1);
        printf("%lld\n",ans);
    }
    return 0;
}