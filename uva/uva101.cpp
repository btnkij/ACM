/**
* Number:uva101
* Title:The Blocks Problem
* Status:AC
* Tag:[模拟, vector]
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

vector<int> st[30];
int pos[30];
void returnback(int x)
{
    auto& stx=st[pos[x]];
    for(int i=stx.size()-1;stx[i]!=x;i--)
    {
        int j=stx[i];
        if(j==pos[x])continue;
        st[j].push_back(pos[j]=j);
        stx.erase(stx.begin()+i);
    }
}
void pileover(int x,int y)
{
    auto& stx=st[pos[x]];
    int i=find(stx.begin(),stx.end(),x)-stx.begin();
    for(int j=i;j<stx.size();j++)
    {
        pos[stx[j]]=pos[y];
        st[pos[y]].push_back(stx[j]);
    }
    stx.erase(stx.begin()+i,stx.end());
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF)
    {
        repne(i,0,n)
        {
            st[i].clear();
            st[i].push_back(pos[i]=i);
        }
        int a,b; char s1[8],s2[8];
        while(reads(s1)!=EOF && s1[0]!='q')
        {
            scanf("%d %s %d",&a,s2,&b);
            if(pos[a]==pos[b])continue;
            if(s1[0]=='m' && s2[1]=='n') // move a onto b
            {
                returnback(a);
                returnback(b);
                pileover(a,b);
            }
            else if(s1[0]=='m' && s2[1]=='v') // move a over b
            {
                returnback(a);
                pileover(a,b);
            }
            else if(s1[0]=='p' && s2[1]=='n') // pile a onto b
            {
                returnback(b);
                pileover(a,b);
            }
            else if(s1[0]=='p' && s2[1]=='v') // pile a over b
            {
                pileover(a,b);
            }
        }
        repne(i,0,n)
        {
            printf("%d:", i);
            repne(j,0,st[i].size())
            {
                printf(" %d",st[i][j]);
            }
            puts("");
        }
    }
    return 0;
}