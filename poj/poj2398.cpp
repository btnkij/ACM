/**
* Number:poj2398
* Title:Toy Storage
* Status:AC
* Tag:[计算几何, 点与直线的位置关系]
**/

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

const int MAXN=5004;
int a[MAXN],b[MAXN],c[MAXN];
struct Line
{
	int Px,Py;
	int vx,vy;
    bool operator<(const Line& rhs)const
    {
        return Px < rhs.Px;
    }
};
inline int OnLine(int x,int y,const Line& line)
{
	return line.vx*(y-line.Py)-line.vy*(x-line.Px);
}
Line line[MAXN];
int cnt[MAXN],ans[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
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
        sort(line, line+n+2);
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
        mset(ans,0);
        for(int i=0;i<=n;i++)ans[cnt[i]]++;
        printf("Box\n");
		for(int i=1;i<=n;i++)
		{
            if(ans[i]==0)continue;
			printf("%d: %d\n",i,ans[i]);
		}
	}
	#ifdef _DEBUG_
	system("pause");
	#endif
	return 0;
}