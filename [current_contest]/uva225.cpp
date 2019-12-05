/**
* Number:uva225
* Title:Golygons
* Status:AC
* Tag:[回溯, 搜索, dfs]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <string>
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

int n,m;
vector<pair<int,int> > block;
vector<string> path;
string trace;
set<pair<int,int> > vis;
const int dir[][3]={{1,0,'e'},{0,1,'n'},{0,-1,'s'},{-1,0,'w'}};
bool check(int x1,int y1,int x2,int y2)
{
    if(vis.count(make_pair(x2,y2)))return false;
    if(x1>x2)swap(x1,x2);
    if(y1>y2)swap(y1,y2);
    for(auto it:block)
    {
        if(x1<=it.first && it.first<=x2 && y1<=it.second && it.second<=y2)
        {
            return false;
        }
    }
    return true;
}
void dfs(int x,int y,int pre)
{
    int step=trace.length()+1;
    if(step>n)
    {
        if(x==0 && y==0)path.push_back(trace);
        return;
    }
    for(int i=0;i<4;i++)
    {
        if(i==pre || (i^3)==pre)continue;
        int nxtx=x+dir[i][0]*step,nxty=y+dir[i][1]*step;
        if(!check(x,y,nxtx,nxty))continue;
        if((step+1+n)*(n-step)/2<abs(nxtx)+abs(nxty))continue;
        vis.emplace(nxtx,nxty);
        trace.push_back(dir[i][2]);
        dfs(nxtx,nxty,i);
        vis.erase(make_pair(nxtx,nxty));
        trace.pop_back();
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        readi(n,m);
        block.clear();
        repne(i,0,m)
        {
            int x,y; readi(x,y);
            block.emplace_back(x,y);
        }
        path.clear();
        dfs(0,0,-1);
        // sort(path.begin(),path.end());
        for(auto s:path)printf("%s\n",s.c_str());
        printf("Found %d golygon(s).",path.size());
        printf("\n\n");
    }
    return 0;
}