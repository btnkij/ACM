/**
* Number:uva1149
* Title:Bin Packing
* Status:AC
* Tag:[greedy]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

int items[100004];
int main()
{
    int T; scanf("%d",&T);
    while(T--)
    {
        int n,L;
        scanf("%d %d",&n,&L);
        for(int i=0;i<n;i++)scanf("%d",items+i);
        sort(items,items+n);
        int lt=0,rt=n-1;
        int ans=0;
        while(lt<rt)
        {
            if(items[rt]+items[lt]<=L)rt--,lt++;
            else rt--;
            ans++;
        }
        if(lt==rt)ans++;
        printf("%d\n",ans);
        if(T)printf("\n");
    }
    return 0;
}