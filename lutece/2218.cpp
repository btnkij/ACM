/**
* Number:2218
* Title:变色龙
* Status:?
* Tag:[]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
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

const int MAXN=1e2+10;
const int MAXM=4e2+10;
struct Edge
{
    int from,to,color,nxt;
}edges[MAXM];
int head[MAXN],edge_id;
void addedge(int from,int to, int color)
{
    edges[edge_id]=(Edge){from,to,color,head[from]};
    head[from]=edge_id++;
}

struct Node
{
    int pos,color,cost;
    bool operator<(const Node& rhs)const
    {
        return cost>rhs.cost;
    }
};
set<int> color[MAXN];
int mindis[MAXN];
int n,m;
int dijkstra(int n)
{
    mset(mindis,INF);
    priority_queue<Node> P;
    P.push((Node){1,-1,0});
    while(!P.empty())
    {
        Node cur=P.top(); P.pop();
        if(cur.cost > mindis[cur.pos])continue;
        if(cur.pos==n)return cur.cost;
        if(cur.cost < mindis[cur.pos])
        {
            mindis[cur.pos]=cur.cost;
            color[cur.pos].clear();
        }
        color[cur.pos].insert(cur.color);

    }
    return -1;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,m);
    mset(head,-1);
    repne(i,0,m)
    {
        int u,v,c; readi(u,v,c);
        addedge(u,v,c); addedge(v,u,c);
    }
    int ans=dijkstra(n);
    printf("%d",ans);
    return 0;
}