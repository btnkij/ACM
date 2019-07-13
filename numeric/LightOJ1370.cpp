/**
* Number:LightOJ1370
* Title:Bi-shoe and Phi-shoe
* Status:AC
* Tag:[数论, 欧拉函数]
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 1000010;
int phi[MAXN];
void init_phi()
{
    phi[1] = 1;
    for(int i = 2; i < MAXN; i++)
    {
        if(phi[i])continue;
        for(int j = i; j < MAXN; j += i)
        {
            if(!phi[j])phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
    }
}

int a[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    init_phi();
    int pre=1;
    repne(i,2,MAXN)
    {
        for(;pre<=phi[i];++pre)
        {
            a[pre]=i;
        }
    }
    int T; readi(T);
    rep(kase,1,T)
    {
        int n; readi(n);
        ll ans=0;
        repne(i,0,n)
        {
            int t; readi(t);
            ans+=a[t];
        }
        printf("Case %d: %lld Xukha\n",kase,ans);
    }
    return 0;
}