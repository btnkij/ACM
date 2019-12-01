/**
* Number:poj1979
* Title:Red and Black
* Status:AC
* Tag:[dfs]
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
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int dir[][2]={{1,0},{-1,0},{0,-1},{0,1}};
char maze[24][24];
int cnt;
void dfs(int x,int y)
{
	if(maze[x][y]!='.')return;
	maze[x][y]='#';
	cnt++;
	for(int i=0;i<4;i++)
	{
		dfs(x+dir[i][0],y+dir[i][1]);
	}
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int w,h;
	while(scanf("%d %d",&w,&h),w&&h)
	{
		memset(maze,0,sizeof(maze));
		int srcx,srcy;
		for(int i=1;i<=h;i++)
		{
			scanf("%s",maze[i]+1);
			for(int j=1;j<=w;j++)
			{
				if(maze[i][j]=='@')
				{
					srcx=i;srcy=j;
					maze[i][j]='.';
					break;
				}
			}
		}
		cnt=0;
		dfs(srcx,srcy);
		printf("%d\n",cnt);
	}
    return 0;
}