#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

int num[500010];
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int n; scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",num+i);
	int mmax=max(num[0],num[n-1]);
	int mmin=min(num[0],num[n-1]);
	int mid=num[n>>1];
	printf("%d",mmax);
	if(n%2==0)
	{
		mid+=num[(n>>1)-1];
		printf(" %.1f ",(double)mid/2.0);
	}
	else
	{
		printf(" %d ",mid);
	}
	printf("%d",mmin);
	return 0;
}
