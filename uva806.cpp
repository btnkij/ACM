#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f

int width;
char mp[80][80];
vector<int> v,ans;
int CountBlack(int x,int y,int width)
{
    int endx=x+width,endy=y+width;
    int cnt=0;
    for(int i=x; i<endx; i++)
    {
        for(int j=y; j<endy; j++)
        {
            if(mp[i][j]=='1')cnt++;
        }
    }
    return cnt;
}
void Dfs(int x,int y,int width)
{
    // printf("x=%d y=%d width=%d\n",x,y,width);
    if(width==0)return;
    int cnt=CountBlack(x,y,width);
    if(!cnt)return;
    if(cnt==width*width)
    {
        int tmp=0;
        for(int i=v.size()-1; i>=0; i--)
        {
            tmp=tmp*5+v[i];
        }
        ans.push_back(tmp);
        return;
    }
    width>>=1;
    v.push_back(1); Dfs(x,y,width); v.pop_back();
    v.push_back(2); Dfs(x,y+width,width); v.pop_back();
    v.push_back(3); Dfs(x+width,y,width); v.pop_back();
    v.push_back(4); Dfs(x+width,y+width,width); v.pop_back();
    // printf("exit\n");
}
int FillBlack(int x,int y,int width)
{
    int endx=x+width,endy=y+width;
    for(int i=x; i<endx; i++)
    {
        for(int j=y; j<endy; j++)
        {
            mp[i][j]='*';
        }
    }
}
int main()
{
    int kase=1;
    while(scanf("%d",&width)!=EOF && width)
    {
        printf("Image %d\n",kase++);
        if(width>0)
        {
            ans.clear();
            v.clear();
            memset(mp,'0',sizeof(mp));
            for(int i=0;i<width;i++)scanf("%s",mp[i]);
            Dfs(0,0,width);
            if(ans.size())
            {
                sort(ans.begin(),ans.end());
                for(int i=0;i<ans.size();i++)
                {
                    if(i && i%12==0)putchar('\n');
                    else if(i)putchar(' ');
                    printf("%d",ans[i]);
                }
                putchar('\n');
            }
            printf("Total number of black nodes = %d\n",ans.size());
        }
        else
        {
            width=-width;
            memset(mp,'.',sizeof(mp));
            int t;
            while(scanf("%d",&t)!=EOF && ~t)
            {
                int x=0,y=0,w=width;
                while(t)
                {
                    w>>=1;
                    switch(t%5)
                    {
                        case 1:break;
                        case 2:y+=w;break;
                        case 3:x+=w;break;
                        case 4:x+=w;y+=w;break;
                    }
                    t/=5;
                }
                FillBlack(x,y,w);
            }
            for(int i=0;i<width;i++)
            {
                for(int j=0;j<width;j++)
                {
                    putchar(mp[i][j]);
                }
                putchar('\n');
            }
        }
        putchar('\n');
    }
    return 0;
}