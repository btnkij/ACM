/**
* Number:loj10145
* Title:「一本通 4.6 练习 2」郁闷的出纳员 
* Status:AC
* Tag:[平衡树, treap]
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

template <typename T, int SZ = 1024>
struct Treap {
    struct Node {
        int l, r, heapw, size, cnt;  // 左右子节点，堆权值，子树大小，重复值个数
        T val;                       // 节点值
    };
    int _size, root, N;
    Node NS[SZ];

    int size() {
        int sz = NS[root].size;
        return sz - 2;
    }

    int _new(const T& val) {
        Node& t = NS[++_size];
        t.val = val, t.heapw = rand(), t.cnt = t.size = 1;
        return _size;
    }

    void maintain(int p) {
        Node& t = NS[p];
        t.size = NS[t.l].size + NS[t.r].size + t.cnt;
    }

    void init() {
        _size = 0;
        _new(-INF), _new(INF);
        root = 1, NS[1].r = 2;  // -∞，∞
        maintain(root);
    }

    int rankOf(int p, const T& val) {
        if (p == 0)
            return 0;
        const Node& t = NS[p];
        if (val == t.val)
            return NS[t.l].size + 1;
        if (val < t.val)
            return rankOf(t.l, val);
        return NS[t.l].size + t.cnt + rankOf(t.r, val);
    }

    T valOfRank(int p, int rank) {
        if (p == 0)
            return INF;
        const Node& t = NS[p];
        if (NS[t.l].size >= rank)
            return valOfRank(t.l, rank);
        if (NS[t.l].size + t.cnt >= rank)
            return t.val;
        return valOfRank(t.r, rank - NS[t.l].size - t.cnt);
    }

    void zig(int& p) {
        int q = NS[p].l;
        NS[p].l = NS[q].r, NS[q].r = p, p = q;
        maintain(NS[p].r), maintain(p);
    }

    void zag(int& p) {
        int q = NS[p].r;
        NS[p].r = NS[q].l, NS[q].l = p, p = q;
        maintain(NS[p].l), maintain(p);
    }

    int insert(int& p, const T& val) {
        if (p == 0)
            return p = _new(val);
        Node& t = NS[p];
        if (val == t.val)
            t.cnt++;
        else if (val < t.val) {
            insert(t.l, val);
            if (t.heapw < NS[t.l].heapw)
                zig(p);  // 不满足堆性质，右旋
        } else {
            insert(t.r, val);
            if (t.heapw < NS[t.r].heapw)
                zag(p);  // 不满足堆性质，左旋
        }
        maintain(p);
        return p;
    }

    void remove(int& p, const T& val) {
        if (p == 0)
            return;
        Node &t = NS[p], *B = NS;
        if (val == t.val) {   // 检索到了val
            if (t.cnt > 1) {  // 有重复，减少副本数即可
                t.cnt--, maintain(p);
                return;
            }

            if (t.l || t.r) {                                 // 不是叶子节点，下旋
                if (t.r == 0 || B[t.l].heapw > B[t.r].heapw)  // 右旋
                    zig(p), remove(B[p].r, val);
                else
                    zag(p), remove(B[p].l, val);
                maintain(p);
            } else
                p = 0;  // 叶子节点，删除
            return;
        }
        val < t.val ? remove(t.l, val) : remove(t.r, val);
        maintain(p);
    }

    int preOf(const T& val) {
        int ans = 1, p = root;  // a[1].val = -∞
        Node* B = NS;
        while (p) {
            if (val == B[p].val) {
                if (B[p].l) {
                    p = B[p].l;
                    while (B[p].r) p = B[p].r;  // 左子树上一直向右走
                    ans = p;
                }
                break;
            }
            if (B[p].val < val && B[p].val > B[ans].val)
                ans = p;
            p = val < B[p].val ? B[p].l : B[p].r;
        }
        return ans;
    }

    int nextOf(const T& val) {
        int ans = 2, p = root;  // a[2].val=∞
        Node* B = NS;
        while (p) {
            if (val == B[p].val) {
                if (B[p].r) {
                    p = B[p].r;
                    while (B[p].l) p = B[p].l;  // 右子树上一直向左走
                    ans = p;
                }
                break;
            }
            if (B[p].val > val && B[p].val < B[ans].val)
                ans = p;
            p = val < B[p].val ? B[p].l : B[p].r;
        }
        return ans;
    }
};

Treap<int, 100010> treap;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,k; readi(n,k);
    int base=0;
    int ans=0;
    treap.init();
    while(n--)
    {
        char op[4]; reads(op);
        int v; readi(v);
        if(op[0]=='I')
        {
            if(v>=k)
            {
                v-=base;
                treap.insert(treap.root, v);
            }
        }
        else if(op[0]=='A')
        {
            base+=v;
        }
        else if(op[0]=='S')
        {
            base-=v;
            int t=k-base;
            int val;
            while((val=treap.NS[treap.preOf(t)].val)!=-INF)
            {
                treap.remove(treap.root, val);
                ans++;
            }
        }
        else if(op[0]=='F')
        {
            if(v>treap.size())printf("-1\n");
            else
            {
                printf("%d\n", treap.valOfRank(treap.root, treap.size()-v+2)+base);
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}