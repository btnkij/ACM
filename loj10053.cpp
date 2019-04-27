/**
* Number:loj10053
* Title:「一本通 2.3 练习 2」L 语言 
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

struct Node
{
    int count;
    int to[26];
}nodes[10010];
int tot;
void insert(char* s)
{
    int u=0;
    char* p=s;
    while(*p)
    {
        int v=*p-'a';
        if(!nodes[u].to[v])
        {
            nodes[u].to[v]=tot;
            memset(nodes+tot, 0, sizeof(Node));
            tot++;
        }
        u=nodes[u].to[v];
        p++;
    }
    nodes[u].count++;
}
char s[1000010];
bool dp[1000010];
void find(int i)
{
    int u=0;
    while(s[i])
    {
        int v=s[i]-'a';
        if(!nodes[u].to[v])return;
        u=nodes[u].to[v];
        if(nodes[u].count)dp[i]=true;
        i++;
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    tot=1;
    int n,m; readi(n,m);
    while(n--)
    {
        reads(s);
        insert(s);
    }
    while(m--)
    {
        reads(s+1);
        int len=strlen(s+1);
        memset(dp,0,sizeof(bool)*(len+4));
        dp[0]=true;
        int ans;
        rep(i,0,len)
        {
            if(dp[i])
            {
                find(i+1);
                ans=i;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}