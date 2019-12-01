/**
* Number:loj10081
* Title:「一本通 3.2 练习 7」道路和航线 
* Status:AC
* Tag:[spfa]
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

inline int read()
{
    register int num = 0;
    register char ch;
    register bool sign = false;
    do
    {
        ch = getchar();
        if(ch == '-')sign = true;
    }while(ch < '0' || ch > '9');
    do{ num = (num << 3) + (num << 1) + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    if(sign)num = -num;
    return num;
}

struct Edge
{
    int from, to, dis;
}edges[200010];
int head[30010], nxt[200010], tot;
void addEdge(int from, int to, int dis)
{
    Edge& e=edges[++tot];
    e.from=from, e.to=to, e.dis=dis;
    nxt[tot]=head[from];
    head[from]=tot;
}

int dis[30010];
bool vis[30010];
void spfa(int src)
{
    mset(dis, INF);
    dis[src]=0;
    deque<int> Q;
    Q.push_back(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop_front();
        vis[u]=false;
        for(int i=head[u]; i; i=nxt[i])
        {
            int v=edges[i].to, w=edges[i].dis;
            if(dis[u]+w < dis[v])
            {
                dis[v]=dis[u]+w;
                if(vis[v])continue;
                vis[v]=true;
                if(!Q.empty() && dis[v]<dis[Q.front()])Q.push_front(v);
                else Q.push_back(v);
            }
        }
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int t,r,p,s; readi(t,r,p,s);
    while(r--)
    {
        int a=read(), b=read(), c=read();
        addEdge(a,b,c); addEdge(b,a,c);
    }
    while(p--)
    {
        int a=read(), b=read(), c=read();
        addEdge(a,b,c);
    }
    spfa(s);
    rep(i,1,t)
    {
        if(dis[i]==INF)printf("NO PATH\n");
        else printf("%d\n", dis[i]);
    }
    return 0;
}