/**
* Number:ybt1539, loj10117
* Title:简单题
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

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)


struct binary_indexed_tree
{
    int data[100010];
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
}T;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    T.size=n;
    while(m--)
    {
        int t; readi(t);
        if(t==1)
        {
            int L,R; readi(L,R);
            T.add(L, 1);
            T.add(R+1, -1);
        }
        else if(t==2)
        {
            int i; readi(i);
            printf("%d\n",(T.query_sum(i)%2+2)%2);
        }
    }
    return 0;
}