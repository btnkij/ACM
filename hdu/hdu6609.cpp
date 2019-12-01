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

struct binary_indexed_tree
{
    ll data[200010];
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
    ll query(int end)
    {
        ll sum = 0;
        while (end)
        {
            sum += data[end];
            end ^= end & -end;
        }
        return sum;
    }
}sum,cnt;

struct Node
{
    int val,idx;
    bool operator<(const Node& rhs)const
    {
        return val<rhs.val;
    }
}ord[200010];
int arr[200010],id[200010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n,m; readi(n,m);
        rep(i,1,n)
        {
            readi(arr[i]);
            ord[i]=(Node){arr[i],i};
        }
        sort(ord+1,ord+n+1);
        rep(i,1,n)id[ord[i].idx]=i;
        sum.clear(n+2);
        cnt.clear(n+2);
        rep(i,1,n)
        {
            int lt=0, rt=n+1;
            int mm=m-arr[i];
            while(lt<rt)
            {
                int mid=(lt+rt+1)>>1;
                if(sum.query(mid)>mm)rt=mid-1;
                else lt=mid;
            }
            printf("%lld ",i-1-cnt.query(lt));
            sum.add(id[i],arr[i]);
            cnt.add(id[i],1);
        }
        printf("\n");
    }
    return 0;
}