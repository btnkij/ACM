/**
* Number:p3377
* Title:【模板】左偏树（可并堆）
* Status:?
* Tag:[左偏树, 可并堆]
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
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 1e5 + 10;
int val[MAXN], dis[MAXN], fa[MAXN], son[MAXN][2];
int findr(int x)
{
    return x == fa[x] ? x : fa[x] = findr(fa[x]);
}
int join(int x, int y) // 合并以x, y为根的堆, x或y作为新的根
{
    if(x == 0 || y == 0)return x | y;
    if(val[x] > val[y] || (val[x] == val[y] && x > y))swap(x, y);
    son[x][1] = join(son[x][1], y);
    if(dis[son[x][0]] < dis[son[x][1]])swap(son[x][0], son[x][1]);
    dis[x] = dis[son[x][1]] + 1;
    return fa[x] = fa[son[x][0]] = fa[son[x][1]] = x;
}
void pop(int x) // 删除节点x, x是堆的根
{
    fa[son[x][0]] = son[x][0];
    fa[son[x][1]] = son[x][1];
    fa[x] = join(son[x][0], son[x][1]);
}

bool del[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    dis[0]=-1;
    rep(i,1,n)
    {
        readi(val[i]);
        fa[i]=i;
    }
    while(m--)
    {
        int op; readi(op);
        if(op==1)
        {
            int x,y; readi(x,y);
            if(del[x]||del[y])continue;
            int rx=findr(x),ry=findr(y);
            if(rx==ry)continue;
            join(rx,ry);
        }
        else if(op==2)
        {
            int x; readi(x);
            if(del[x])printf("-1\n");
            else
            {
                int rx=findr(x);
                printf("%d\n",val[rx]);
                del[rx]=true;
                pop(rx);
            }
        }
    }
    return 0;
}