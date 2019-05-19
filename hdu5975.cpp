/**
* Number:hdu5975
* Title:Aninteresting game
* Status:AC
* Tag:[规律]
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

ll query(ll n)
{
    ll ans=0;
    for(ll b=1,k=1;b<=n;b<<=1,k++)
        ans+=((n+b)>>k)<<(k-1);
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ll n, q;
    while(scanf("%lld %lld",&n,&q)!=EOF)
    {
        while(q--)
        {
            int op; readi(op);
            if(op==1)
            {
                ll l,r; scanf("%lld %lld",&l,&r);
                printf("%lld\n",query(r)-query(l-1));
            }
            else if(op==2)
            {
                ll x; scanf("%lld",&x);
                int ans=0;
                while(x<=n)
                {
                    ans++;
                    x+=x&-x;
                }
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}