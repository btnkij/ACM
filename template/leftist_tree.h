/**
 * 
 * 左偏树 可并堆
 * 
**/

#include <algorithm>

const int MAXN = 1e5 + 10;
int val[MAXN], dis[MAXN], fa[MAXN], son[MAXN][2];
int findr(int x)
{
    return x == fa[x] ? x : fa[x] = findr(fa[x]);
}
int join(int x, int y) // 合并以x, y为根的堆, x或y作为新的根
{
    if(x == 0 || y == 0)return x | y;
    if(val[x] > val[y] || (val[x] == val[y] && x > y))std::swap(x, y);
    son[x][1] = join(son[x][1], y);
    if(dis[son[x][0]] < dis[son[x][1]])std::swap(son[x][0], son[x][1]);
    dis[x] = dis[son[x][1]] + 1;
    return fa[x] = fa[son[x][0]] = fa[son[x][1]] = x;
}
void pop(int x) // 删除节点x, x是堆的根
{
    fa[son[x][0]] = son[x][0];
    fa[son[x][1]] = son[x][1];
    fa[x] = join(son[x][0], son[x][1]);
}