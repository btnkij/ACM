/**
* Number:p3803
* Title:【模板】多项式乘法（FFT）
* Status:AC
* Tag:[fft]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <complex>
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

typedef Complex<double> C;
struct FFT
{
    int r[(1 << 21) + 10];
    void init(int logn)
    {
        int n = 1 << logn;
        logn--;
        for(int i = 0; i < n; i++)
            r[i] = (r[i >> 1] >> 1) | ((i & 1) << logn);
    }
    void operator()(C* poly, int n, int op)
    {
        for(int i = 0; i < n; i++)
            if(i < r[i])swap(poly[i], poly[r[i]]);
        for(int i = 1; i < n; i <<= 1)
        {
            C x = {cos(PI / i), op * sin(PI / i)};
            for(int j = 0; j < n; j += (i << 1))
            {
                C y = {1, 0};
                for(int k = 0; k < i; k++, y = x * y)
                {
                    C p = poly[j + k], q = y * poly[i + j + k];
                    poly[j + k] = p + q;
                    poly[i + j + k] = p - q;
                }
            }
        }
        if(op == -1)
            for(int i = 0; i <= n; i++)
                poly[i].real /= n;
    }
}fft;

C a[(1<<21)+10], b[(1<<21)+10];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep(i,0,n)scanf("%lf",&a[i].real);
    rep(i,0,m)scanf("%lf",&b[i].real);
    int len=1, logn=0;
    while(len<=n+m)
    {
        len<<=1;
        logn++;
    }
    fft.init(logn);
    fft(a,len,1);
    fft(b,len,1);
    rep(i,0,len)a[i]=a[i]*b[i];
    fft(a,len,-1);
    rep(i,0,n+m)
    {
        printf("%d ",(int)round(a[i].real));
    }
    return 0;
}