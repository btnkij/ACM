/**
* Number:2214
* Title:迷宫
* Status:AC
* Tag:[dfs, 二分]
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

#define INF 2000000005
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

struct Edge
{
    int from,to,dis;
}edges[2000010];
int head[2000010],nxt[2000010],tot;
void addedge(int from,int to,int dis)
{
    edges[++tot]=(Edge){from,to,dis};
    nxt[tot]=head[from];
    head[from]=tot;
}
bool trace[2000010],sorted[2000010];
int mid;
bool dfs(int u)
{
    if(trace[u])return false;
    else if(sorted[u])return true;
    trace[u]=true;
    bool flag=true;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=edges[i].to;
        if(edges[i].dis<=mid || sorted[v])continue;
        else if(!dfs(v)){flag=false;break;}
    }
    trace[u]=false;
    return sorted[u]=flag;
}
int n,m; 
bool check()
{
    fill_n(sorted+1,n,false);
    rep(i,1,n)if(!dfs(i))return false;
    return true;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,m);
    repne(i,0,m)
    {
        int u,v,w; readi(u,v,w);
        addedge(u,v,w);
    }
    int lt=0,rt=2000000005;
    while(lt<rt)
    {
        mid=((ll)lt+rt)>>1;
        if(check())rt=mid;
        else lt=mid+1;
    }
    if(lt==INF)printf("Sleep forever!");
    else printf("%d",lt);
    return 0;
}