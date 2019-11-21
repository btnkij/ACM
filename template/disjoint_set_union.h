/**
 * 
 * 并查集 DSU
 * 
**/

struct disjoint_set_union
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
};