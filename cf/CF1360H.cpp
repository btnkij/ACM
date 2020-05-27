/**
* Number:CF1360H
* Title:Binary Median
* Status:AC
* Tag:[二分]
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

char s[100];
ll num[100];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n,m; readi(n,m);
        for(int i=0;i<n;i++)
        {
            reads(s);
            ll t=0;
            for(int j=0;j<m;j++)t=(t<<1)|(s[j]&1);
            num[i]=t;
        }
        sort(num,num+n);
        ll k=((1LL<<m)-n-1)/2;
        ll lt=0,rt=(1LL<<m)-1;
        while(lt<rt)
        {
            ll mid=(lt+rt)>>1;
            int i=lower_bound(num,num+n,mid)-num;
            if(num[i]==mid)
            {
                if((mid-1)-i<k)lt=mid+1;
                else rt=mid-1;
            }
            else
            {
                if(mid-i<k)lt=mid+1;
                else rt=mid;
            }
        }
        ll ans=lt;
        for(int i=m-1;i>=0;i--)printf("%d",(ans>>i)&1);
        puts("");
    }
    return 0;
}