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

ll arr[200010];
bool check(ll mid,int n,int k)
{
    ll sum=0, cnt=0;
    repne(i,0,n)
    {
        if(arr[i]>mid)return false;
        if(sum+arr[i]>mid)
        {
            cnt++;
            sum=arr[i];
        }
    }
    if(sum)cnt++;
    return cnt>=k;
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
        int n,k; readi(n,k);
        ll lt=(ll)(2e14)+10, rt=(ll)(-2e14)-10;
        repne(i,0,n)
        {
            scanf("%lld",arr+i);
            lt=min(lt,arr[i]);
            rt=max(rt,arr[i]);
        }
        while(lt<rt)
        {
            ll mid=(lt+rt)>>1;
            if(check(mid,n,k))rt=mid;
            else lt=mid+1;
        }
        printf("%lld\n",lt);
    }
    return 0;
}