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
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

bool vis[100010];
char s[100010];
int len;
bool check(int st,int k)
{
    int i=st;
    do
    {
        if(s[i]=='P')return false;
        i=(i+k)%len;
    }while(i!=st);
    return true;
}
int gcd(int a,int b)
{
    return b==0 ? a : gcd(b,a%b);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(reads(s)!=EOF)
    {
        len=strlen(s);
        for(int i=1;i<len;i++)
        {
            if(len%i)continue;
            for(int j=0;j<i;j++)
            {
                if(check(j,i))
                {
                    vis[i]=true;
                    break;
                }
            }
        }
        int ans=0;
        repne(i,1,len)ans+=vis[gcd(len,i)];
        printf("%d\n",ans);
    }
    return 0;
}