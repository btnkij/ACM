/**
* Number:uva1386
* Title:Cellular Automaton
* Status:AC
* Tag:[矩阵快速幂, 循环矩阵]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
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

struct Mat
{
    ll mat[510];
    Mat()
    {
        clr(mat,0);
    }
    inline ll& operator[](int i)
    {
        return mat[i];
    }
    inline const ll &operator[](int i)const
    {
        return mat[i];
    }
};
Mat mul(const Mat& lhs,const Mat& rhs,int n,int m)
{
    Mat ans;
    repne(i,0,n)
    {
        repne(j,0,n)
        {
            ans[i]=(ans[i]+lhs[j]*rhs[((n+i-j)%n+n)%n])%m;
        }
    }
    return ans;
}
Mat pow(const Mat& mat,int p,int n,int m)
{
    Mat tmp=mat,ans;
    ans[0]=1;
    for(;p;p>>=1)
    {
        if(p&1)ans=mul(ans,tmp,n,m);
        tmp=mul(tmp,tmp,n,m);
    }
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,d,k;
    while(readi(n,m,d,k)!=EOF)
    {
        Mat A,F;
        repne(i,0,n)scanf("%lld",&A[i]);
        rep(i,0,d)F[i]=F[((n-i)%n+n)%n]=1;
        F=pow(F,k,n,m);
        Mat B;
        repne(i,0,n)
        {
            repne(j,0,n)
            {
                B[i]=(B[i]+F[((j-i)%n+n)%n]*A[j])%m;
            }
        }
        repne(i,0,n)printf("%lld%c",B[i],i==(n-1)?'\n':' ');
    }
    return 0;
}