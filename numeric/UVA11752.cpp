/**
* Number:UVA11752
* Title:The Super Powers
* Status:AC
* Tag:[数论, 质数]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_set>
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

int nonprime[]={4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 
    24, 25, 26, 27, 28, 30, 32, 33, 34, 35, 36, 38, 39, 40, 42, 
    44, 45, 46, 48, 49, 50, 51, 52, 54, 55, 56, 57, 58, 60, 62, 63};
ull a[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n=1;
    a[0]=1;
    unordered_set<ull> S;
    for(ull i=2;i<1<<16;i++)
    {
        ull i2=i*i;
        int mm=(int)ceil((64*log(2)/log(i)))-1;
        ull t=1;
        int p=0;
        for(int j=0;j<=44 && nonprime[j]<=mm;j++)
        {
            for(;p<nonprime[j];p++)t*=i;
            if(!S.count(t))
            {
                a[n++]=t;
                S.insert(t);
            }
        }
    }
    sort(a,a+n);
    repne(i,0,n)printf("%llu\n",a[i]);
    return 0;
}
