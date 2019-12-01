/**
* Number:loj10099
* Title:「一本通 3.6 例 2」矿场搭建
* Status:AC
* Tag:[tarjan, 割点]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
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

const int MAXN=1010;

struct Edge
{
    int from,to,nxt;
}edges[MAXN];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int dfsid,dfn[MAXN],low[MAXN];
int grpid;
vector<int> trace,grp[MAXN];
bool cut[MAXN];
void tarjan(int u,int pre)
{
    dfn[u]=low[u]=++dfsid;
    trace.push_back(u);
    int son=0;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre)continue;
        if(!dfn[v])
        {
            son++;
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u])
            {
                cut[u]=true;
                grp[++grpid].clear();
                while(trace.back()!=u)
                {
                    grp[grpid].push_back(trace.back());
                    trace.pop_back();
                }
                grp[grpid].push_back(u);
            }
        }
        else low[u]=min(low[v],low[u]);
    }
    if(pre==0 && son<2)cut[u]=false;
}

unordered_map<int,int> id;
vector<pair<int,int> > link;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,kase=1;
    while(readi(n)!=EOF && n)
    {
        link.clear();
        id.clear();
        repne(i,0,n)
        {
            int u,v; readi(u,v);
            link.emplace_back(u,v);
            if(!id.count(u))id.insert(make_pair(u,id.size()+1));
            if(!id.count(v))id.insert(make_pair(v,id.size()+1));
        }
        // for(auto it:id)
        // {
        //     printf("# %d -> %d\n",it.first,it.second);
        // }
        clr(head,-1); edgeid=0;
        for(auto it:link)
        {
            addedge(id[it.first],id[it.second]);
            addedge(id[it.second],id[it.first]);
        }
        clr(dfn,0); dfsid=grpid=0;
        clr(cut,false);
        rep(i,1,id.size())if(!dfn[i])tarjan(i,0);
        ll ans1=0,ans2=1;
        if(grpid==1)
        {
            ans1=2, ans2=grp[1].size()*(grp[1].size()-1)/2;
        }
        else rep(i,1,grpid)
        {
            // printf("# ");
            // for(int it:grp[i])printf("%d ",it);
            // printf("\n");
            int cnt=count_if(grp[i].begin(),grp[i].end(),[](int u){return cut[u];});
            if(cnt==1)ans1++,ans2*=grp[i].size()-1;
        }
        printf("Case %d: %lld %lld\n",kase++,ans1,ans2);
    }
    return 0;
}