/**
* Number:loj10049
* Title:「一本通 2.3 例 1」Phone List 
* Status:AC
* Tag:[trie, 字典树]
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
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

bool flag;
struct Trie
{
    struct Node
    {
        int count;
        Node* to[16];
    }nodes[100010];
    int tot;
    Node* root;
    Node* createNode()
    {
        Node* nod = &nodes[tot++];
        memset(nod, 0, sizeof(Node));
        return nod;
    }
    void clear()
    {
        tot = 0;
        root = createNode();
    }
    inline int ord(char ch)
    {
        return ch & 0xF;
    }
    int insert(const char* s)
    {
        Node* nod = root;
        const char* p = s;
        bool tag=false;
        while(*p)
        {
            int v = ord(*p);
            if(!nod->to[v])
            {
                nod->to[v] = createNode();
                tag=true;
            }
            nod = nod->to[v];
            if(nod->count)flag=true;
            p++;
        }
        flag=flag||!tag;
        return nod->count++;
    }
    int find(const char* s)
    {
        Node* nod = root;
        const char* p = s;
        while(*p)
        {
            int v = ord(*p);
            if(!nod->to[v])return 0;
            nod = nod->to[v];
            p++;
        }
        return nod->count;
    }
}trie;

char s[20];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        trie.clear();
        flag=false;
        while(n--)
        {
            reads(s);
            if(!flag)trie.insert(s);
        }
        if(flag)printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}