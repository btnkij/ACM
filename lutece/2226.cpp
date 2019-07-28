/**
* Number:2226
* Title:洁姐姐带找工作
* Status:AC
* Tag:[差分约束]
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

const int MAXN = 1010;
const int MAXM = 5010*2;
struct Edge
{
    int from, to, dis, nxt;
}edges[MAXM];
int head[MAXN], edge_id;
void addedge(int from, int to, int dis)
{
    edges[edge_id] = (Edge){from, to, dis, head[from]};
    head[from] = edge_id++;
}

int n,m;
int dis[1010],cnt[1010];
bool vis[1010];
bool spfa()
{
    queue<int> Q;
    rep(i,1,n)
    {
        dis[i]=cnt[i]=1;
        vis[i]=true;
        Q.push(i);
    }
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        vis[u]=false;
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(dis[u]+e.dis>dis[e.to])
            {
                dis[e.to]=dis[u]+e.dis;
                if(!vis[e.to])
                {
                    cnt[e.to]=max(cnt[e.to],cnt[u])+1;
                    if(cnt[e.to]>n)return false;
                    Q.push(e.to);
                    vis[e.to]=true;
                }
            }
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
    readi(n,m);
    fill(head, head+n+1, -1);
    repne(i,0,m)
    {
        int r,a,b; readi(r,a,b);
        if(r==1)addedge(b,a,1);
        else if(r==2)addedge(a,b,1);
        else if(r==3){addedge(a,b,0);addedge(b,a,0);}
    }
    if(spfa())
    {
        int sum=0;
        rep(i,1,n)sum+=dis[i];
        printf("%d",sum);
    }
    else printf("-1");
    return 0;
}