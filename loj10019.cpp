/**
* Number:loj10019
* Title:「一本通 1.3 例 2」生日蛋糕
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
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int ans;
void dfs(int n,int m,int S,int r,int h)
{
    if(m==0)
    {
        if(n==0 && S<ans)ans=S;
        return;
    }
    if(n>m*r*r*h || n<=0)return;
    for(int i=r;i>=m;i--)
    {
        for(int j=h;j>=m;j--)
        {
            int nxtS=S+2*i*j;
            if(nxtS>=ans)continue;
            dfs(n-i*i*j, m-1, nxtS, i-1, j-1);
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    ans=INF;
    for(int i=100;i>=m;i--)
    {
        for(int j=1000;j>=m;j--)
        {
            dfs(n-i*i*j, m-1, i*i+2*i*j, i-1, j-1);
        }
    }
    printf("%d",ans);
    return 0;
}