/**
* Number:p3402
* Title:【模板】可持久化并查集
* Status:AC
* Tag:[可持久化并查集]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cassert>
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

const int MAXN=3e5+10;

struct Node
{
    int lson,rson,fa,dep;
}tree[MAXN*20];
int tot;
int clone(int ori)
{
    tree[++tot]=tree[ori];
    return tot;
}
int build(int p,int lt,int rt)
{
    int id=clone(p);
    if(lt==rt)
    {
        tree[id].fa=lt;
        return id;
    }
    int mid=(lt+rt)>>1;
    tree[id].lson=build(tree[p].lson,lt,mid);
    tree[id].rson=build(tree[p].rson,mid+1,rt);
    return id;
}
int query(int p,int lt,int rt,int qpos)
{
    if(lt==rt)return p;
    int mid=(lt+rt)>>1;
    if(qpos<=mid)return query(tree[p].lson,lt,mid,qpos);
    else return query(tree[p].rson,mid+1,rt,qpos);
}
int update(int p,int lt,int rt,int qpos,int fa,int dep)
{
    int id=clone(p);
    if(lt==rt)
    {
        tree[id].fa=fa;
        tree[id].dep=dep;
        return id;
    }
    int mid=(lt+rt)>>1;
    if(qpos<=mid)tree[id].lson=update(tree[p].lson,lt,mid,qpos,fa,dep);
    else tree[id].rson=update(tree[p].rson,mid+1,rt,qpos,fa,dep);
    return id;
}

int root[MAXN],ver,n;
int getfa(int x)
{
    int p=query(root[ver],1,n,x);
    return x==tree[p].fa ? p : getfa(tree[p].fa);
}
void merge(int x,int y)
{
    int px=getfa(x),py=getfa(y);
    int rx=tree[px].fa,dx=tree[px].dep;
    int ry=tree[py].fa,dy=tree[py].dep;
    if(rx==ry)return;
    if(dx>dy)swap(rx,ry),swap(dx,dy);
    root[ver]=update(root[ver],1,n,rx, ry, dx);
    if(dx==dy)root[ver]=update(root[ver],1,n,ry,ry,dy+1);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m; readi(n,m);
    root[0]=build(0,1,n);
    for(ver=1;ver<=m;ver++)
    {
        int op; readi(op);
        root[ver]=root[ver-1];
        if(op==1)
        {
            int a,b; readi(a,b);
            merge(a,b);
        }
        else if(op==2)
        {
            int k; readi(k);
            root[ver]=root[k];
        }
        else if(op==3)
        {
            int a,b; readi(a,b);
            int ra=getfa(a),rb=getfa(b);
            printf("%d\n",tree[ra].fa==tree[rb].fa);
        }
    }
    return 0;
}

/*
template<typename T>
struct PersistentArray
{
    struct Node
    {
        int lson, rson;
        T val;
    };
    vector<Node> tree;
    vector<int> history;
    int root, size, qpos;
    T qval;
    void init(int _size)
    {
        this->size = _size;
        tree.reserve(_size * 20);
        tree.clear();
        tree.push_back({0, 0, (T)0});
        history.clear();
        history.push_back(root = 0);
    }
    int build2(int lt, int rt)
    {
        int id = tree.size();
        tree.push_back({0, 0, (T)0});
        if(lt == rt)
        {
            tree[id].val = lt;
            return id;
        }
        int mid = (lt + rt) >> 1;
        tree[id].lson = build2(lt, mid);
        tree[id].rson = build2(mid + 1, rt);
        return id;
    }
    void init2(int _size)
    {
        this->size = _size;
        tree.reserve(_size * 20);
        tree.clear();
        history.clear();
        history.push_back(root = build2(1, _size));
    }
    int clone(int origin_id)
    {
        assert(origin_id < tree.size()); // 节点不存在
        int id = tree.size();
        tree.push_back(tree[origin_id]);
        return id;
    }
    T getHelp(int p, int lt, int rt)
    {
        if(lt == rt)return tree[p].val;
        int mid = (lt + rt) >> 1;
        if(qpos <= mid)return getHelp(tree[p].lson, lt, mid);
        else return getHelp(tree[p].rson, mid + 1, rt);
    }
    T get(int idx)
    {
        assert(root < tree.size()); // 历史版本不存在
        assert(idx < size); // 数组下标越界
        qpos = idx;
        return getHelp(root, 1, size);
    }
    int setHelp(int p, int lt, int rt)
    {
        int id = clone(p);
        if(lt == rt)
        {
            tree[id].val = qval;
            return id;
        }
        int mid = (lt + rt) >> 1;
        if(qpos <= mid)
        {
            tree[id].lson = setHelp(tree[p].lson, lt, mid);
        }
        else
        {
            tree[id].rson = setHelp(tree[p].rson, mid + 1, rt);
        }
        return id;
    }
    int set(int idx, T val)
    {
        assert(root < tree.size()); // 历史版本不存在
        assert(idx < size); // 数组下标越界
        qpos = idx, qval = val;
        return root = setHelp(root, 1, size);
    }
    int mark()
    {
        history.push_back(root);
        return history.size() - 1;
    }
    void version(int t)
    {
        assert(t < history.size()); // 历史版本不存在
        root = history[t];
    }
};

PersistentArray<int> fa,rk;
int getfa(int x)
{
    int rx=fa.get(x);
    return x==rx ? x : getfa(rx);
}
void merge(int x,int y)
{
    int rx=fa.get(x), ry=fa.get(y);
    if(rx==ry)return;
    int wx=rk.get(rx), wy=rk.get(ry);
    if(wx<=wy)
    {
        fa.set(rx,ry);
        if(wx==wy)rk.set(ry,wy+1);
    }
    else
    {
        fa.set(ry,rx);
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    fa.init2(n+10);
    rk.init(n+10);
    rep(i,1,m)
    {
        int op; readi(op);
        if(op==1)
        {
            int a,b; readi(a,b);
            merge(a,b);
        }
        else if(op==2)
        {
            int k; readi(k);
            fa.version(k);
            rk.version(k);
        }
        else if(op==3)
        {
            int a,b; readi(a,b);
            int ra=getfa(a), rb=getfa(b);
            printf("%d\n",ra==rb);
        }
        fa.mark(); rk.mark();
    }
    return 0;
}
*/