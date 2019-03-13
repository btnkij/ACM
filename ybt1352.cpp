/**
* Number:ybt1352
* Title:【例4-13】奖金
* Status:AC
* Tag:[拓扑排序]
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

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Edge
{
    int from,to;
}edges[20010];
int head[10010],nxt[20010],tot;
void add_edge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int sorted[10010],ans;
bool ok, vis[10010], pass[10010];
void dfs(int u)
{
    pass[u]=true;
    int w=100;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(pass[v])ok=false;
        if(ok && !sorted[v])dfs(v);
        if(!ok)return;
        w=max(w,sorted[v]+1);
    }
    pass[u]=false;
    vis[u]=true;
    sorted[u]=w;
    ans+=w;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep(i,1,n)head[i]=-1;
    while(m--)
    {
        int a,b; readi(a,b);
        add_edge(a,b);
    }
    ok=true;
    rep(i,1,n)
    {
        if(!vis[i])dfs(i);
        if(!ok)break;
    }
    if(ok)printf("%d",ans);
    else printf("Poor Xed");
    return 0;
}