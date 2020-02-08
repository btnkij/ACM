/**
* Number:p3374
* Title:树状数组 1
* Status:AC
* Tag:[树状数组]
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
typedef int ll;

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

struct binary_indexed_tree
{
    int data[500010];
    int size;
    void clear(int size)
    {
        this->size = size;
        memset(data + 1, 0, sizeof(ll) * size);
    }
    void add(int idx, ll delta)
    {
        while (idx <= size)
        {
            data[idx] += delta;
            idx += idx & -idx;
        }
    }
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
}bit;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,q; readi2(n,q);
    bit.size=n;
    rep(i,1,n)
    {
        int t; readi(t);
        bit.add(i,t);
    }
    while(q--)
    {
        int op,x,y;
        readi3(op,x,y);
        if(op==1)bit.add(x,y);
        else if(op==2)
            printf("%d\n",bit.query_sum(y)-bit.query_sum(x-1));
    }
    return 0;
}