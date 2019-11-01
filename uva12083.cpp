/**
* Number:uva12083
* Title:Guardian of Decency
* Status:AC
* Tag:[二分图, hungary, 最大独立集]
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

struct Edge
{
    int from,to,nxt;
}edges[510*510];
int head[510],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int match[510];
bool vis[510];
int dfs(int u)
{
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(vis[v])continue;
        vis[v]=true;
        if(!match[v] || dfs(match[v]))
        {
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

ull hashcode(char* s)
{
    ull ans=0;
    for(char* p=s;*p;p++)ans=ans*131+*p;
    return ans;
}

struct Node
{
    int height;
    char gender[4];
    ull music,sport;
}stu[510];

char s1[110],s2[110];
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
        rep(i,1,n)
        {
            scanf("%d %s %s %s",&stu[i].height,stu[i].gender,s1,s2);
            stu[i].music=hashcode(s1);
            stu[i].sport=hashcode(s2);
        }
        clr(head,-1); edgeid=0;
        rep(i,1,n)
        {
            if(stu[i].gender[0]!='M')continue;
            Node &u=stu[i];
            rep(j,1,n)
            {
                if(i==j)continue;
                Node &v=stu[j];
                if(abs(u.height-v.height)<=40 
                    && u.gender[0]!=v.gender[0]
                    && u.music==v.music
                    && u.sport!=v.sport)
                {
                    addedge(i,j);
                }
            }
        }
        int maxmatch=0;
        clr(match,0);
        rep(i,1,n)
        {
            if(stu[i].gender[0]!='M')continue;
            clr(vis,false);
            maxmatch+=dfs(i);
        }
        printf("%d\n",n-maxmatch);
    }
    return 0;
}