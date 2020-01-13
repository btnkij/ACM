/**
* Number:cf1285d
* Title:Dr. Evil Underscores
* Status:AC
* Tag:[分治]
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

struct Node
{
    int son[2];
    int cnt;
}trie[40*100010];
int nodeid;
int Q[40*100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)
    {
        int a; readi(a);
        int cur=0;
        for(int i=29;i>=0;i--)
        {
            int bit=(a>>i)&1;
            if(!trie[cur].son[bit])
            {
                trie[cur].son[bit]=++nodeid;
                trie[cur].cnt++;
            }
            cur=trie[cur].son[bit];
        }
    }
    int ans=0;
    int head=0,tail=0;
    Q[tail++]=0;
    for(int i=29;i>=0;i--)
    {
        int bit=2;
        for(int j=head;j<tail;j++)
        {
            bit=min(bit,trie[Q[j]].cnt);
        }
        if(bit==2)ans|=1<<i;
        int newtail=tail;
        for(int j=head;j<tail;j++)
        {
            if(trie[Q[j]].cnt==bit)
            {
                if(trie[Q[j]].son[0])Q[newtail++]=trie[Q[j]].son[0];
                if(trie[Q[j]].son[1])Q[newtail++]=trie[Q[j]].son[1];
            }
        }
        head=tail, tail=newtail;
    }
    printf("%d",ans);
    return 0;
}