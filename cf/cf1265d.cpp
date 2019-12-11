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

int ans[100100];
int a,b,c,d;
void dfs(int dep)
{

}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int a,b,c,d; readi(a,b,c,d);
    bool ok=true;
    int tot=0;
    while(a||b||c||d)
    {
        if(a)
        {
            if(a>b && !tot || tot && ans[tot-1]==1)
                ans[tot++]=0,a--;
        }
        if(b)
        {
            if(!tot && b>c || tot && ans[tot-1]==0 || tot && ans[tot-1]==2)
                ans[tot++]=1,b--;
        }
        if(c)
        {
            if(!tot && (c>d || c>b))ans[tot++]=2,c--;
            else if(tot)
            {
                
            }
        }
    }
    if(a>b)
    {
        if(a-b==1)ans[tot++]=0;
        else ok=false;
    }
    while(a && b)
    {
        ans[tot++]=1, ans[tot++]=0;
        a--, b--;
    }
    if(b)
    {
        if(b==1)ans[tot++]=1;
        else if(!c)ok=false;
    }
    if(c && (!tot || tot && ans[tot-1]==0))
    {
        if(b)ans[tot++]=1,b--;
        else ok=false;
    }
    while(b && c)
    {
        ans[tot++]=2, ans[tot++]=1;
        b--, c--;
    }
    if(b)ok=false;
    if(d && (!tot || tot && ans[tot-1]==1))
    {
        if(c)ans[tot++]=2,c--;
        else ok=false;
    }
    while(c && d)
    {
        ans[tot++]=3, ans[tot++]=2;
        c--, d--;
    }
    if(c)ok=false;
    if(d==1)ans[tot++]=2;
    else if(d)ok=false;
    if(ok)
    {
        puts("YES");
        repne(i,0,tot)printf("%d ",ans[i]);
    }
    else puts("NO");
    return 0;
}