#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
using namespace std;

queue<string> ins[10010];
bool vis[10010];
bool dfs(int pre, int pid, int response) // response 0 send 1 receive
{
	if(ins[pid].empty() || vis[pid])return false;
	vis[pid]=true;
	string evt=ins[pid].front();
	ins[pid].pop();
	int act=evt[0]=='S'?0:1;
	int tar=atoi(evt.c_str()+1);
	//printf("pre=%d pid=%d res=%d\n",pre,pid,response);
	//cout<<evt<<endl;
	//printf("act=%d tar=%d\n",act,tar);
	bool flag;
	if(response==-1)
	{
		flag=dfs(pid, tar, act^1);
	}
	else if(act==response && tar==pre)
	{
		flag=true;
	}
	else
	{
		flag=false;
		while(!ins[pid].empty() && dfs(pid, tar, act^1))
		{
			if(ins[pid].empty())
			{
				break;
			}
			evt=ins[pid].front();
			ins[pid].pop();
			act=evt[0]=='S'?0:1;
			tar=atoi(evt.c_str()+1);
			if(act==response && tar==pre)
			{
				flag=true;
				break;
			}
		}
	}
	vis[pid]=false;
	return flag;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int T,n; scanf("%d %d",&T,&n);
	string s;
	getline(cin,s);
	while(T--)
	{
		for(int i=0;i<n;i++)
		{
			while(!ins[i].empty())ins[i].pop();
			getline(cin,s);
			stringstream ss(s);
			string evt;
			while(ss>>evt)
			{
				ins[i].push(evt);
			}
		}
		bool flag=true;
		for(int i=0;i<n;i++)
		{
			while(!ins[i].empty() && flag)
			{
				flag=dfs(-1,i,-1);
			}
			if(!flag)break;
		}
		printf("%d\n",flag?0:1);
	}
	return 0;
}
