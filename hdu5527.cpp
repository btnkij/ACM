/**
* Number:hdu5527
* Title:Too Rich
* Status:AC
* Tag:[贪心, dfs]
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

#define INF 0x3f3f3f3f3f3f3f3f
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

ll c[]={0,1,5,10,20,50,100,200,500,1000,2000};
ll num[12];
ll dfs(ll tot, int k)
{
    if(tot==0)return 0;
    if(k==0)return INF;
    if(num[k]==0)
        return dfs(tot,k-1);
    ll x=min(num[k], tot/c[k]);
    ll ans=x+dfs(tot-x*c[k], k-1);
    if(x>=1)ans=min(ans, x-1+dfs(tot-(x-1)*c[k], k-1));
    return ans;
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
        ll p; scanf("%lld",&p);
        ll tot=0,n=0;
        rep(i,1,10)
        {
            scanf("%lld",num+i);
            tot+=c[i]*num[i];
            n+=num[i];
        }
        tot=tot-p;
        if(tot<0)
        {
            printf("-1\n");
            continue;
        }
        ll ans=dfs(tot,10);
        if(ans>n)printf("-1\n");
        else printf("%lld\n",n-ans);
    }
    return 0;
}