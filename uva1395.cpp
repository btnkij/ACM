/**
 * Number:uva1395
 * Title:Slim Span
 * Status:AC
 * Tag:[mst]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

#ifdef _DEBUG_
#define debug(format, ...) printf(format, __VA_ARGS__)
#define pause system("pause")
#else
#define debug(format, ...)
#define pause
#endif

const int MAX_SIZE=104;
const int INF=0x3f3f3f3f;

struct Edge
{
	int a,b,dist;
	bool operator<(const Edge& rhs)const
	{
		return dist < rhs.dist;
	}
}edges[10004];
int nnode,nedge;

struct Kruskal
{
	///并查集
	int uset[MAX_SIZE];
	int findRoot(int x)
	{
		return x==uset[x] ? x : uset[x]=findRoot(uset[x]);
	}
	///Kruskal
	int operator()(Edge* edges,int ne)
	{
		int i;
		for(i=1;i<=nnode;i++)
			uset[i]=i;
		int n=0;
		for(i=0;i<ne;i++)
		{
			Edge& ed=edges[i];
			int x=findRoot(ed.a);
			int y=findRoot(ed.b);
			if(x!=y)
			{
				uset[x]=y;
				n++;
				if(n==nnode-1)break;
			}
		}
		if(i<ne)return edges[i].dist-edges[0].dist;
		else return -1;
	}
};

Kruskal solver;
int main()
{
	while(scanf("%d %d",&nnode,&nedge)!=EOF)
	{
		if(nnode==0 && nedge==0)break;
		for(int i=0;i<nedge;i++)
		{
			int a,b,d;
			scanf("%d %d %d",&a,&b,&d);
			edges[i]=(Edge){a,b,d};
		}
		sort(edges,edges+nedge);
		int ans=INF;
		for(int i=0;i<=nedge-nnode+1;i++)
		{
			int temp=solver(edges+i,nedge-i);
			if(~temp)ans=min(ans,temp);
		}
		if(ans==INF)printf("-1\n");
		else printf("%d\n",ans);
	}
	pause;
	return 0;
}