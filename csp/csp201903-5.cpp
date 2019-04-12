#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

struct Edge
{
	int from,to,dist;
}edges[20010];
int head[10010],nxt[10010],tot;
void add_edge(int from,int to,int dist)
{
	Edge& e=edges[tot];
	e.from=from, e.to=to, e.dist=dist;
	nxt[tot]=head[from];
	head[from]=tot++;
}

struct Node
{
	int u,cost;
	bool operator<(const Node& rhs)const
	{
		return cost>rhs.cost;
	}
};
int dis[10010][110],tail[10010];
bool vis2[10010][110],*vis;
void dijkstra(int src)
{
	priority_queue<Node> Q;
	Q.push((Node){src,0});
	while(!Q.empty())
	{
		Node node=Q.top(); Q.pop();
		if(vis[node.u])continue;
		vis[node.u]=true;
		dis[node.u][tail[node.u]++]=node.cost;
		//printf("%d->%d %d\n",src,node.u,node.cost);
		for(int i=head[node.u];~i;i=nxt[i])
		{
			Edge& e=edges[i];
			if(vis[e.to])continue;
			Q.push((Node){e.to, node.cost+e.dist});
		}
	}
}

bool safe[10010];
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int n,m,k; scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		head[i]=-1;
		int t; scanf("%d",&t);
		safe[i]=(t==1);
	}
	for(int i=0;i<m;i++)
	{
		int u,v,w; scanf("%d %d %d",&u,&v,&w);
		//printf("%d %d %d\n",u,v,w);
		add_edge(u,v,w); add_edge(v,u,w);
	}
	for(int i=1;i<=n;i++)
	{
		if(!safe[i])continue;
		vis=vis2[i];
		dijkstra(i);
	}
	for(int i=1;i<=n;i++)
	{
		int cnt=tail[i];
		int sum=0;
		int *pdis=dis[i];
		if(cnt>k)sort(pdis,pdis+cnt);
		for(int i=0;i<k;i++)sum+=pdis[i];
		printf("%d\n",sum);
	}
	return 0;
}
