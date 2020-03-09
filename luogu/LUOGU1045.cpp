/**
* Number:luogu1045
* Title:麦森数
* Status:AC
* Tag:[大整数, 高精度, 快速幂]
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

const int MAXN=500;
void add(const int* a,const int* b,int* c)
{
    fill(c,c+MAXN,0);
    int carry=0;
    for(int i=0;i<MAXN;i++)
    {
        int t=a[i]+b[i]+carry;
        c[i]=t%10;
        carry=t/10;
    }
}
void mul(const int* a,const int* b,int* c)
{
    fill(c,c+MAXN,0);
    int sum=0;
    for(int i=0;i<MAXN;i++)
    {
        for(int j=0;j<=i;j++)
        {
            sum+=a[j]*b[i-j];
        }
        c[i]=sum%10;
        sum/=10;
    }
}
void qpow(int b,int* c)
{
    static int tmp[MAXN]={2};
    static int buf[MAXN];
    fill(c,c+MAXN,0);
    c[0]=1;
    for(;b;b>>=1)
    {
        if(b&1)
        {
            mul(tmp,c,buf);
            copy(buf,buf+MAXN,c);
        }
        mul(tmp,tmp,buf);
        copy(buf,buf+MAXN,tmp);
    }
}

int ans[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int p; readi(p);
    printf("%d\n",(int)ceil(p*log10(2)));
    qpow(p,ans);
    ans[0]-=1;
    for(int i=MAXN-1;i>=0;i--)
    {
        putchar(ans[i]|0x30);
        if(i%50==0)putchar('\n');
    }
    return 0;
}