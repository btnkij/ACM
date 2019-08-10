/**
* Number:hdu6621
* Title:K-th Closest Distance
* Status:AC
* Tag:[主席树, 二分]
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
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct
{
    int lson, rson, val;
}tree[100010*20];
int node_id;
inline int clone(int from)
{
    tree[++node_id] = tree[from];
    return node_id;
}
int update(int p, int lt, int rt, int qpos)
{
    int id = clone(p);
    tree[id].val++;
    if(lt==rt)return id;
    int mid = (lt + rt) >> 1;
    if(qpos <= mid)tree[id].lson = update(tree[p].lson, lt, mid, qpos);
    else tree[id].rson = update(tree[p].rson, mid + 1, rt, qpos);
    return id;
}
int query(int p, int lt, int rt, int qlt, int qrt)
{
    if(qlt <= lt && rt <= qrt)return tree[p].val;
    int mid = (lt + rt) >> 1;
    int sum = 0;
    if(qlt <= mid)sum += query(tree[p].lson, lt, mid, qlt, qrt);
    if(mid < qrt)sum += query(tree[p].rson, mid + 1, rt, qlt, qrt);
    return sum;
}

int arr[100010],ord[100010];
int root[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        node_id=0;
        int n,m; readi(n,m);
        rep(i,1,n)
        {
            readi(arr[i]);
            ord[i]=arr[i];
        }
        sort(ord+1, ord+n+1);
        rep(i,1,n)
        {
            int id=lower_bound(ord+1,ord+n+1,arr[i])-ord;
            root[i]=update(root[i-1],1,n,id);
        }
        int ans=0;
        while(m--)
        {
            int l,r,p,k; readi(l,r,p,k);
            l^=ans, r^=ans, p^=ans, k^=ans;
            int lt=0, rt=1000004;
            while(lt<rt)
            {
                int mid=(lt+rt)>>1;
                int id1=lower_bound(ord+1, ord+n+1, p-mid)-ord;
                int id2=upper_bound(ord+1, ord+n+1, p+mid)-ord-1;
                int cnt=query(root[r],1,n,id1,id2)-query(root[l-1],1,n,id1,id2);
                if(cnt<k)lt=mid+1;
                else rt=mid;
            }
            ans=lt;
            printf("%d\n",ans);
        }
    }
    return 0;
}