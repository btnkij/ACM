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
const ll N=1e6;
const ll MOD=1e6+3;
ll a[N+10];
int main() 
{
#ifdef __DEBUG__
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    a[0]=1;
    for(int i=1;i<=N;i++){
        a[i]=a[i-1]*i%MOD;
    }
    int n;
    while(scanf("%d",&n)!=EOF){
        printf("%lld\n",a[n%MOD]);
    }
    return 0;
}