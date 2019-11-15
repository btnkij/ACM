/**
* Number:p3369
* Title:【模板】普通平衡树
* Status:AC
* Tag:[splay tree, 伸展树]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#define INF 0x3f3f3f3f
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

template<typename T, int MAXN>
struct SplayTree
{
    struct Node
    {
        int son[2], fa, sz, cnt;
        T val;
    }tree[MAXN];
    int nodeid,root;
    inline int makenode(T val)
    {
        tree[++nodeid]=(Node){0,0,0,1,val};
        return nodeid;
    }
    inline void link(int u,int fa,int d)
    {
        tree[u].fa=fa;
        tree[fa].son[d]=u;
    }
    void init()
    {
        memset(tree[nodeid=0],0,sizeof(Node));
        link(root=makenode(INF),0,0);
        link(makenode(-INF),root,0);
    }
    inline void pushup(int u)
    {
        Node& nod=tree[u];
        nod.sz=tree[nod.son[0]].sz+tree[nod.son[1]].sz+nod.cnt;
    }
    inline int dir(int u)
    {
        return tree[tree[u].fa].son[1]==u;
    }
    void rotate(int u)
    {
        int fa=tree[u].fa, dfa=dir(u);
        int ffa=tree[fa].fa, dffa=dir(fa);
        int son=tree[u].son[dfa^1];
        link(u,ffa,dffa); link(fa,u,dfa^1); link(son,fa,dfa);
        pushup(fa); pushup(u);
    }
    void splay(int u,int top)
    {
        for(int fa=tree[u].fa;fa!=top;)
        {
            if(tree[fa].fa)
                rotate(dir(u)==dir(fa)?tree[fa].fa:fa);
            rotate(u);
        }
    }
    int findpos(T val, int subtree)
    {
        while(true)
        {
            Node& nod=tree[subtree];
            if(val<nod.val && nod.son[0])subtree=nod.son[0];
            else if(val>nod.val && nod.son[1])subtree=nod.son[1];
            else break;
        }
        return subtree;
    }
    int find(T val)
    {
        root=findpos(val,tree[0].son[0]);
        splay(root,0);
        return tree[root].val==val ? root : 0;
    }
    int prev(T val)
    {
        find(val);
        if(tree[root].val<val)return root;
        else return findpos(val,tree[root].son[0]);
    }
    int next(T val)
    {
        find(val);
        if(tree[root].val>val)return root;
        else return findpos(val,tree[root].son[1]);
    }
    void insert(T val)
    {
        int u=findpos(val,root),v;
        if(tree[u].val==val)tree[v=u].cnt++;
        else link(v=makenode(val),u,val>tree[u].val);
        splay(v,0);
    }
    void remove(T val)
    {
        if(!find(val))return;
        if(tree[root].cnt>1)
        {
            tree[root].cnt--;
            tree[root].sz--;
        }
        else
        {
            int l=findpos(val,tree[root].son[0]);
            int r=findpos(val,tree[root].son[1]);
            splay(l,0); splay(r,l);
            tree[r].son[0]=0;
            pushup(r); pushup(l);
        }
    }
    int rank(T val)
    {
        find(val);
        if(tree[root].val>=val)return tree[tree[root].son[0]].sz;
        else return tree[tree[root].son[0]].sz+tree[root].cnt;
    }
    int kth(int k)
    {
        k++;
        for(int u=root;k;)
        {
            int l=tree[u].son[0], r=tree[u].son[1];
            if(k<=tree[l].sz)u=l;
            else if(k<=tree[l].sz+tree[u].cnt)return tree[u].val;
            else u=r,k-=tree[l].sz+tree[u].cnt;
        }
    }
};

SplayTree<int,100010> splay;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    while(n--)
    {
        int op,x; readi(op,x);
        switch(op)
        {
        case 1:
            splay.insert(x);
            break;
        case 2:
            splay.remove(x);
            break;
        case 3:
            printf("%d\n",splay.rank(x));
            break;
        case 4:
            printf("%d\n",splay.kth(x));
            break;
        case 5:
            printf("%d\n",splay.tree[splay.prev(x)]);
            break;
        case 6:
            printf("%d\n",splay.tree[splay.next(x)]);
            break;
        }
    }
    return 0;
}

/**
* Number:p3369
* Title:【模板】普通平衡树
* Status:AC
* Tag:[fhq treap]
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

template<typename T, int MAXN>
struct Treap
{
    struct Node
    {
        int son[2], size, cnt, w;
        T val;
    }tree[MAXN];
    int node_id, root;
    int makenode(T val)
    {
        Node& nod = tree[++node_id];
        nod = (Node){0, 0, 1, 1, rand(), val};
        return node_id;
    }
    void maintain(int id)
    {
        Node& mid = tree[id];
        const Node& ltree = tree[mid.son[0]];
        const Node& rtree = tree[mid.son[1]];
        mid.size = ltree.size + rtree.size + mid.cnt;
    }
    void splitByValue(T val, int p, int& l, int& r)
    {
        if(p == 0)
        {
            l = r = 0;
            return;
        }
        if(tree[p].val <= val)
        {
            l = p;
            splitByValue(val, tree[p].son[1], tree[l].son[1], r);
        }
        else
        {
            r = p;
            splitByValue(val, tree[p].son[0], l, tree[r].son[0]);
        }
        maintain(p);
    }
    void splitBySize(int size, int p, int& l, int& r)
    {
        if(p == 0)
        {
            l = r = 0;
            return;
        }
        int lsz = tree[tree[p].son[0]].size;
        if(lsz < size)
        {
            l = p;
            splitBySize(size - lsz - tree[p].cnt, tree[p].son[1], tree[l].son[1], r);
        }
        else
        {
            r = p;
            splitBySize(size, tree[p].son[0], l, tree[r].son[0]);
        }
        maintain(p);
    }
    int merge(int l, int r)
    {
        if(l == 0 || r == 0)return l | r;
        int p;
        if(tree[l].w < tree[r].w)
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
    void insert(T val)
    {
        int l, m, r;
        splitByValue(val, root, l, r);
        splitByValue(val - 1, l, l, m);
        if(m)tree[m].cnt++, tree[m].size++;
        else m = makenode(val);
        root = merge(merge(l, m), r);
    }
    void remove(T val)
    {
        int l, m, r;
        splitByValue(val, root, l, r);
        splitByValue(val - 1, l, l, m);
        if(m)
        {
            if(tree[m].cnt == 1)m = 0;
            else tree[m].cnt--, tree[m].size--;
        }
        root = merge(merge(l, m), r);
    }
    int rank(T val)
    {
        int l, r;
        splitByValue(val - 1, root, l, r);
        int ans = tree[l].size + 1;
        root = merge(l, r);
        return ans;
    }
    T kth(int k)
    {
        int l, r, p;
        splitBySize(k, root, l, r);
        for(p = l; tree[p].son[1]; p = tree[p].son[1]);
        root = merge(l, r);
        return tree[p].val;
    }
    T prev(T val)
    {
        int l, r, p;
        splitByValue(val - 1, root, l, r);
        for(p = l; tree[p].son[1]; p = tree[p].son[1]);
        root = merge(l, r);
        return tree[p].val;
    }
    T next(T val)
    {
        int l, r, p;
        splitByValue(val, root, l, r);
        for(p = r; tree[p].son[0]; p = tree[p].son[0]);
        root = merge(l, r);
        return tree[p].val;
    }
};

Treap<int, 100010> treap;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    while(n--)
    {
        int op,x; readi(op,x);
        switch(op)
        {
        case 1:
            treap.insert(x);
            break;
        case 2:
            treap.remove(x);
            break;
        case 3:
            printf("%d\n",treap.rank(x));
            break;
        case 4:
            printf("%d\n",treap.kth(x));
            break;
        case 5:
            printf("%d\n",treap.prev(x));
            break;
        case 6:
            printf("%d\n",treap.next(x));
            break;
        }
    }
    return 0;
}
*/