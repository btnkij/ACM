/**
* Number:uva11542
* Title:Square
* Status:AC
* Tag:[高斯消元, 异或方程组]
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

int mat[510][110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        clr(mat,0);
        rep(i,1,n)
        {
            ll t; scanf("%lld",&t);
            for(int j=2;j<=500;j++)
            {
                while(t%j==0)
                {
                    t/=j;
                    mat[j][i]^=1;
                }
            }
        }
        int nequ=0;
        rep(i,1,n)
        {
            int k=nequ+1;
            while(k<=500 && mat[k][i]!=1)k++;
            if(k>500)continue;
            nequ++;
            if(k!=nequ)rep(j,1,n)swap(mat[nequ][j],mat[k][j]);
            rep(r,1,500)
            {
                if(mat[r][i]!=1 || r==nequ)continue;
                rep(c,1,n)mat[r][c]^=mat[nequ][c];
            }
        }
        int nvar=n-nequ;
        printf("%lld\n",(1LL<<nvar)-1);
    }
    return 0;
}