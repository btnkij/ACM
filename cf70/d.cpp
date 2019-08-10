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

char num1[100010],num7[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clr(num1,'1');
    clr(num7,'7');
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        int mm=(int)sqrt(n+0.5);
        int a,b,tmp=INF;
        for(int i=1;i<=mm;i++)
        {
            if(n%i!=0)continue;
            int j=n/i;
            if(i+j<tmp)
            {
                a=i, b=j, tmp=i+j;
            }
        }
        num1[a]='\0'; num7[b]='\0';
        printf("%s33%s\n",num1,num7);
        num1[a]='1'; num7[b]='7';
    }    
    return 0;
}