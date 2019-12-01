/**
* Number:hdu5792
* Title:World is Exploding
* Status:?
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
typedef long long ll;

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

int readu()
{
    int num = 0;
    char ch;
    do{ ch = getchar(); }while(ch < '0' || ch > '9');
    do{ num = (num << 3) + (num << 1) + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    return num;
}

const int MAXN=500;
struct binary_indexed_tree
{
    int data[MAXN];
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
}bit;

int arr[MAXN],sorted[MAXN];
int llt[MAXN],rlt[MAXN],lgt[MAXN],rgt[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF)
    {
        rep(i,1,n)arr[i]=sorted[i]=readu();
        sort(sorted+1, sorted+n+1);
        int tail=unique(sorted+1, sorted+n+1)-sorted;
        ll a=0, b=0, ans=0;
        bit.clear(n+2);
        for(int i=1;i<=n;i++)
        {
            int id=arr[i]=lower_bound(sorted+1, sorted+tail, arr[i])-sorted;
            bit.add(id,1);
            llt[i]=bit.query_sum(id-1);
            a+=llt[i];
            lgt[i]=i-bit.query_sum(id);
            b+=lgt[i];
        }
        ans=a*b;
        bit.clear(n+2);
        for(int i=n;i>=1;i--)
        {
            int id=arr[i];
            bit.add(id,1);
            rlt[i]=bit.query_sum(id-1);
            rgt[i]=(n-i+1)-bit.query_sum(id);
            ans-=llt[i]*rlt[i] + lgt[i]*rgt[i] + rgt[i]*rlt[i] + lgt[i]*llt[i];
        }
        printf("%lld\n",ans);
    }
    return 0;
}