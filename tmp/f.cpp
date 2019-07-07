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

char s[100010];
int val[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(s);
    int n=strlen(s);
    repne(i,0,n)val[i]=s[i]=='R'?1:-1;
    int sum=-INF;
    int beg[2],end[2],maxs[2]={-INF,-INF};
    for(int i=n-1;i>=0;i--)
    {
        if(sum>0)sum+=val[i];
        else sum=val[i];
        if(sum>=maxs[0])
        {
            maxs[0]=sum;
            beg[0]=i;
        }
    }
    sum=0;
    for(int i=beg[0];i<n;i++)
    {
        sum+=val[i];
        if(sum==maxs[0])
        {
            end[0]=i;
            break;
        }
    }
    sum=-INF;
    repne(i,0,n)val[i]=-val[i];
    for(int i=n-1;i>=0;i--)
    {
        if(sum>0)sum+=val[i];
        else sum=val[i];
        if(sum>=maxs[1])
        {
            maxs[1]=sum;
            beg[1]=i;
        }
    }
    sum=0;
    for(int i=beg[1];i<n;i++)
    {
        sum+=val[i];
        if(sum==maxs[1])
        {
            end[1]=i;
            break;
        }
    }
    if(maxs[0]>maxs[1] || (maxs[0]==maxs[1] && (beg[0]<beg[1] || beg[0]==beg[1] && end[0]<end[1])))
        printf("%d %d",beg[0]+1,end[0]+1);
    else
        printf("%d %d",beg[1]+1,end[1]+1);
    return 0;
}