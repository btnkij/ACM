/**
 * 
 * 树状数组
 * 
**/

#include <cstring>

typedef int ll;

struct binary_indexed_tree
{
    ll data[100010];
    int size; // 最大的下标
    void clear(int size)
    {
        this->size = size;
        memset(data + 1, 0, sizeof(ll) * size);
    }
    // 原数组 arr[idx] += delta
    void add(int idx, ll delta)
    {
        while (idx <= size)
        {
            data[idx] += delta;
            idx += idx & -idx;
        }
    }
    // 查询区间 [1, end] 的和
    ll query_sum(int end)
    {
        ll sum = 0;
        while (end)
        {
            sum += data[end];
            end ^= end & -end;
        }
        return sum;
    }
};


struct binary_indexed_tree_2d
{
    ll data[5010][5010];
    int maxr, maxc; // 最大的下标
    void clear(int maxr, int maxc)
    {
        this->maxr = maxr, this->maxc = maxc;
        for(int i = 0; i <= maxr; i++)
            memset(data[i], 0, sizeof(ll)*maxc);
    }
    // 原数组 arr[r][c] += delta
    void add(int r, int c, ll delta)
    {
        for(int i = r; i <= maxr; i += i & -i)
            for(int j = c; j <= maxc; j += j & -j)
                data[i][j] += delta;
    }
    // 查询区间 [1, 1 : r, c] 的和
    ll query_sum(int r, int c)
    {
        ll sum = 0;
        for(int i = r; i; i ^= i & -i)
            for(int j = c; j; j ^= j & -j)
                sum += data[i][j];
        return sum;
    }
};