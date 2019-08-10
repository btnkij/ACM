/**
* Number:p2766
* Title:最长不下降子序列问题
* Status:AC
* Tag:[dp, 网络流最大流]
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=1010;
const int MAXM=1000010;

struct Edge
{
    int from,to,cap,nxt;
}edges[MAXM];
int head[MAXN],edge_id;
void addedge(int from,int to,int cap)
{
    edges[edge_id]=(Edge){from,to,cap,head[from]};
    head[from]=edge_id++;
    edges[edge_id]=(Edge){to,from,0,head[to]};
    head[to]=edge_id++;
}

int src,dst;
int dep[MAXN];
bool bfs()
{
    mset(dep,0);
    queue<int> Q;
    Q.push(src);
    dep[src]=1;
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(dep[e.to] || e.cap<=0)continue;
            dep[e.to]=dep[u]+1;
            Q.push(e.to);
        }
    }
    return dep[dst]>0;
}
int cur[MAXN];
int dfs(int u,int flow)
{
    if(u==dst)return flow;
    for(int& i=cur[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(dep[u]+1!=dep[e.to] || e.cap<=0)continue;
        int f=dfs(e.to, min(flow, e.cap));
        if(f)
        {
            e.cap-=f;
            edges[i^1].cap+=f;
            return f;
        }
    }
    return 0;
}
int dinic()
{
    int ans=0;
    while(bfs())
    {
        memcpy(cur,head,sizeof(head));
        int f;
        while(f=dfs(src,INF))
        {
            ans+=f;
        }
    }
    return ans;
}

int arr[MAXN], dp[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);

    // 计算其最长不下降子序列的长度s
    int s=0;
    rep(i,1,n)
    {
        readi(arr[i]);
        int tmp=0;
        for(int j=i-1;j>=1;j--)
        {
            if(arr[i]>=arr[j])
            {
                tmp=max(tmp, dp[j]);
            }
        }
        dp[i]=tmp+1;
        s=max(s, dp[i]);
    }
    printf("%d\n",s);
    if(s==1)
    {
        printf("%d\n%d",n,n);
        return 0;
    }

    // 计算从给定的序列中最多可取出多少个长度为s的不下降子序列
    src=0, dst=1;
    mset(head,-1);
    rep(i,1,n)
    {
        if(dp[i]==s)addedge((i<<1)|1, dst, INF);
        if(dp[i]==1)addedge(src, i<<1, INF);
        addedge(i<<1, (i<<1)|1, 1);
        for(int j=i-1;j>=1;j--)
        {
            if(dp[i]==dp[j]+1 && arr[i]>=arr[j])
            {
                addedge((j<<1)|1, i<<1, 1);
            }
        }
    }
    int ans=dinic();
    printf("%d\n", ans);

    // 如果允许在取出的序列中多次使用x1和xn，则从给定序列中最多可取出多少个长度为s的不下降子序列
    addedge(1<<1, (1<<1)|1, INF);
    addedge(n<<1, (n<<1)|1, INF);
    ans+=dinic();
    printf("%d", ans);

    return 0;
}