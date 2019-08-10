/**
* Number:p3380
* Title:【模板】二逼平衡树（树套树）
* Status:AC
* Tag:[树套树]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <ctime>
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

struct Node
{
    int son[2], size, cnt, prior, val;
}tree[10000000];
int node_id;
int makenode(int val)
{
    tree[++node_id] = (Node){0, 0, 1, 1, rand(), val};
    return node_id;
}
void maintain(int p)
{
    Node &m = tree[p], &l = tree[m.son[0]], &r = tree[m.son[1]];
    m.size = l.size + r.size + m.cnt;
}
void rotate(int& root, int d) // d=0左旋, d=1右旋
{
    int p = tree[root].son[d ^ 1];
    tree[root].son[d ^ 1] = tree[p].son[d];
    tree[p].son[d] = root;
    maintain(root); maintain(p);
    root = p;
}
void insert(int& root, int val)
{
    if(root == 0)root = makenode(val);
    else if(tree[root].val == val)tree[root].size++, tree[root].cnt++;
    else
    {
        int d = (int)(val > tree[root].val);
        int& branch = tree[root].son[d];
        insert(branch, val);
        if(tree[root].prior < tree[branch].prior)rotate(root, d ^ 1);
        maintain(root);
    }
}
void remove(int& root, int val)
{
    if(root == 0)return;
    else if(tree[root].val == val)
    {
        int l = tree[root].son[0], r = tree[root].son[1];
        if(!l && !r)
        {
            tree[root].size--, tree[root].cnt--;
            if(tree[root].cnt == 0)root = 0;
        }
        else if(l && r)
        {
            int d = (int)(tree[l].prior > tree[r].prior);
            rotate(root, d);
            remove(tree[root].son[d], val);
        }
        else
        {
            int d = (int)(l > r);
            rotate(root, d);
            remove(tree[root].son[d], val);
        }
    }
    else
    {
        int d = tree[root].val < val;
        remove(tree[root].son[d], val);
    }
    maintain(root);
}
int order(int root, int val)
{
    int ans = 0;
    while(root)
    {
        Node& m = tree[root];
        if(m.val == val)return ans + tree[m.son[0]].size;
        if(m.val > val)root = m.son[0];
        else ans += tree[m.son[0]].size + m.cnt, root = m.son[1];
    }
    return ans;
}
int kth(int root, int k)
{
    while(root)
    {
        Node& m = tree[root];
        if(tree[m.son[0]].size >= k)root = m.son[0];
        k -= tree[m.son[0]].size;
        if(m.cnt >= k)return m.val;
        k -= m.cnt;
        root = m.son[1];
    }
    return 2147483647;
}
int prev(int root, int val)
{
    if(root == 0)return -2147483647;
    Node& m = tree[root];
    if(m.val >= val)return prev(m.son[0], val);
    return max(m.val, prev(m.son[1], val));
}
int nxt(int root, int val)
{
    if(root == 0)return 2147483647;
    Node& m = tree[root];
    if(m.val <= val)return nxt(m.son[1], val);
    return min(m.val, nxt(m.son[0], val));
}

int arr[50010];
int seg[50010<<2];
void build(int p,int l,int r)
{
    for(int i=l;i<=r;i++)
    {
        insert(seg[p],arr[i]);
    }
    if(l==r)return;
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
}
void update(int p,int l,int r,int qpos,int qval)
{
    remove(seg[p],arr[qpos]);
    insert(seg[p],qval);
    if(l==r)return;
    int mid=(l+r)>>1;
    if(qpos<=mid)update(p<<1,l,mid,qpos,qval);
    else update(p<<1|1,mid+1,r,qpos,qval);
}
int query_order(int p,int l,int r,int ql,int qr,int qval)
{
    if(ql<=l && r<=qr)return order(seg[p],qval);
    int mid=(l+r)>>1,ans=0;
    if(ql<=mid)ans+=query_order(p<<1,l,mid,ql,qr,qval);
    if(mid<qr)ans+=query_order(p<<1|1,mid+1,r,ql,qr,qval);
    return ans;
}
int query_kth(int l,int r,int ql,int qr,int k)
{
    int low=0,high=1e8;
    while(low<high)
    {
        int mid=(low+high+1)>>1;
        if(query_order(1,l,r,ql,qr,mid)+1>k)high=mid-1;
        else low=mid;
    }
    return low;
}
int query_prev(int p,int l,int r,int ql,int qr,int qval)
{
    if(ql<=l && r<=qr)return prev(seg[p],qval);
    int mid=(l+r)>>1,ans=-2147483647;
    if(ql<=mid)ans=max(ans,query_prev(p<<1,l,mid,ql,qr,qval));
    if(mid<qr)ans=max(ans,query_prev(p<<1|1,mid+1,r,ql,qr,qval));
    return ans;
}
int query_nxt(int p,int l,int r,int ql,int qr,int qval)
{
    if(ql<=l && r<=qr)return nxt(seg[p],qval);
    int mid=(l+r)>>1,ans=2147483647;
    if(ql<=mid)ans=min(ans,query_nxt(p<<1,l,mid,ql,qr,qval));
    if(mid<qr)ans=min(ans,query_nxt(p<<1|1,mid+1,r,ql,qr,qval));
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    srand(time(NULL));
    int n,m; readi(n,m);
    rep(i,1,n)readi(arr[i]);
    build(1,1,n);
    while(m--)
    {
        int op; readi(op);
        int l,r,k,pos;
        switch(op)
        {
        case 1:
            readi(l,r,k);
            printf("%d\n",query_order(1,1,n,l,r,k)+1);
            break;
        case 2:
            readi(l,r,k);
            printf("%d\n",query_kth(1,n,l,r,k));
            break;
        case 3:
            readi(pos,k);
            update(1,1,n,pos,k);
            arr[pos]=k;
            break;
        case 4:
            readi(l,r,k);
            printf("%d\n",query_prev(1,1,n,l,r,k));
            break;
        case 5:
            readi(l,r,k);
            printf("%d\n",query_nxt(1,1,n,l,r,k));
            break;
        }
    }
    return 0;
}