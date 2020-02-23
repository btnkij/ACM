/**
* Number:p5156
* Title:【模板】插头dp
* Status:AC
* Tag:[插头dp]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <unordered_map>
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

char maze[15][15];
unordered_map<int, ll> pre, cur;
inline int getbits(int sta, int j)
{
    return (sta >> (j << 1)) & 3;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    readi(n, m);
    int lastx, lasty;
    repne(i, 0, n)
    {
        reads(maze[i]);
        repne(j, 0, m) if (maze[i][j] == '.') lastx = i, lasty = j;
    }
    ll ans = 0;
    cur[0] = 1;
    repne2(i, 0, n, j, 0, m)
    {
        if (j == 0)
        {
            pre.clear();
            for (const auto &it : cur)
                pre[it.first << 2] = it.second;
        }
        else
            swap(pre, cur);
        cur.clear();
        for (auto it : pre)
        {
            int sta = it.first;
            ll cnt = it.second;
            int left = getbits(sta, j), up = getbits(sta, j + 1);
            if (maze[i][j] != '.')
                cur[sta] += cnt;
            else if (!left && !up)
            {
                if (maze[i][j + 1] == '.' && maze[i + 1][j] == '.')
                    cur[sta | (0b1001 << j * 2)] += cnt;
            }
            else if (!left || !up)
            {
                if (maze[i + !up][j + !left] == '.')
                    cur[sta] += cnt;
                if (maze[i + !left][j + !up] == '.')
                    cur[sta & ~(15 << j * 2) | (left << (j + 1) * 2) | (up << j * 2)] += cnt;
            }
            else if (left == up)
            {
                int dir = left == 1 ? 1 : -1;
                int nested = 1, k = dir == 1 ? j + 2 : j - 1;
                for (; nested; k += dir)
                {
                    int b = getbits(sta, k);
                    if (b == left)
                        nested++;
                    else if (b != 0)
                        nested--;
                }
                k -= dir;
                cur[sta & ~(15 << j * 2) ^ (3 << k * 2)] += cnt;
            }
            else if (left == 2 && up == 1)
                cur[sta & ~(15 << j * 2)] += cnt;
            else if (i == lastx && j == lasty)
                ans += cnt;
        }
    }
    printf("%lld", ans);
    return 0;
}