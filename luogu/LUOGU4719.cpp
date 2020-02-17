/**
* Number:luogu4719
* Title:【模板】动态 DP
* Status:?
* Tag:[]
**/

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
inline void read(T &x)
{
    int sgn = x = 0, c = getchar();
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        x = (x << 3) + (x << 1) + (c & 0xF), c = getchar();
    if (f)
        x = -x;
}

template <typename T, typename... Args>
inline void read(T &x, Args &... args)
{
    read(x);
    read(args...);
}

template <typename T>
void write(T x)
{
    if (x < 0)
        x = -x, putchar('-');
    if (x > 9)
        write(x / 10);
    putchar(0x30 | x % 10);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    return 0;
}