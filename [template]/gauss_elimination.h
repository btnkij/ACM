/**
 * 
 * 高斯消元
 * 
**/

#include <cmath>
#include <algorithm>

const int MAXN = 104;
const double eps = 1e-15;
struct gauss_elimination
{
    double* mat[MAXN];
    // 保证系数矩阵为方阵，化为行最简矩阵
    int operator()(double arr[][MAXN], int nequ) // 系数矩阵，行数
    {
        for(int i = 0; i < nequ; i++)
            mat[i] = arr[i];
        int nvar = 0;
        for(int c = 0; c < nequ; c++)
        {
            int k = -1;
            double tmp = 0;
            for(int r = nvar; r < nequ; r++)
                if(fabs(mat[r][c]) > tmp)
                    tmp = fabs(mat[r][c]), k = r;
            if(k == -1)continue;
            std::swap(mat[nvar], mat[k]);
            for(int r = 0; r < nequ; r++)
            {
                if(fabs(mat[r][c]) < eps || r == nvar)continue;
                for(int i = c + 1; i <= nequ; i++)
                {
                    mat[r][i] -= mat[nvar][i] / mat[nvar][c] * mat[r][c];
                }
                mat[r][c] = 0;
            }
            nvar++;
        }
        for(int r = 0; r < nvar; r++)
        {
            bool zero = true;
            for(int c = r; c < nequ; c++)
            {
                if(fabs(mat[r][c]) > eps)
                {
                    zero = false;
                    break;
                }
            }
            if(zero && fabs(mat[r][nequ]) > eps)return 0; // 无解
        }
        return nvar; // 返回主元个数
    }
};