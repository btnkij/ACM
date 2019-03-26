/**
* Number:loj10132
* Title:「一本通 4.4 例 3」异象石
* Status:AC
* Tag:[lca, dfs序, set]
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

inline int readu()
{
    int num = 0;
    char ch;
    do{ ch = getchar(); }while(ch < '0' || ch > '9');
    do{ num = (num << 3) + (num << 1) + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    return num;
}

struct Edge
{
    int from,to;
    ll dis;
}edges[400010];
int head[200010],nxt[200010],tot;
void add_edge(int from,int to, ll dis)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.dis=dis;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int fa[200010][20];
int tin[200010], tout[200010], timer;
int pos[400010];
ll dis[200010];
void dfs(int u, int pre)
{
    tin[u]=timer++;
    pos[tin[u]]=u;
    fa[u][0]=pre;
    for(int i=1;i<17;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(e.to==pre)continue;
        dis[e.to]=dis[u]+e.dis;
        dfs(e.to, u);
    }
    tout[u]=timer++;
}
bool isAncestor(int fa,int x)
{
    return !fa || tin[fa]<=tin[x] && tout[x]<=tout[fa];
}
int lca(int x,int y)
{
    if(isAncestor(x,y))return x;
    if(isAncestor(y,x))return y;
    for(int i=16;i>=0;i--)
        if(!isAncestor(fa[x][i],y))
            x=fa[x][i];
    return fa[x][0];
}
ll getDis(int x,int y)
{
    return dis[x]+dis[y]-(dis[lca(x,y)]<<1);
}

set<int> S;
set<int>::iterator getLeft(set<int>::iterator it)
{
    it++;
    if(it==S.end())it=S.begin();
    return it;
}
set<int>::iterator getRight(set<int>::iterator it)
{
    if(it==S.begin())it=S.end();
    it--;
    return it;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n=readu();
    rep(i,1,n)head[i]=-1;
    repne(i,1,n)
    {
        int u,v,w; readi(u,v,w);
        add_edge(u,v,w); add_edge(v,u,w);
    }
    dfs(1,0);
    int m; readi(m);
    ll ans=0;
    while(m--)
    {
        char op[4]; reads(op);
        if(op[0]=='+')
        {
            int x; readi(x);
            S.insert(tin[x]);
            if(S.size()==1)continue;
            set<int>::iterator it=S.find(tin[x]);
            set<int>::iterator lt=getLeft(it), rt=getRight(it);
            ans+=getDis(pos[*lt],x)+getDis(x,pos[*rt])-getDis(pos[*lt],pos[*rt]);
        }
        else if(op[0]=='-')
        {
            int x; readi(x);
            set<int>::iterator it=S.find(tin[x]);
            set<int>::iterator lt=getLeft(it), rt=getRight(it);
            S.erase(it);
            ans-=getDis(pos[*lt],x)+getDis(x,pos[*rt])-getDis(pos[*lt],pos[*rt]);
        }
        else if(op[0]=='?')
        {
            printf("%lld\n",ans>>1);
        }
    }
    return 0;
}