/**
* Number:p3835
* Title:【模板】可持久化平衡树
* Status:AC
* Tag:[可持久化, fhq treap]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <ctime>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 1e6 + 10;
struct Node // FhqTreap模板
{
    int son[2], size, cnt, prior, val;
} tree[MAXN * 30];
int node_id;
int clone(int ori)
{
    tree[++node_id] = tree[ori];
    return node_id;
}
int makenode(int val)
{
    tree[++node_id] = (Node){0, 0, 1, 1, rand(), val};
    return node_id;
}
void maintain(int p)
{
    tree[p].size = tree[tree[p].son[0]].size + tree[tree[p].son[1]].size + tree[p].cnt;
}
void split(int val, int p, int &l, int &r)
{
    if (p == 0)
    {
        l = r = 0;
        return;
    }
    int id = clone(p); // 只加这一行代码就可实现可持久化
    if (tree[id].val <= val)
    {
        l = id;
        split(val, tree[id].son[1], tree[l].son[1], r);
    }
    else
    {
        r = id;
        split(val, tree[id].son[0], l, tree[r].son[0]);
    }
    maintain(id);
}
int merge(int l, int r)
{
    if (l == 0 || r == 0)
        return l | r;
    int p;
    if (tree[l].prior < tree[r].prior)
    {
        p = r;
        tree[r].son[0] = merge(l, tree[r].son[0]);
    }
    else
    {
        p = l;
        tree[l].son[1] = merge(tree[l].son[1], r);
    }
    maintain(p);
    return p;
}
void insert(int &root, int val)
{
    int l, m, r;
    split(val, root, l, r);
    split(val - 1, l, l, m);
    if (m)
        tree[m].cnt++, tree[m].size++;
    else
        m = makenode(val);
    root = merge(merge(l, m), r);
}
void remove(int &root, int val)
{
    int l, m, r;
    split(val, root, l, r);
    split(val - 1, l, l, m);
    if (m)
    {
        if (tree[m].cnt == 1)
            m = 0;
        else
            tree[m].cnt--, tree[m].size--;
    }
    root = merge(merge(l, m), r);
}
int order(int &root, int val)
{
    int l, r;
    split(val - 1, root, l, r);
    int ans = tree[l].size + 1;
    root = merge(l, r);
    return ans;
}
int kth(int root, int k)
{
    // if(k>tree[root].size)throw;
    int p = root;
    while (true)
    {
        if (tree[tree[p].son[0]].size >= k)
        {
            p = tree[p].son[0];
            continue;
        }
        k -= tree[tree[p].son[0]].size;
        if (k <= tree[p].cnt)
            return tree[p].val;
        k -= tree[p].cnt;
        p = tree[p].son[1];
    }
}
int prev(int &root, int val)
{
    int l, r, p;
    split(val - 1, root, l, r);
    for (p = l; tree[p].son[1]; p = tree[p].son[1])
        ;
    root = merge(l, r);
    return tree[p].val;
}
int nxt(int &root, int val)
{
    int l, r, p;
    split(val, root, l, r);
    for (p = r; tree[p].son[0]; p = tree[p].son[0])
        ;
    root = merge(l, r);
    return tree[p].val;
}

int root[MAXN], ver;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    srand(233333);
    int n;
    readi(n);
    insert(root[0], -2147483647);
    insert(root[0], 2147483647);
    for (ver = 1; ver <= n; ver++)
    {
        int v, opt, x;
        readi(v, opt, x);
        root[ver] = root[v]; // 在版本v的基础上操作
        switch (opt)
        {
        case 1: // 插入x数
            insert(root[ver], x);
            break;
        case 2: // 删除x数(若有多个相同的数，因只删除一个，如果没有请忽略该操作)
            remove(root[ver], x);
            break;
        case 3: // 查询x数的排名(排名定义为比当前数小的数的个数+1。若有多个相同的数，因输出最小的排名)
            printf("%d\n", order(root[ver], x) - 1);
            break;
        case 4: // 查询排名为x的数
            printf("%d\n", kth(root[ver], x + 1));
            break;
        case 5: // 求x的前驱(前驱定义为小于x，且最大的数，如不存在输出-2147483647)
            printf("%d\n", prev(root[ver], x));
            break;
        case 6: // 求x的后继(后继定义为大于x，且最小的数，如不存在输出2147483647)
            printf("%d\n", nxt(root[ver], x));
            break;
        }
    }
    return 0;
}

/**
* Number:p3835
* Title:【模板】可持久化平衡树
* Status:AC
* Tag:[可持久化线段树, 二分]
**/

/*
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

const int MAXN=5e5+10;

struct Node
{
    Node *lson,*rson;
    int val;
}tree[MAXN*20];
int node_id;
Node* clone(Node* ori)
{
    tree[++node_id]=*ori;
    return &tree[node_id];
}
Node* update(Node* p,int lt,int rt,int qpos,int qval)
{
    Node* nod=clone(p);
    if(lt==rt)
    {
        nod->val=max(0, nod->val+qval);
        return nod;
    }
    int mid=(lt+rt)>>1;
    if(qpos<=mid)nod->lson=update(nod->lson,lt,mid,qpos,qval);
    else nod->rson=update(nod->rson,mid+1,rt,qpos,qval);
    nod->val=nod->lson->val+nod->rson->val;
}
int query(Node* p,int lt,int rt,int qlt,int qrt)
{
    if(qlt<=lt && rt<=qrt)return p->val;
    int mid=(lt+rt)>>1;
    int sum=0;
    if(qlt<=mid)sum+=query(p->lson,lt,mid,qlt,qrt);
    if(mid<qrt)sum+=query(p->rson,mid+1,rt,qlt,qrt);
    return sum;
}

int v[MAXN],opt[MAXN],x[MAXN],ord[MAXN],tot;
Node* root[MAXN];
void init()
{
    node_id=0;
    tree[0]=(Node){&tree[0],&tree[0],0};
    root[0]=&tree[0];
    root[0]=update(root[0],1,tot-1,1,1);
    root[0]=update(root[0],1,tot-1,tot-1,1);
}
int nth(Node* p,int lt,int rt,int n)
{
    if(lt==rt)return ord[lt];
    int mid=(lt+rt)>>1;
    if(p->lson->val > n)return nth(p->lson,lt,mid,n);
    else return nth(p->rson, mid+1, rt, n - p->lson->val);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    ord[1]=x[1]=-2147483647, ord[n+2]=x[n+2]=2147483647;
    rep(i,1,n)
    {
        readi(v[i],opt[i],x[i+1]);
        ord[i+1]=x[i+1];
    }
    sort(ord+1,ord+n+3);
    tot=unique(ord+1,ord+n+3)-ord;
    init();
    rep(i,1,n)
    {
        int id=lower_bound(ord+1,ord+tot,x[i+1])-ord;
        int k;
        switch(opt[i])
        {
        case 1:
            root[i]=update(root[v[i]],1,tot-1,id,1);
            break;
        case 2:
            root[i]=update(root[v[i]],1,tot-1,id,-1);
            break;
        case 3:
            root[i]=root[v[i]];
            printf("%d\n",query(root[v[i]],1,tot-1,1,id-1));
            break;
        case 4:
            root[i]=root[v[i]];
            printf("%d\n",nth(root[v[i]],1,tot-1,x[i+1]));
            break;
        case 5:
            root[i]=root[v[i]];
            k=query(root[v[i]],1,tot-1,1,id-1);
            printf("%d\n",nth(root[v[i]],1,tot-1,k-1));
            break;
        case 6:
            root[i]=root[v[i]];
            k=query(root[v[i]],1,tot-1,1,id);
            printf("%d\n",nth(root[v[i]],1,tot-1,k));
            break;
        }
    }
    return 0;
}
*/