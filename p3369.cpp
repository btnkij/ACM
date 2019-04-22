/**
* Number:p3369
* Title:【模板】普通平衡树
* Status:?
* Tag:[splay tree, 伸展树]
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
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct splay_tree
{
    struct splay_tree_node
    {
        int value, count, rank;
        splay_tree_node *parent, *child[2];
    }nodes[100010];
    int tot, size;
    splay_tree_node *root;
    inline void _update(splay_tree_node* nod)
    {
        nod->rank = nod->child[0]->rank + nod->child[1]->rank + nod->count;
    }
    inline int _branch(splay_tree_node* nod)
    {
        return (int)(nod->parent->child[1] == nod);
    }
    inline void _link(splay_tree_node *pa, splay_tree_node *nod, int b)
    {
        if(pa)pa->child[b] = nod;
        if(nod)nod->parent = pa;
    }
    void _rotate(splay_tree_node* nod)
    {
        if(nod == root)return;
        splay_tree_node *pa = nod->parent;
        splay_tree_node *gpa = pa->parent;
        int b1 = _branch(nod), b2 = _branch(pa);
        splay_tree_node *sub = nod->child[b1 ^ 1];
        _link(gpa, nod, b2); _link(nod, pa, b1 ^ 1); _link(pa, sub, b1);
        _update(nod); _update(pa);
    }
    void _splay(splay_tree_node *nod)
    {
        while(nod != root)
        {
            splay_tree_node *pa = nod->parent;
            if(_branch(pa) == _branch(nod))
            {
                _rotate(pa); _rotate(nod);
            }
            else
            {
                _rotate(nod); _rotate(nod);
            }
        }
    }

    splay_tree_node* find(int val)
    {
        splay_tree_node *nod = root;
        while(nod)
        {
            if(nod->value == val)break;
            int b = (int)(val > nod->value);
            nod = nod->child[b];
        }
        if(nod)_splay(nod);
        return nod;
    }
    void insert(int val)
    {
        if(!root)
        {
            root = &nodes[tot++];
            *root = (splay_tree_node){val, 1, 1, NULL, NULL, NULL};
            return;
        }
        splay_tree_node *nod = root;
        while(true)
        {
            nod->rank++;
            if(nod->value == val)
            {
                nod->count++;
                break;
            }
            int b = (int)(val > nod->value);
            if(!nod->child[b])
            {
                nod->child[b] = &nodes[tot++];
                *nod->child[b] = (splay_tree_node){val, 1, 1, nod, NULL, NULL};
                nod = nod->child[b];
                break;
            }
            nod = nod->child[b];
        }
        _splay(nod);
    }
    splay_tree_node* get_prev(int val)
    {
        if(!root)return NULL;
        _splay(find(val));
        splay_tree_node *nod = root->child[1];
        while(nod->child[0])nod = nod->child[0];
        return nod;
    }
    splay_tree_node* get_next(int val)
    {
        if(!root)return NULL;
        _splay(find(val));
        splay_tree_node *nod = root->child[0];
        while(nod->child[1])nod = nod->child[1];
        return nod;
    }
    int get_rank(int val)
    {
        _splay(find(val));
        if(root->child[0])return root->child[0]->rank + 1;
        else return 1;
    }
    splay_tree_node* get_kth(int k)
    {
        splay_tree_node *nod = root;
        
    }
};



int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    
    return 0;
}