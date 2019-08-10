/**
* Number:p3369
* Title:【模板】普通平衡树
* Status:AC
* Tag:[fhq treap]
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

/**
* Number:p3369
* Title:【模板】普通平衡树
* Status:AC
* Tag:[splay tree, 伸展树]
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
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

template<typename T, int maxn, T inf = 0x7FFFFFFF>
struct SplayTree
{
    struct Node
    {
        T value;
        int count, rank;
        Node *parent, *child[2];
    }nodes[maxn];
    int tot;
    Node _nul, *nul;
    Node *root, *end, *rend;
    int size()
    {
        return root->rank - 2;
    }
    Node* createNode(T val)
    {
        Node *nod = &nodes[tot++];
        nod->value = val;
        nod->count = nod->rank = 1;
        nod->parent = nod->child[0] = nod->child[1] = nul;
        return nod;
    }
    inline void link(Node *nod, Node *pa, int b)
    {
        nod->parent = pa;
        if(pa != nul)pa->child[b] = nod;
    }
    void init()
    {
        tot = 0;
        nul = &_nul;
        memset(nul, 0, sizeof(Node));
        root = rend = createNode(-inf);
        end = createNode(inf);
        root->child[1] = end;
        end->parent = root;
    }
    inline void maintain(Node* nod)
    {
        nod->rank = nod->count + nod->child[0]->rank + nod->child[1]->rank;
    }
    inline int branch(Node* nod)
    {
        return (int)(nod->parent->child[1] == nod);
    }
    void rotate(Node* nod)
    {
        Node *pa = nod->parent;
        Node *gpa = pa->parent;
        int b = branch(nod);
        link(nod, gpa, branch(pa));
        link(nod->child[b ^ 1], pa, b);
        link(pa, nod, b ^ 1);
        maintain(pa);
        maintain(nod);
    }
    void splay(Node *nod, Node *pa)
    {
        while(nod->parent != pa)
        {
            Node *pnod = nod->parent;
            if(pnod->parent != pa)
                rotate(branch(nod) == branch(pnod) ? pnod : nod);
            rotate(nod);
        }
    }
    Node* findpos(T val, Node *tree)
    {
        Node *nod = tree;
        while(nod != nul)
        {
            if(val < nod->value && nod->child[0] != nul)nod = nod->child[0];
            else if(val > nod->value && nod->child[1] != nul)nod = nod->child[1];
            else break;
        }
        return nod;
    }
    Node* find(T val)
    {
        Node *nod = findpos(val, root);
        splay(nod, nul);
        root = nod;
        return nod->value == val ? nod : NULL;
    }
    void insert(T val)
    {
        Node *nod = findpos(val, root);
        if(nod->value == val)nod->count++, root = nod;
        else link(root = createNode(val), nod, (int)(val > nod->value));
        splay(root, nul);
    }
    Node* remove(T val)
    {
        Node *pre = prevOf(val);
        Node *nxt = nextOf(val);
        splay(pre, nul);
        splay(nxt, pre);
        Node *nod = nxt->child[0];
        nod->count--, nod->rank--;
        if(nod->count == 0)nxt->child[0] = nul;
        maintain(nxt);
        maintain(pre);
        root = pre;
        return nod;
    }
    Node* removeRange(T lbound, T rbound)
    {
        Node *pre = prevOf(lbound);
        Node *nxt = nextOf(rbound);
        splay(pre, nul);
        splay(nxt, pre);
        Node *nod = nxt->child[0];
        nxt->child[0] = nul;
        maintain(nxt);
        maintain(pre);
        root = pre;
        return nod;
    }
    Node* prevOf(T val)
    {
        find(val);
        if(root->value < val)return root;
        return findpos(val, root->child[0]);
    }
    Node* nextOf(T val)
    {
        find(val);
        if(root->value > val)return root;
        return findpos(val, root->child[1]);
    }
    int orderOf(T val)
    {
        find(val);
        if(root->value >= val)return root->child[0]->rank;
        return root->child[0]->rank + root->count;
    }
    Node* findByOrder(int ord)
    {
        ord++;
        Node *nod = root;
        while(nod != nul)
        {
            if(nod->child[0]->rank >= ord)
                nod = nod->child[0];
            else if(nod->child[0]->rank + nod->count >= ord)
                break;
            else
            {
                ord -= nod->child[0]->rank + nod->count;
                nod = nod->child[1];
            }
        }
        return nod;
    }
};

SplayTree<int, 100010> Tree;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    Tree.init();
    int n; readi(n);
    rep(i,1,n)
    {
        int op, k; readi(op, k);
        switch(op)
        {
            case 1:
            Tree.insert(k);
            break;
            case 2:
            Tree.remove(k);
            break;
            case 3:
            printf("%d\n", Tree.orderOf(k));
            break;
            case 4:
            printf("%d\n", Tree.findByOrder(k)->value);
            break;
            case 5:
            printf("%d\n", Tree.prevOf(k)->value);
            break;
            case 6:
            printf("%d\n", Tree.nextOf(k)->value);
            break;
        }
    }
    return 0;
}
*/