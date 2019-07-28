/**
* Number:2223
* Title:cxx守株待兔
* Status:AC
* Tag:[最小点覆盖, hopcroft_karp]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

inline int readu()
{
    register int num = 0;
    register char ch;
    do{ ch = getchar(); }while(ch < '0' || ch > '9');
    do{ num = (num << 3) + (num << 1) + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    return num;
}

const int MAXN = 100010;
const int MAXM = 300010;

struct Edge
{
    int from, to, nxt;
}edges[MAXM];
int head[MAXN], edge_id;
void addedge(int from, int to)
{
    edges[edge_id] = (Edge){from, to, head[from]};
    head[from] = edge_id++;
}

int nx, ny, m; // x支节点数, y支节点数, 边数
int dep[MAXN], d;
int match[MAXN];
bool vis[MAXN];
bool bfs()
{
    d = INF;
    queue<int> Q;
    fill_n(dep, nx + ny + 1, 0);
    for(int i = 1; i <= nx; i++)
    {
        if(!match[i])
        {
            dep[i] = 1;
            Q.push(i);
        }
    }
    while(!Q.empty())
    {
        int u = Q.front(); Q.pop();
        if(dep[u] > d)break;
        for(int i = head[u]; ~i; i = edges[i].nxt)
        {
            int v = edges[i].to;
            if(dep[v])continue;
            dep[v] = dep[u] + 1;
            if(!match[v])d = dep[v];
            else
            {
                dep[match[v]] = dep[v] + 1;
                Q.push(match[v]);
            }
        }
    }
    return d != INF;
}
int dfs(int u)
{
    for(int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if(vis[v] || dep[u] + 1 != dep[v])continue;
        vis[v] = true;
        if(match[v] && dep[v] == d)continue;
        if(!match[v] || dfs(match[v]))
        {
            match[u] = v, match[v] = u;
            return 1;
        }
    }
    return 0;
}
int hopcroft_karp()
{
    int ans = 0;
    while(bfs())
    {
        fill_n(vis, nx + ny + 1, false);
        for(int i = 1; i <= nx; i++)
        {
            if(!match[i])ans += dfs(i);
        }
    }
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(nx,ny,m);
    std::fill_n(head,nx+ny+4,-1);
    repne(i,0,m)
    {
        int u=readu(),v=readu();
        addedge(u,nx+v);
    }
    int ans=hopcroft_karp();
    printf("%d",ans);
    return 0;
}