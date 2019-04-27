/**
* Number:loj2012
* Title:「SCOI2016」背单词 
* Status:AC
* Tag:[trie, 贪心]
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

struct
{
    int end;
    int to[26];
}trie[510010];
int tot;
void insert(char* s,int len)
{
    int u=0;
    for(int i=len-1;i>=0;i--)
    {
        int& v=trie[u].to[s[i]-'a'];
        if(!v)v=tot++;
        u=v;
    }
    trie[u].end++;
}

struct Node
{
    int rk;
    vector<int> adj;
}nodes[510010];
void build(int u, int pre)
{
    if(trie[u].end)
    {
        nodes[pre].adj.push_back(u);
        // printf("edge %d %d\n",pre,u);
        pre=u;
        nodes[u].rk=1;
    }
    for(int i=0;i<26;i++)
    {
        int v=trie[u].to[i];
        if(v)
        {
            build(v, pre);
            nodes[u].rk+=nodes[v].rk;
        }
    }
    // printf("rank %d %d\n",u,nodes[u].rk);
}

int timer;
ll ans;
void dfs(int u, int pre)
{
    ans+=timer-pre;
    pre=timer++;
    sort(nodes[u].adj.begin(), nodes[u].adj.end(), [](int lhs, int rhs){
        return nodes[lhs].rk < nodes[rhs].rk;
    });
    for(int v:nodes[u].adj)
    {
        dfs(v, pre);
    }
}

char s[510010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    tot=1;
    while(n--)
    {
        reads(s);
        int len=strlen(s);
        insert(s,len);
    }
    build(0,0);
    dfs(0,0);
    printf("%lld",ans);
    return 0;
}