#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

char expr[100];
vector<int> num;
vector<char> opt;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int T; scanf("%d",&T);
	while(T--)
	{
		num.clear();
		opt.clear();
		scanf("%s",expr);
		int len=strlen(expr);
		for(int i=0;i<len;i++)
		{
			if('0'<=expr[i] && expr[i]<='9')
			{
				num.push_back(expr[i]&0xF);
			}
			else if(expr[i]=='+' || expr[i]=='-' || expr[i]=='x' || expr[i]=='/')
			{
				opt.push_back(expr[i]);
			}
		}
		while(opt.size()>0)
		{
			int idx=-1;
			char ch;
			for(int i=0;i<opt.size();i++)
			{
				if(idx==-1)
				{
					ch=opt[i];
					idx=i;
				}
				else if((ch=='+' || ch=='-') && (opt[i]=='x' || opt[i]=='/'))
				{
					ch=opt[i];
					idx=i;
					break;
				}
			}
			opt.erase(opt.begin()+idx);
			int ans;
			switch(ch)
			{
				case '+':
					ans=num[idx]+num[idx+1];
					break;
				case '-':
					ans=num[idx]-num[idx+1];
					break;
				case 'x':
					ans=num[idx]*num[idx+1];
					break;
				case '/':
					ans=num[idx]/num[idx+1];
					break;
			}
			num[idx+1]=ans;
			num.erase(num.begin()+idx);
		}
		if(num[0]==24)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
