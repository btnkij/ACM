/**
* Number:CF1361B
* Title:Johnny and Grandmaster
* Status:?
* Tag:[快速幂]
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

constexpr int MOD=1e9+7;
ll qpow(ll p,int k)
{
    ll tmp=p, ans=1;
    while(k)
    {
        if(k&1)ans=(ans*tmp)%MOD;
        tmp=(tmp*tmp)%MOD;
        k>>=1;
    }
    return ans;
}

int arr[1000010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin>>T;
    while(T--)
    {
        int n;
        ll p;
        cin>>n>>p;
        for(int i=0;i<n;i++)cin>>arr[i];
        sort(arr,arr+n);
        ll ans=0;
        for(int i=n-1;i>=0;i--)
        {
            ll x=qpow(p,arr[i]);
            if(ans>0)ans=(ans+x)%MOD;
            else ans=((ans-x)%MOD+MOD)%MOD;
        }
        cout<<ans<<"\n";
    }
    return 0;
}