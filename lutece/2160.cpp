/**
* Number:2160
* Title:战争
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Node
{
    int to[2];
    int cnt;
}trie[500010*32];
int tot=1;
void insert(int num)
{
    int p=1;
    for(int i=30;i>=0;i--)
    {
        int k=(num>>i)&1;
        trie[p].cnt++;
        if(!trie[p].to[k])trie[p].to[k]=++tot;
        p=trie[p].to[k];
    }
    trie[p].cnt++;
}
void remove(int num)
{
    int p=1;
    for(int i=30;i>=0;i--)
    {
        int k=(num>>i)&1;
        trie[p].cnt--;
        if(trie[trie[p].to[k]].cnt==1)
        {
            trie[p].to[k]=0;
            return;
        }
        p=trie[p].to[k];
    }
    trie[p].cnt--;
}
int querymax(int num)
{
    int ans=0,p=1;
    for(int i=30;i>=0;i--)
    {
        int k=(num>>i)&1;
        if(trie[p].to[k^1])
        {
            p=trie[p].to[k^1];
            ans=(ans<<1)|1;
        }
        else
        {
            p=trie[p].to[k];
            ans=ans<<1;
        }
    }
    return ans;
}
int querymin(int num)
{
    int ans=0,p=1;
    for(int i=30;i>=0;i--)
    {
        int k=(num>>i)&1;
        if(trie[p].to[k])
        {
            p=trie[p].to[k];
            ans=ans<<1;
        }
        else
        {
            p=trie[p].to[k^1];
            ans=(ans<<1)|1;
        }
    }
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    while(n--)
    {
        int op,v; readi(op,v);
        if(op==1)
        {
            insert(v);
        }
        else if(op==2)
        {
            remove(v);
        }
        else if(op==3)
        {
            printf("%d %d\n",querymin(v),querymax(v));
        }
    }
    return 0;
}