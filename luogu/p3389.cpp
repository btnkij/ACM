/**
* Number:p3389
* Title:【模板】高斯消元法
* Status:?
* Tag:[]
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 104;
const double eps = 1e-15;
struct gauss_elimination
{
    double* mat[MAXN];
    int operator()(double arr[][MAXN], int nequ)
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
            swap(mat[nvar], mat[k]);
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
}solver;
double arr[MAXN][MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)rep(j,0,n)scanf("%lf",&arr[i][j]);
    int r = solver(arr, n);
    if(r<n)printf("No Solution\n");
    else
    {
        repne(i,0,n)
            printf("%.2lf\n",(double)solver.mat[i][n]/solver.mat[i][i]);
    }
    return 0;
}