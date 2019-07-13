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

ull qpow(ull x,ull p)
{
    ull ans=1;
    ull tmp=x;
    while(p)
    {
        if(p&1)ans*=tmp;
        tmp*=tmp;
        p>>=1;
    }
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ull a,b,c,n; 
    while(cin>>a>>b>>c>>n)
    {
        if(n<=2)
        {
            cout<<0<<endl;
        }
        else
        {
            int eq=0;
            if(a==b)eq++;
            if(b==c)eq++;
            if(b==c)eq++;
            ull ans=qpow(n,n)-n;
            int mm=(n+1)/2;
            if(mm>=2)ans-=n*(3*(2+mm)*(mm-1)-6*(mm-1));
            if(eq==1)ans/=2;
            else if(eq==3)ans/=6;
            cout<<ans<<endl;
        }
    }
    return 0;
}