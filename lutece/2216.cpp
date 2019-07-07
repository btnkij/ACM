/**
* Number:2216
* Title:oydy的征途II
* Status:AC
* Tag:[有向图欧拉路径]
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

priority_queue<int,vector<int>,greater<int> > Q[1000010];
int indeg[1000010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    repne(i,0,m)
    {
        int u,v; readi(u,v);
        indeg[v]++;
        Q[u].push(v);
    }
    int src=0,dst=0;
    bool ok=true;
    rep(i,1,n)
    {
        if(indeg[i]==Q[i].size())continue;
        else if(indeg[i]==Q[i].size()+1 && !dst)dst=i;
        else if(indeg[i]+1==Q[i].size() && !src)src=i;
        else{ok=false; break;}
    }
    if((bool)src^(bool)dst)ok=false;
    if(ok)
    {
        if(!src)do{src++;}while(Q[src].empty());
        vector<int> path;
        stack<int> trace;
        while(true)
        {
            if(Q[src].empty())
            {
                path.push_back(src);
                if(trace.empty())break;
                src=trace.top();
                trace.pop();
                continue;
            }
            int to=Q[src].top();
            Q[src].pop();
            trace.push(src);
            src=to;
        }
        for(auto it=path.rbegin();it!=path.rend();it++)
        {
            printf("%d ",*it);
        }
    }
    else
    {
        printf("What a shame!");
    }
    return 0;
}