/**
* Number:L1-006
* Title:连续因子
* Status:AC
* Tag:[暴力]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <list>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef int ll;

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

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    int st, len=0;
    int ub=(int)sqrt(n)+1;
    for(int i=2;i<=ub;i++)
    {
        if(n%i==0)
        {
            int m=n;
            int len1=0;
            for(int j=i;m%j==0 && j<=ub;j++,len1++)
            {
                m/=j;
            }
            if(len1>len)
            {
                len=len1;
                st=i;
            }
        }
    }
    if(len==0)
    {
        printf("1\n%d",n);
    }
    else
    {
        printf("%d\n",len);
        for(int i=0;i<len;i++)
        {
            if(i)putchar('*');
            printf("%d",st+i);
        }
    }
    return 0;
}