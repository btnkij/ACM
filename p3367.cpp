/**
* Number:p3367
* Title:【模板】并查集
* Status:AC
* Tag:[并查集]
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

struct union_find_set
{
    int fa[10010];
    void clear(int n)
    {
        for(int i = 1; i <= n; i++)
            fa[i] = i;
    }
    int find_root(int x)
    {
        return x == fa[x] ? x : fa[x] = find_root(fa[x]);
    }
    bool merge(int x, int y)
    {
        int rx = find_root(x), ry = find_root(y);
        if(rx == ry)return false;
        fa[rx] = ry;
        return true;
    }
}ufs;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi2(n,m);
    ufs.clear(n);
    while(m--)
    {
        int op, x, y;
        readi3(op,x,y);
        if(op==1)
            ufs.merge(x,y);
        else if(op==2)
            printf("%c\n",ufs.find_root(x)==ufs.find_root(y)?'Y':'N');
    }
    return 0;
}