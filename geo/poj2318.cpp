/**
* Number:poj2318
* Title:TOYS
* Status:AC
* Tag:[计算几何, 点与直线的位置关系]
**/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN=5004;
int a[MAXN],b[MAXN],c[MAXN];
struct Line
{
	int Px,Py;
	int vx,vy;
};
inline int OnLine(int x,int y,const Line& line)
{
	return line.vx*(y-line.Py)-line.vy*(x-line.Px);
}
Line line[MAXN];
int cnt[MAXN];
int main()
{
	int n,m,x_1,y_1,x_2,y_2;
	int U,L;
	while(scanf("%d",&n),n)
	{
		scanf("%d %d %d %d %d",&m,&x_1,&y_1,&x_2,&y_2);
		line[0].Px=x_1-1;line[0].Py=y_1;
		line[0].vx=0;line[0].vy=1;
		line[n+1].Px=x_2+1;line[n+1].Py=y_2;
		line[n+1].vx=0;line[n+1].vy=1;
		for(int i=1;i<=n;i++)
		{
			scanf("%d %d",&U,&L);
			line[i].Px=U;line[i].Py=y_1;
			line[i].vx=L-U;line[i].vy=y_2-y_1;
		}
		memset(cnt,0,sizeof(cnt));
		int x,y;
		while(m--)
		{
			scanf("%d %d",&x,&y);
			int lt=0,rt=n+1;
			while(rt-lt>1)
			{
				int mid=(lt+rt)/2;
				if(OnLine(x,y,line[mid])<0)rt=mid;
				else lt=mid;
			}
			cnt[lt]++;
		}
		for(int i=0;i<=n;i++)
		{
			printf("%d: %d\n",i,cnt[i]);
		}
		printf("\n");
	}
	#ifdef _DEBUG_
	system("pause");
	#endif
	return 0;
}