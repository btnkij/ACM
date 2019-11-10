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

const ll MOD=2147493647;
struct Mat
{
    int nrow,ncol;
    ll buf[100];
    Mat(int r,int c):nrow(r),ncol(c)
    {
        memset(buf,0,sizeof(buf));
    }
    ll* operator[](int r)
    {
        return buf+r*ncol;
    }
    const ll* operator[](int r)const
    {
        return buf+r*ncol;
    }
};
Mat operator*(const Mat& lhs, const Mat& rhs)
{
    Mat ans(lhs.nrow,rhs.ncol);
    for(int i=0;i<ans.nrow;i++)
    {
        for(int j=0;j<ans.ncol;j++)
        {
            for(int k=0;k<lhs.ncol;k++)
            {
                ans[i][j]=(ans[i][j]+lhs[i][k]*rhs[k][j])%MOD;
            }
        }
    }
    return ans;
}
Mat qpow(const Mat& mat, int p)
{
    Mat ans(mat.nrow,mat.ncol);
    for(int i=0;i<ans.nrow;i++)ans[i][i]=1;
    Mat tmp=mat;
    while(p)
    {
        if(p&1)ans=ans*tmp;
        tmp=tmp*tmp;
        p>>=1;
    }
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    Mat A(7,7);
    A[0][0]=1, A[0][1]=2, A[0][2]=1, A[0][3]=4, A[0][4]=6, A[0][5]=4, A[0][6]=1;
    A[1][0]=1, A[1][1]=0, A[1][2]=0, A[1][3]=0, A[1][4]=0, A[1][5]=0, A[1][6]=0;
    A[2][0]=0, A[2][1]=0, A[2][2]=1, A[2][3]=4, A[2][4]=6, A[2][5]=4, A[2][6]=1;
    A[3][0]=0, A[3][1]=0, A[3][2]=0, A[3][3]=1, A[3][4]=3, A[3][5]=3, A[3][6]=1;
    A[4][0]=0, A[4][1]=0, A[4][2]=0, A[4][3]=0, A[4][4]=1, A[4][5]=2, A[4][6]=1;
    A[5][0]=0, A[5][1]=0, A[5][2]=0, A[5][3]=0, A[5][4]=0, A[5][5]=1, A[5][6]=1;
    A[6][0]=0, A[6][1]=0, A[6][2]=0, A[6][3]=0, A[6][4]=0, A[6][5]=0, A[6][6]=1;
    int T; readi(T);
    while(T--)
    {
        int n,a,b; readi(n,a,b);
        if(n==1)printf("%lld\n",(ll)a%MOD);
        if(n==2)printf("%lld\n",(ll)b%MOD);
        else
        {
            Mat X(7,1);
            X[0][0]=b, X[1][0]=a, X[2][0]=16, X[3][0]=8, X[4][0]=4, X[5][0]=2, X[6][0]=1;
            Mat Y=qpow(A,n-2)*X;
            printf("%lld\n",Y[0][0]);
        }
    }
    return 0;
}