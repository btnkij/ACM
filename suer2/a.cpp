#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pi acos(-1)
const int inf=0x3f3f3f3f;
const int N=1e5+5;
const ll MOD=1e9+7;
ll dp[2][N];
char s[N],t[305];
ll num[30],sum[N],lastsum[N];
int main() 
{
#ifdef __DEBUG__
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int tlen,slen;
    scanf("%d%d",&tlen,&slen);
    for(int i=0;i<26;i++){
        scanf("%lld",&num[i]);
    }
    scanf("%s%s",t+1,s+1);
    memset(dp,0,sizeof(dp));
    memset(sum,0,sizeof(sum));
    memset(lastsum,0,sizeof(lastsum));
    ll ans=0;
    int tmp=1;
    for(int i=1;i<=tlen;i++){
        tmp^=1;
        for(int j=1;j<=slen;j++){
            if(i==1){
                if(t[i]==s[j]){
                    dp[tmp][j]=1;
                }else{
                    dp[tmp][j]=0;
                }
            }else{
                if(t[i]==s[j]&&j-1-num[t[i-1]-'A']>0){
                    dp[tmp][j]=lastsum[j-1-num[t[i-1]-'A']];
                }else{
                    dp[tmp][j]=0;
                }
            }
            sum[j]=(sum[j-1]+dp[tmp][j])%MOD;
        }     
        copy(sum+1,sum+1+slen,lastsum+1);
        memset(sum,0,sizeof(sum));
        if(i==tlen){
            for(int j=tlen;j<=slen;j++){
                ans=(ans+dp[tmp][j])%MOD;
            }
        }
    }
    printf("%lld\n",ans%MOD);
    return 0;
}
