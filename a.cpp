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

ll gcd(ll a,ll b)
{
    return b==0?a:gcd(b,a%b);
}
ll lcm(ll a,ll b)
{
    return a*b/gcd(a,b);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    rep(kase,1,T)
    {
        // ll a,b,c,L,ans;
        // cin>>a>>b>>L;
        // ll d=lcm(a,b);
        // ll g=gcd(a,b);
        // bool flag=true;
        // if(L%d!=0)
        // {
        //     flag=false;
        // }
        // else
        // {
        //     // ans=L*L/d/lcm(d,L/d);
        //     ll t=L/d;
        //     ans = t * gcd(d,t);
        //     flag=true;
        // }
        // printf("Case %d: ",kase);
        // if(!flag)printf("impossible\n");
        // else cout<<ans<<endl;
        int flag=0;
        ll a,b,c,L,ans;
        scanf("%lld %lld %lld",&a,&b,&L);
        ll d=lcm(a,b),e=gcd(a,b);
        ll res=L/d;
        for(ll i=res;i<=L;i+=res){
            ll lab=e;
            if(i%d==0){
                lab=d;
            }
            if(lab*L==i*d){
                flag=1;
                ans=i;
                break;
            }
        }
        printf("Case %d: ",kase);
        if(!flag)printf("impossible\n");
        else printf("%lld\n",ans);
    }
    return 0;
}