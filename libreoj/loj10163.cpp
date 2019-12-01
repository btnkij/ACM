/**
* Number:loj10163
* Title:「一本通 5.3 例 1」Amount of Degrees
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

ll base[100],x,y;
int ans=0;
void dfs(ll sum,int pre,int dep)
{
    if(dep==0)
    {
        if(x<=sum && sum<=y)ans++;
        return;
    }
    dep--;
    for(int i=pre-1;i>=dep;i--)
    {
        ll nxt=sum+base[i];
        if(nxt+base[i]<x)return;
        if(nxt>y)continue;
        dfs(nxt,i,dep);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ll k,b; scanf("%lld %lld %lld %lld",&x,&y,&k,&b);
    base[0]=1;
    int n=1;
    for(;base[n-1]<=y;n++)base[n]=base[n-1]*b;
    dfs(0,n,k);
    printf("%d",ans);
    return 0;
}