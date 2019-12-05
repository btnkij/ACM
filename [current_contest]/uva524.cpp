/**
* Number:uva524
* Title:Prime Ring Problem
* Status:AC
* Tag:[dfs, 回溯, 质数]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
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

bool prime[40];
vector<int> adj[20];
bool vis[20];
vector<int> trace;
int n;
void dfs()
{
    if(trace.size()==n)
    {
        if(prime[trace.front()+trace.back()])
        {
            repne(i,0,trace.size())
                printf("%d%c",trace[i],i==trace.size()-1?'\n':' ');
        }
        return;
    }
    int pre=trace.back();
    for(int i:adj[pre])
    {
        if(!vis[i])
        {
            vis[i]=true;
            trace.push_back(i);
            dfs();
            vis[i]=false;
            trace.pop_back();
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int kase=1;
    trace.push_back(1);
    vis[1]=true;
    repne(i,2,40)
    {
        bool flag=true;
        repne(j,2,i)
        {
            if(i%j==0)
            {
                flag=false;
                break;
            }
        }
        prime[i]=flag;
    }
    while(readi(n)!=EOF)
    {
        rep(i,1,n)
        {
            adj[i].clear();
            rep(j,1,n)
            {
                if(i==j)continue;
                if(prime[i+j])adj[i].push_back(j);
            }
        }
        if(kase>1)puts("");
        printf("Case %d:\n",kase++);
        dfs();
    }
    return 0;
}