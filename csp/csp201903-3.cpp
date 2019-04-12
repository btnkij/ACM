#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

int toInt(char ch)
{
	if('0'<=ch && ch<='9')return ch&0xF;
	else return ch-'A'+10;
}
void printHex(unsigned x)
{
	for(int i=0;i<8;i++)
	{
		unsigned low=(x&0xF0000000u)>>28;
		x<<=4;
		if(low<10)putchar(0x30|low);
		else putchar('A'-10+low);
	}
}

unsigned data[1010][10250];
bool valid[1010];
char s[40*(1<<10)*2+10];
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int n,sz,L; scanf("%d %d %d",&n, &sz, &L);
	for(int i=0;i<L;i++)
	{
		int t; scanf("%d",&t);
		valid[t]=true;
		scanf("%s",s);
		int b=0;
		for(char* p=s;*p;p+=8,b++)
		{
			unsigned& ans=data[t][b];
			for(int k=0;k<8;k++)
			{
				ans=(ans<<4)|toInt(*(p+k));
			}
		}
	}
	int nblock=strlen(s)>>3;
	int maxn=nblock*(n-1)-1;
	//printf("maxn=%d\n",maxn);
	int m; scanf("%d",&m);
	while(m--)
	{
		int id; scanf("%d",&id);
		if(id<0 || id>maxn)printf("-");
		else
		{
			int line=id/((n-1)*sz);
			int sta=((n-1-line)%n+n+1)%n;
			int disk=(sta+id/sz-line*(n-1))%n;
			int offset=line*sz+id%sz;
			//printf("line=%d sta=%d disk=%d offset=%d\n",line,sta,disk,offset);
			if(valid[disk])
			{
				printHex(data[disk][offset]);
			}
			else
			{
				unsigned ans=0;
				int cnt=0;
				for(int i=0;i<n;i++)
				{
					if(valid[i])
					{
						ans^=data[i][offset];
						cnt++;
					}
				}
				if(cnt==n-1)printHex(ans);
				else printf("-");
			}
		}
		printf("\n");
	}
	return 0;
}
