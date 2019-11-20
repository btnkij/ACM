/**
* Number:hdu2752
* Title:Seek the Name, Seek the Fame
* Status:AC
* Tag:[kmp]
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

char s[400010];
int nxt[400010];
void init_nxt(int len)
{
    nxt[0]=-1;
    int i=0,j=-1;
    while(i<len)
    {
        if(j==-1 || s[i]==s[j])nxt[++i]=++j;
        else j=nxt[j];
    }
}
vector<int> ans;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(reads(s)!=EOF)
    {
        int len=strlen(s);
        init_nxt(len);
        ans.clear();
        for(int i=len;nxt[i]>0;i=nxt[i])ans.push_back(nxt[i]);
        for(int i=ans.size()-1;i>=0;i--)printf("%d ",ans[i]);
        printf("%d\n",len);
    }
    return 0;
}