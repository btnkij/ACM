/**
* Number:loj10160
* Title:「一本通 5.2 练习 3」周年纪念晚会 
* Status:AC
* Tag:[树型dp]
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

struct Edge
{
    int from,to;
}edges[6010*2];
int head[6010],nxt[6010*2],tot;
void add_edge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int deg[6010];
int dp[6010][2];
int p[6010];
void dfs(int u)
{
    dp[u][1]=p[u];
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        dfs(v);
        dp[u][0]+=max(dp[v][0], dp[v][1]);
        dp[u][1]+=dp[v][0];
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)
    {
        head[i]=-1;
        readi(p[i]);
    }
    head[0]=-1;
    int k,l;
    while(readi(k,l)!=EOF && k && l)
    {
        add_edge(l,k);
        deg[k]++;
    }
    int ans=0;
    rep(i,1,n)
    {
        if(deg[i]==0)
        {
            add_edge(0,i);
        }
    }
    dfs(0);
    printf("%d",dp[0][0]);
    return 0;
}