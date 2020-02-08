/**
* Number:loj10082
* Title:「一本通 3.3 例 1」Word Rings
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

struct Edge
{
    int from, to, dis;
}edges[1000010];
int head[100010], nxt[1000010], tot;
void addEdge(int from, int to, int dis)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.dis=dis;
    nxt[tot]=head[from];
    head[from]=tot++;
}

double mid;
bool vis[100010];
double dis[100010];
bool spfa(int u)
{
    vis[u]=true;
    bool ans=false;
    for(int i=head[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(dis[u]+e.dis-mid>dis[e.to])
        {
            dis[e.to]=dis[u]+e.dis-mid;
            if(vis[e.to] || spfa(e.to))
            {
                ans=true;
                break;
            }
        }
    }
    vis[u]=false;
    return ans;
}

int n;
bool check()
{
    fill(dis, dis+n+1, 0);
    repne(i,0,26*26)
    {
        if(spfa(i))return true;
    }
    return false;
}

int adj[900][900];
char s[1010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(readi(n)!=EOF && n)
    {
        mset(head, -1);
        tot=0;
        mset(adj,0);
        repne(i,0,n)
        {
            reads(s);
            int len=strlen(s);
            int pref=(s[0]-'a')*26+(s[1]-'a');
            int suff=(s[len-2]-'a')*26+(s[len-1]-'a');
            adj[pref][suff]=max(adj[pref][suff], len);
        }
        repne2(i,0,26*26,j,0,26*26)
        {
            if(adj[i][j])
            {
                addEdge(i,j,adj[i][j]);
            }
        }
        double lt=0, rt=1010;
        while(rt-lt>1e-4)
        {   
            mid=(lt+rt)/2;
            if(check())lt=mid;
            else rt=mid;
        }
        mid=lt;
        if(check())printf("%lf\n", lt);
        else printf("No solution\n");
    }
    return 0;
}