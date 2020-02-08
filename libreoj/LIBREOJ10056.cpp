/**
* Number:loj10056
* Title:「一本通 2.3 练习 5」The XOR-longest Path 
* Status:AC
* Tag:[trie]
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

struct Node
{
    int to[2];
}nodes[100010*32];
int tot;
int find(int s)
{
    int p=0;
    int ans=0;
    for(int i=30;i>=0;i--)
    {
        int b=(s>>i)&1;
        if(nodes[p].to[b^1])b^=1;
        ans|=(b<<i)^(s&(1<<i));
        p=nodes[p].to[b];
    }
    return ans;
}
void insert(int s)
{
    int p=0;
    for(int i=30;i>=0;i--)
    {
        int b=(s>>i)&1;
        if(!nodes[p].to[b])
        {
            nodes[p].to[b]=tot++;
        }
        p=nodes[p].to[b];
    }
}

struct Edge
{
    int from, to, weight;
} edges[200010];
int head[100010], nxt[200010], tot1;
void add_edge(int from, int to, int weight)
{
    Edge &e = edges[tot1];
    e.from = from, e.to = to, e.weight = weight;
    nxt[tot1] = head[from];
    head[from] = tot1++;
}

int num[100010];
void dfs(int u, int pre, int sum)
{
    num[u]=sum;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs(v, u, sum^edges[i].weight);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    tot=1;
    int n; readi(n);
    rep(i,1,n)head[i]=-1;
    repne(i,1,n)
    {
        int u,v,w; readi(u,v,w);
        add_edge(u,v,w); add_edge(v,u,w);
    }
    dfs(1,0,0);
    insert(num[1]);
    int ans=0;
    rep(i,2,n)
    {
        ans=max(ans, find(num[i]));
        insert(num[i]);
    }
    printf("%d", ans);
    return 0;
}