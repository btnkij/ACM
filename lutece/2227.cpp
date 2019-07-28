/**
* Number:2227
* Title:洁姐姐带我上分
* Status:AC
* Tag:[dijkstra]
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

int n,m,k;
int cp[20];
bool vis[1<<20];
int dis[1<<20];
int all;
bool check(int sta)
{
    if(sta&1)sta=~sta;
    repne(i,0,m)
    {
        if((sta&cp[i])==cp[i])
            return false;
    }
    return true;
}
int cnt(int sta)
{
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(sta&(1<<i))ans++;
    }
    return ans;
}
struct Node
{
    int sta, cost;
    bool operator<(const Node& rhs)const
    {
        return cost > rhs.cost;
    }
};
int dijkstra()
{
    priority_queue<Node> Q;
    Q.push((Node){0,0});
    while(!Q.empty())
    {
        Node cur=Q.top(); Q.pop();
        if(vis[cur.sta])continue;
        // printf("%X %d\n",cur.sta,cur.cost);
        if(cur.sta==all)return cur.cost;
        vis[cur.sta]=true;
        int s=cur.sta;
        if(s&1)s^=1;
        else s=(s^all)&(~1);
        bool flag=true;
        for(int i=s;flag;i=(i-1)&s)
        {
            if(!i)flag=false;
            int nxt=cur.sta^(i|1);
            if(vis[nxt])continue;
            int c=cnt(i);
            if(c>k)continue;
            if(!check(nxt))continue;
            Q.push((Node){nxt,cur.cost+c+1});
        }
    }
    return -1;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,m,k);
    k--;
    all=(1<<(n+1))-1;
    repne(i,0,m)
    {
        int a,b; readi(a,b);
        cp[i]=(1<<a)|(1<<b);
    }
    int ans=dijkstra();
    if(ans==-1)printf("mole");
    else printf("%d",ans);
    return 0;
}