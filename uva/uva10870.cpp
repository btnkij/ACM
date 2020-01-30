/**
* Number:uva10870
* Title:Recurrences
* Status:AC
* Tag:[矩阵快速幂]
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

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

template <typename T>
struct Mat
{
    int nrow, ncol;
    T buf[400];
    Mat(int r, int c) : nrow(r), ncol(c)
    {
        memset(buf, 0, sizeof(buf));
    }
    inline T *operator[](int r)
    {
        return buf + r * ncol;
    }
    inline const T *operator[](int r) const
    {
        return buf + r * ncol;
    }
};

int mod;
template <typename T>
Mat<T> operator*(const Mat<T> &lhs, const Mat<T> &rhs)
{
    assert(lhs.ncol == rhs.nrow);
    Mat<T> ans(lhs.nrow, rhs.ncol);
    for (int i = 0; i < lhs.nrow; i++)
    {
        for (int j = 0; j < rhs.ncol; j++)
        {
            for (int k = 0; k < lhs.ncol; k++)
            {
                ans[i][j] = (ans[i][j] + lhs[i][k] * rhs[k][j] % mod) % mod;
            }
        }
    }
    return ans;
}
template <typename T>
Mat<T> pow(const Mat<T> &mat, int p)
{
    assert(mat.nrow == mat.ncol);
    Mat<T> tmp = mat, ans(mat.nrow, mat.nrow);
    for (int i = 0; i < mat.nrow; i++)
        ans[i][i] = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            ans = ans * tmp;
        tmp = tmp * tmp;
    }
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int d, n;
    while (readi(d, n, mod) != EOF && (d | n | mod))
    {
        Mat<int> A(d, d);
        repne(i, 1, d) A[i - 1][i] = 1;
        for (int i = d - 1; i >= 0; i--)
        {
            scanf("%d", &A[d - 1][i]);
            A[d - 1][i] %= mod;
        }
        Mat<int> F(d, 1);
        repne(i, 0, d)
        {
            scanf("%d", &F[i][0]);
            F[i][0] %= mod;
        }
        F = pow(A, n - 1) * F;
        printf("%d\n", F[0][0]);
    }
    return 0;
}