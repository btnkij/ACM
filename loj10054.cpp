/**
* Number:loj10054
* Title:「一本通 2.3 练习 3」Secret Message 秘密信息 
* Status:AC
* Tag:[trie]
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

inline int readu()
{
    int num = 0;
    char ch;
    do{ ch = getchar(); }while(ch < '0' || ch > '9');
    do{ num = (num << 3) + (num << 1) + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    return num;
}

struct Node
{
    int count,end;
    int to[2];
}nodes[1000010];
int tot;
int find(int *s, int len)
{
    int p=0;
    int ans=0;
    for(int i=0;i<len;i++)
    {
        int& r=nodes[p].to[s[i]];
        if(!r)return ans;
        p=r;
        ans+=nodes[p].end;
    }
    return ans+nodes[p].count;
}
void insert(int *s, int len)
{
    int p=0;
    for(int i=0;i<len;i++)
    {
        int& r=nodes[p].to[s[i]];
        if(!r)r=tot++;
        p=r;
        nodes[p].count++;
    }
    nodes[p].count--;
    nodes[p].end++;
}

int num[10010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    tot=1;
    while(n--)
    {
        int len=readu();
        repne(i,0,len)num[i]=readu();
        insert(num,len);
    }
    while(m--)
    {
        int len=readu();
        repne(i,0,len)num[i]=readu();
        printf("%d\n",find(num,len));
    }
    return 0;
}