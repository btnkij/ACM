/**
* Number:ybt1396
* Title:病毒(virus)
* Status:AC
* Tag:[拓扑排序]
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

struct Edge
{
    int from,to;
}edges[160];
int head[30],nxt[160],tot;
int deg[30];
void add_edge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
    deg[to]++;
}

int sorted[30];
bool ok,vis[30];
void dfs(int u)
{
    int& ord=sorted[u];
    ord=0;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(ok)dfs(v);
        if(!ok)return;
        ord=max(ord,sorted[v]+1);
    }
    if(vis[ord])ok=false;
    vis[ord]=true;
}

bool adj[30][30];
char buf1[5000],buf2[5000];
bool alphabet[30];
int trans[30],tail;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    char *cur=buf1, *pre=buf2;
    repne(k,0,n)
    {
        reads(cur);
        for(char* p=cur;*p!='\0';p++)
            alphabet[*p-'a']=true;
        if(k)
        {
            for(int i=0;cur[i]!='\0' && pre[i]!='\0';i++)
            {
                if(cur[i]!=pre[i])
                {
                    adj[pre[i]-'a'][cur[i]-'a']=true;
                    break;
                }
            }
        }
        swap(cur,pre);
    }
    repne(i,0,26)
    {
        if(alphabet[i])
        {
            trans[tail++]=i;
        }
    }
    mset(head,-1);
    repne2(i,0,26,j,0,26)
        if(adj[i][j])
            add_edge(i,j);
    int src=-1;
    repne(i,0,26)
    {
        if(alphabet[i] && !deg[i])
        {
            src=i;
            break;
        }
    }
    ok=(src!=-1);
    if(ok)
    {
        mset(sorted,-1);
        dfs(src);
    }
    if(ok)
    {
        int cnt=0;
        repne(i,0,26)
            if(~sorted[i])
                cnt++;
        ok=(cnt==tail);
    }
    if(ok)
    {
        reads(buf1);
        for(char* p=buf1;*p!='\0';p++)
        {
            if(sorted[*p]==-1)
            {
                ok=false;
                break;
            }
            *p=trans[sorted[*p]];
        }
    }
    if(ok)printf(buf1);
    else printf("0");
    return 0;
}