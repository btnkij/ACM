/**
* Number:uva1663
* Title:Purifying Machine
* Status:AC
* Tag:[二分图, 最大匹配, hungary]
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

struct Edge
{
    int from,to,nxt;
}edges[4000010];
int head[4010],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int match[4010];
bool vis[4010];
int dfs(int u)
{
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(vis[v])continue;
        vis[v]=true;
        if(!match[v] || dfs(match[v]))
        {
            match[v]=u;
            return 1;
        }
    }
    return 0;
}
int maxmatch(int nx)
{
    int ans=0;
    clr(match,0);
    rep(i,1,nx)
    {
        clr(vis,false);
        ans+=dfs(i);
    }
    return ans;
}

char s[16];
vector<int> num;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m;
    while(readi(n,m)!=EOF && (n|m))
    {
        num.clear();
        num.push_back(0);
        rep(i,1,m)
        {
            reads(s);
            int t=0,pos=-1;
            repne(i,0,n)
            {
                if(s[i]=='*')pos=i;
                else t|=(s[i]&1)<<i;
            }
            num.push_back(t);
            if(pos!=-1)num.push_back(t|(1<<pos));
        }
        clr(head,-1); edgeid=0;
        sort(num.begin()+1,num.end());
        num.erase(unique(num.begin()+1,num.end()),num.end());
        m=num.size()-1;
        rep2(i,1,m,j,1,m)
        {
            if(i==j)continue;
            int t=num[i]^num[j];
            if((t&(t-1))==0)addedge(i,j);
        }
        printf("%d\n",m-maxmatch(m)/2);
    }
    return 0;
}