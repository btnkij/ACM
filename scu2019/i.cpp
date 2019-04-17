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

struct Node
{
    int end;
    int nxt[11];
}trie[40005*12];
int tot;

bool flag;
void add(char* s)
{
    bool branch=false;
    Node* node=&trie[0];
    int i=0;
    while(s[i])
    {
        int d=s[i]&0xF;
        if(node->nxt[d])
        {
            node=&trie[node->nxt[d]];
            if(node->end)
            {
                flag=true;
                return;
            }
        }
        else
        {
            node->nxt[d]=tot;
            node=&trie[tot];
            tot++;
            branch=true;
        }
        i++;
    }
    node->end++;
    if(!branch)flag=true;
}

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
        flag=false;
        mset(trie, 0);
        tot=1;
        while(n--)
        {
            reads(s);
            if(!flag)add(s);
        }
        printf("%s\n",!flag?"YES":"NO");
    }
    return 0;
}