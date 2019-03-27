/**
* Number:L1-002
* Title:打印沙漏
* Status:AC
* Tag:[]
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

char ch[4]; 
void show(int n,int k)
{
    int sp=(k-n)/2;
    repne(i,0,sp)putchar(' ');
    repne(i,0,n)putchar(ch[0]);
    // repne(i,0,sp)putchar(' ');
    putchar('\n');
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    reads(ch);
    n--;
    int k=3;
    while(n-k*2>=0)
    {
        n-=k*2;
        k+=2;
    }
    k-=2;
    for(int i=k;i>=3;i-=2)
    {
        show(i,k);
    }
    show(1,k);
    for(int i=3;i<=k;i+=2)
    {
        show(i,k);
    }
    printf("%d",n);
    return 0;
}