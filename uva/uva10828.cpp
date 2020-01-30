/**
* Number:uva10828
* Title:Back to Kernighan-Ritchie
* Status:AC
* Tag:[高斯消元]
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

const double eps = 1e-6;
double mat[110][110];
void gauss(int n)
{
    for (int cur = 1; cur <= n; cur++)
    {
        double maxv = 0;
        int maxi = -1;
        for (int i = cur; i <= n; i++)
        {
            if (fabs(mat[i][cur]) - fabs(maxv) > eps)
            {
                maxv = mat[i][cur];
                maxi = i;
            }
        }
        if (maxi == -1)
            continue;
        for (int j = 1; j <= n + 1; j++)
            swap(mat[cur][j], mat[maxi][j]);
        for (int i = 1; i <= n; i++)
        {
            if (i == cur)
                continue;
            for (int j = n + 1; j >= cur; j--)
            {
                mat[i][j] -= mat[cur][j] * mat[i][cur] / maxv;
            }
        }
    }
}
vector<int> edges[110];
bool inf[110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, kase = 1;
    while (readi(n) != EOF && n)
    {
        rep(i, 1, n) edges[i].clear();
        clr(mat, 0);
        mat[1][n + 1] = -1;
        int u, v;
        while (readi(u, v), u)
            edges[u].push_back(v);
        rep(i, 1, n)
        {
            mat[i][i] = -1;
            repne(j, 0, edges[i].size())
            {
                mat[edges[i][j]][i] += 1.0 / edges[i].size();
            }
        }
        gauss(n);
        clr(inf, false);
        for (int i = n; i >= 1; i--)
        {
            if (fabs(mat[i][i]) < eps && fabs(mat[i][n + 1]) > eps)
                inf[i] = true;
            for (int j = i + 1; j <= n; j++)
            {
                if (fabs(mat[i][j]) > eps && inf[j])
                {
                    inf[i] = true;
                    break;
                }
            }
        }
        int q;
        readi(q);
        printf("Case #%d:\n", kase++);
        while (q--)
        {
            int u;
            readi(u);
            if (inf[u])
                puts("infinity");
            else if (fabs(mat[u][u]) < eps || fabs(mat[u][n + 1] / mat[u][u]) < eps)
                puts("0.000");
            else
                printf("%.3lf\n", mat[u][n + 1] / mat[u][u]);
        }
    }
    return 0;
}