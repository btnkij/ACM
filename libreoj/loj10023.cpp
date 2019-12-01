/**
* Number:loj10023
* Title:「一本通 1.3 练习 2」平板涂色
* Status:AC
* Tag:[dfs]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <cassert>
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Node
{
    int x1,y1,x2,y2;
    int color;
}nodes[20];
int indeg[20];
bool vis[20];
struct Edge
{
    int from,to;
}edges[400];
int head[20],nxt[400],tot;
void addEdge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
    indeg[to]++;
}

bool isAdj(int up, int down)
{
    Node &a=nodes[up], &b=nodes[down];
    return a.y2==b.y1 && !(b.x1>a.x2 || b.x2<a.x1);
}

int n;
int ans;
void dfs(int color, int cnt, int dep)
{
    if(cnt>ans)return;
    if(dep==0)
    {
        ans=cnt;
        return;
    }
    repne(i,0,n)
    {
        if(vis[i] || indeg[i])continue;
        for(int j=head[i];~j;j=nxt[j])
        {
            indeg[edges[j].to]--;
        }
        vis[i]=true;
        dfs(nodes[i].color, cnt+int(color!=nodes[i].color), dep-1);
        vis[i]=false;
        for(int j=head[i];~j;j=nxt[j])
        {
            indeg[edges[j].to]++;
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n);
    repne(i,0,n)
    {
        Node& r=nodes[i];
        readi(r.y1,r.x1,r.y2,r.x2);
        readi(r.color);
    }
    mset(head,-1);
    repne2(i,0,n,j,0,n)
    {
        if(isAdj(i,j))
            addEdge(i,j);
    }
    ans=INF;
    dfs(-1, 0, n);
    printf("%d",ans);
    return 0;
}