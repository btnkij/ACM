/**
* Number:loj10155
* Title:「一本通 5.2 例 3」数字转换 
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
}edges[50010*2];
int head[50010],nxt[50010*2],tot;
void add_edge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int maxdep, id;
int dep;
void dfs(int u, int pre)
{
    if(maxdep<dep)
    {
        maxdep=dep;
        id=u;
    }
    for(int i=head[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(e.to==pre)continue;
        dep++;
        dfs(e.to, u);
        dep--;
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)head[i]=-1;
    rep(i,2,n)
    {
        int sum=1;
        for(int j=2;j*j<=i;j++)
        {
            if(i%j==0)
            {
                sum+=j;
                if(i/j>j)sum+=i/j;
            }
        }
        if(sum<i)
        {
            add_edge(sum,i);
            add_edge(i,sum);
        }
    }
    maxdep=dep=0;
    dfs(1,0);
    maxdep=dep=0;
    dfs(id, 0);
    printf("%d",maxdep);
    return 0;
}