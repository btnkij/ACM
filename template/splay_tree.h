/**
 * 
 * Splay Tree, 伸展树, 平衡树
 * 
**/

#include <cstring>

template<typename T, int maxn, T inf = 0x7FFFFFFF>
// 类型，最大节点数，正无穷大
struct SplayTree
{
    struct Node
    {
        T value; // 值
        int count, rank; // 重复次数，排名
        Node *parent, *child[2]; // 父节点，左右儿子
    }nodes[maxn];
    int tot;
    Node _nul, *nul;
    Node *root, *end, *rend;
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
    void remove(Node *nod)
    {
        Node *pre = prevOf(nod->value);
        Node *nxt = nextOf(nod->value);
        splay(pre, nul);
        splay(nxt, pre);
        nod->count--, nod->rank--;
        if(nod->count == 0)nxt->child[0] = nul;
        maintain(nxt);
        maintain(pre);
        root = pre;
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
        if(ord <= 0)return rend;
        if(ord > root->rank)return end;
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