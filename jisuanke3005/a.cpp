#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
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

bool vis[1010][1010];
bool dp[1010][1010];
bool win(int n,int mx)
{
    if(n==0)return false;
    if(vis[n][mx])return dp[n][mx];
    vis[n][mx]=true;
    for(int i=1;i<=mx;i++)
    {
        if(!win(n-i,min(n-1,i*2)))
        {
            return dp[n][mx]=true;
        }
    }
    return dp[n][mx]=false;
}
set<ll> fib;
const ll MAXN=1e15+10;

const int N=20;
ll a[N],m[N];
int n;
void exgcd(ll a,ll b,ll &g,ll &x,ll &y){
    if(!b){
        x=1,y=0;
        g=a;
        return;
    }
    exgcd(b,a%b,g,y,x);
    y-=(a/b)*x;
}
ll excrt(){
    for(int i=1;i<=n;i++)
    {
        if(m[i]<=a[i])
        {
            return -1;
        }
    }
    ll g,x,y;
    ll ans=a[1],M=m[1];//前k-1个解为x,lcm为M
    for(int i=2;i<=n;i++){
        ll A=M,B=m[i],C=(a[i]-ans%B+B)%B;//c为符合条件的正数
        exgcd(A,B,g,x,y);
        if(C%g!=0){
            return -1;//exgcd无解
        }   
        B/=g; 
        x=(x*C/g%B+B)%B;//exgcd的最终最小x
        ans+=x*M;
        M*=B;//前i个的lcm
        ans=(ans%M+M)%M;//取一遍最小正数
    }
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    for(int i=2;i<=1000;i++)
    {
        printf("%d %d\n",i,win(i,max(1,i-1)));
    }
    // fib.insert(2);
    // fib.insert(3);
    // ll fa=2,fb=3,fc;
    // while((fc=fa+fb)<MAXN)
    // {
    //     fib.insert(fc);
    //     // printf("%lld\n",fc);
    //     fa=fb, fb=fc;
    // }
    // while(readi(n)!=EOF)
    // {
    //     rep(i,1,n)scanf("%lld %lld",m+i,a+i);
    //     ll k=excrt();
    //     if(k==1 || k==-1)printf("Tankernb!\n");
    //     else if(fib.count(k))printf("Lbnb!\n");
    //     else printf("Zgxnb!\n");
    // }
    return 0;
}