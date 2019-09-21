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

ll arr[500010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,k;
    while(readi(n,k)!=EOF)
    {
        ll tot=0;
        ll mmin=INF,mmax=-INF;
        repne(i,0,n)
        {
            scanf("%lld",arr+i);
            tot+=arr[i];
            mmin=min(mmin,arr[i]), mmax=max(mmax,arr[i]);
        }
        int lt=mmin,rt=mmax,mid;
        while(lt<rt)
        {
            mid=(lt+rt)>>1;
            ll sum=0;
            repne(i,0,n)
            {
                if(arr[i]<=mid)
                {
                    sum+=mid-arr[i]+1;
                }
            }
            sum--;
            if(sum<k)lt=mid+1;
            else rt=mid;
        }
        int lb=lt;
        lt=mmin,rt=mmax;
        while(lt<rt)
        {
            mid=(lt+rt+1)>>1;
            ll sum=0;
            repne(i,0,n)
            {
                if(arr[i]>=mid)
                {
                    sum+=arr[i]-mid+1;
                }
            }
            sum--;
            if(sum>=k)lt=mid;
            else rt=mid-1;
        }
        int rb=lt;
        if(lb<=rb)printf("%d\n",rb-lb);
        else printf("%d\n",(int)(tot%n!=0));
    }
    return 0;
}