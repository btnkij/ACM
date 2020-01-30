#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f

int leftmost,rightmost;
int sum[200];
void solve(int index)
{
    int n;
    scanf("%d",&n);
    if(n==-1)return;
    leftmost=min(leftmost,index);
    rightmost=max(rightmost,index);
    sum[index]+=n;
    solve(index-1);
    solve(index+1);
}

int main()
{
    int kase=1;
    int n;
    while(scanf("%d",&n)!=EOF && n!=-1)
    {
        memset(sum,0,sizeof(sum));
        leftmost=rightmost=100;
        sum[100]=n;
        solve(99);
        solve(101);
        printf("Case %d:\n",kase++);
        for(int i=leftmost;i<=rightmost;i++)
        {
            if(i>leftmost)putchar(' ');
            printf("%d",sum[i]);
        }
        printf("\n\n");
    }
    return 0;
}