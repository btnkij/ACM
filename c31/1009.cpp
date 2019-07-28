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

vector<int> pos[30];
char s[300010];
int l[30],r[30];
bool vis[300010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(scanf("%s",s)!=EOF)
    {
        int k;readi(k);
        repne(i,0,26)
        {
            readi(l[i],r[i]);
            pos[i].clear();
        }
        int len=strlen(s);
        if(k>len)
        {
            printf("-1\n");
            continue;
        }
        repne(i,0,len)
        {
            pos[s[i]-'a'].push_back(i);
            vis[i]=false;
        }
        int del=len-k;
        bool ok=true;
        repne(i,0,26)
        {
            while(pos[i].size()>r[i] && del>0)
            {
                pos[i].pop_back();
                del--;
            }
            if(pos[i].size()>r[i] || pos[i].size()<l[i])
            {
                ok=false;
                break;
            }
        }
        if(!ok)
        {
            printf("-1\n");
            continue;
        }
        for(int i=25;i>=0;i--)
        {
            while(pos[i].size()>l[i] && del>0)
            {
                pos[i].pop_back();
                del--;
            }
        }
        repne(i,0,26)
        {
            for(int j:pos[i])
            {
                vis[j]=true;
            }
        }
        repne(i,0,len)
        {
            if(vis[i])putchar(s[i]);
        }
        puts("");
    }
    return 0;
}