/**
* Number:loj10145
* Title:「一本通 4.6 练习 2」郁闷的出纳员 
* Status:WA
* Tag:[平衡树, splay]
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

SplayTree<int, 100010> tree;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,k; readi(n,k);
    int base=0;
    int ans=0;
    tree.init();
    rep(i,1,n)
    {
        char op[4]; reads(op);
        int v; readi(v);
        if(i==26623)
        {
            op[1]='a';
        }
        if(op[0]=='I')
        {
            if(v>=k)
            {
                v-=base;
                tree.insert(v);
            }
        }
        else if(op[0]=='A')
        {
            base+=v;
        }
        else if(op[0]=='S')
        {
            base-=v;
            ans += tree.removeRange(-INF, k-base-1)->rank;
        }
        else if(op[0]=='F')
        {
            if(v>tree.size())
                printf("-1\n");
            else
                printf("%d\n", tree.findByOrder(tree.size()-v+1)->value+base);
        }
    }
    printf("%d\n",ans);
    return 0;
}