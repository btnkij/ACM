/**
 * 
 * 矩阵
 * 
**/

#include <cstring>
#include <cassert>

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
                ans[i][j] = ans[i][j] + lhs[i][k] * rhs[k][j];
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