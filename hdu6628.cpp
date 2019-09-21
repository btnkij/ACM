/**
* Number:hdu6628
* Title:permutation 1
* Status:AC
* Tag:[dfs]
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
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

bool vis[50];
int num[30],n,k;
bool dfs(int dep,int low,int high)
{
    if(dep==n)
    {
        if(--k)return false;
        repne(i,0,dep)printf("%d%c",num[i]-low+1,i+1==dep?'\n':' ');
        return true;
    }
    int lb=high-(n-1), ub=low+(n-1);
    for(int i=lb;i<=ub;i++)
    {
        if(vis[i])continue;
        vis[i]=true;
        num[dep]=i;
        if(dfs(dep+1,min(i,low),max(i,high)))return true;
        vis[i]=false;
    }
    return false;
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
        readi(n,k);
        clr(vis,false);
        num[0]=n, vis[n]=true;
        dfs(1,n,n);
    }
    return 0;
}