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

int prime[1000100], *tailp;
bool is_nonprime[1000100];
void init_prime(int n)
{
    tailp = prime;
    is_nonprime[0] = is_nonprime[1] = true;
    for(int i = 2; i <= n; i++)
    {
        if(!is_nonprime[i])
            *(tailp++) = i;
        for(int* iter = prime; iter != tailp; iter++)
        {
            int t = i * (*iter);
            if(t > n)break;
            is_nonprime[t] = true;
            if(i % *iter == 0)break;
        }
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    init_prime(1000010);
    int T; readi(T);
    while(T--)
    {
        ll n; scanf("%lld",&n);
        int ans=INF;
        bool flag=false;
        ll q=(ll)sqrt(n+0.5);
        if(!flag && q*q==n && ans>2)
        {
            ans=2;
            flag=true;
        }
        int tot=tailp-prime;
        ll tmp=n;
        for(int i=0;i<tot;i++)
        {
            if(prime[i]>tmp || n%prime[i]!=0)continue;
            flag=true;
            int cnt=0;
            while(tmp%prime[i]==0)
            {
                tmp/=prime[i];
                cnt++;
            }
            ans=min(ans,cnt);
            if(ans==1)break;
        }
        printf("%d\n",flag?ans:1);
    }
    return 0;
}