#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <set>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=2e5+10;
struct Edge
{
    int from,to,nxt;
}edges[MAXN*2];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int bfn[MAXN];
bool vis[MAXN];
set<int> son;
bool bfs(int n)
{
    if(bfn[0]!=1)return false;
    queue<int> Q; Q.push(1);
    vis[1]=true;
    int p=1;
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        son.clear();
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            int v=edges[i].to;
            if(vis[v])continue;
            son.insert(v);
        }
        while(!son.empty())
        {
            if(son.count(bfn[p]))
            {
                vis[bfn[p]]=true;
                Q.push(bfn[p]);
                son.erase(bfn[p]);
                p++;
            }
            else return false;
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
    int n; readi(n);
    clr(head,-1);
    repne(i,1,n)
    {
        int u,v; readi(u,v);
        addedge(u,v); addedge(v,u);
    }
    repne(i,0,n)readi(bfn[i]);
    if(bfs(n))puts("Yes");
    else puts("No");
    return 0;
}