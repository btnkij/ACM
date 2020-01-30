/**
* Number:uva725
* Title:Division
* Status:AC
* Tag:[枚举, 暴力]
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

bool check(int a,int b)
{
    bool vis[10];
    clr(vis,false);
    for(int i=0;i<5;i++)
    {
        int x=a%10;
        a/=10;
        if(vis[x])return false;
        vis[x]=true;
    }
    for(int i=0;i<5;i++)
    {
        int x=b%10;
        b/=10;
        if(vis[x])return false;
        vis[x]=true;
    }
    return true;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    bool first=true;
    while (readi(n)!=EOF && n)
    {
        if(!first)puts("");
        first=false;
        vector<int> ans;
        for(int a=01234;a*n<100000;a++)
        {
            int b=a*n;
            if(check(a,b))ans.push_back(a);
        }
        if(ans.size()==0)
        {
            printf("There are no solutions for %d.\n",n);
            continue;
        }
        for(int a:ans)
        {
            printf("%05d / %05d = %d\n",a*n,a,n);
        }
    }
    return 0;
}