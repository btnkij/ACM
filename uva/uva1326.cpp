/**
* Number:uva1326
* Title:Jurassic Remains
* Status:AC
* Tag:[meet-in-the-mid]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <unordered_map>
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

int a[30];
unordered_map<int,int> mid;
char s[1010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF)
    {
        clr(a,0);
        repne(i,0,n)
        {
            reads(s);
            int len=strlen(s);
            repne(j,0,len)
            {
                a[i]^=1<<(s[j]-'A');
            }
        }
        mid.clear();
        int n1=n>>1, n2=n-n1;
        repne(i,0,1<<n1)
        {
            int sum=0;
            repne(j,0,n1)
            {
                if(i&(1<<j))sum^=a[j];
            }
            if(!mid.count(sum) || __builtin_popcount(mid[sum])<__builtin_popcount(i))mid[sum]=i;
        }
        int ans=mid[0];
        int mask=(1<<n1)-1;
        repne(i,0,1<<n2)
        {
            int sum=0;
            repne(j,0,n2)
            {
                if(i&(1<<j))sum^=a[n1+j];
            }
            if(mid.count(sum) && __builtin_popcount(ans)<__builtin_popcount(mid[sum])+__builtin_popcount(i))
            {
                ans=mid[sum]|(i<<n1);
            }
        }
        printf("%d\n",__builtin_popcount(ans));
        repne(i,0,n)
            if(ans&(1<<i))
                printf("%d ",i+1);
        puts("");
    }
    return 0;
}