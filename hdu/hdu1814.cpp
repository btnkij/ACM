/**
* Number:hdu1814
* Title:Peaceful Commission
* Status:AC
* Tag:[2-sat, dfs]
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

const int MAXN=8010*2;
const int MAXM=20010*2;
struct Edge
{
    int from,to,nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

vector<int> trace;
bool mark[MAXN];
bool dfs(int u)
{
    if(mark[u])return true;
    if(mark[u^1])return false;
    mark[u]=true,mark[u^1]=false;
    trace.push_back(u);
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(!dfs(v))return false;
    }
    return true;
}
bool solve(int n)
{
    clr(mark,false);
    repne(i,0,n<<1)
    {
        if(mark[i] || mark[i^1])continue;
        trace.clear();
        if(dfs(i))continue;
        for(int j:trace)mark[j]=false;
        trace.clear();
        if(!dfs(i^1))return false;
    }
    return true;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m;
    while(readi(n,m)!=EOF)
    {
        clr(head,-1);
        edgeid=0;
        repne(i,0,m)
        {
            int a,b; readi(a,b);
            a--, b--;
            addedge(a,b^1);
            addedge(b,a^1);
        }
        if(!solve(n))puts("NIE");
        else
        {
            repne(i,0,n<<1)
            {
                if(mark[i])
                {
                    printf("%d\n",i+1);
                }
            }
        }
    }
    return 0;
}