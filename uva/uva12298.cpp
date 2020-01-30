/**
* Number:uva12298
* Title:Super Poker II
* Status:WA
* Tag:[fft]
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

template<typename T>
struct Complex
{
    T real, img;
    friend Complex operator+(const Complex& lhs, const Complex& rhs)
    {
        return (Complex){lhs.real + rhs.real, lhs.img + rhs.img};
    }
    friend Complex operator-(const Complex& lhs, const Complex& rhs)
    {
        return (Complex){lhs.real - rhs.real, lhs.img - rhs.img};
    }
    friend Complex operator*(const Complex& lhs, const Complex& rhs)
    {
        return (Complex){
            lhs.real * rhs.real - lhs.img * rhs.img, 
            lhs.img * rhs.real + lhs.real * rhs.img};
    }
};

typedef Complex<long double> Cplx;
struct FFT
{
    int r[(1 << 21) + 10];
    void init(int logn)
    {
        int n = 1 << logn;
        logn--;
        r[0] = 0;
        for(int i = 0; i < n; i++)
            r[i] = (r[i >> 1] >> 1) | ((i & 1) << logn);
    }
    void operator()(Cplx* poly, int n, int op)
    {
        for(int i = 0; i < n; i++)
            if(i < r[i])std::swap(poly[i], poly[r[i]]);
        for(int i = 1; i < n; i <<= 1)
        {
            Cplx x = {cos(PI / i), op * sin(PI / i)};
            for(int j = 0; j < n; j += (i << 1))
            {
                Cplx y = {1, 0};
                for(int k = 0; k < i; k++, y = x * y)
                {
                    Cplx p = poly[j + k], q = y * poly[i + j + k];
                    poly[j + k] = p + q;
                    poly[i + j + k] = p - q;
                }
            }
        }
        if(op == -1)
            for(int i = 0; i < n; i++)
                poly[i].real /= n;
    }
}fft;

bool notprime[50010];
int prime[50010],tot;
void initPrime()
{
    tot=0;
    repne(i,2,50005)
    {
        if(!notprime[i])prime[tot++]=i;
        for(int j=0;j<tot && (ll)prime[j]*i<50005;j++)
        {
            notprime[prime[j]*i]=true;
            if(i%prime[j]==0)break;
        }
    }
}

Cplx S[1<<21],H[1<<21],C[1<<21],D[1<<21];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    initPrime();
    int a,b,c;
    bool first=true;
    while(readi(a,b,c)!=EOF && (a|b|c))
    {
        int len=1,logn=0;
        b++;
        for(;len<(b<<2);len<<=1,logn++);
        mset(fft.r,0);
        fft.init(logn);
        mset(S,0); mset(H,0); mset(C,0); mset(D,0);
        repne(i,2,b)
        {
            if(notprime[i])S[i].real=H[i].real=C[i].real=D[i].real=1;
        }
        while(c--)
        {
            int val;
            char type;
            scanf("%d%c",&val,&type);
            if(type=='S')S[val].real=0;
            else if(type=='H')H[val].real=0;
            else if(type=='C')C[val].real=0;
            else if(type=='D')D[val].real=0;
        }
        fft(S,len,1); fft(H,len,1); fft(C,len,1); fft(D,len,1);
        repne(i,0,len)S[i]=S[i]*H[i]*C[i]*D[i];
        fft(S,len,-1);
        if(!first)printf("\n\n");
        first=false;
        repne(i,a,b)
        {
            if(i>a)putchar('\n');
            printf("%lld",(ll)(S[i].real+0.5));
        }
    }
    return 0;
}