#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f

int nRow,nCol;
struct Node
{
    char s[80];
    bool solvable;
    int value;
};
const int MAXR=22,MAXC=12;
Node sheet[MAXR][MAXC];
bool vis[MAXR][MAXC];

bool solve(int x,int y)
{
    Node& node=sheet[x][y];
    if(vis[x][y])return node.solvable;
    vis[x][y]=true;
    int ans=0;
    int sign=1;
    char* p=node.s;
    while(*p!='\0')
    {
        if(*p=='+')
        {
            sign=1;
            p++;
        }
        else if(*p=='-')
        {
            sign=-1;
            p++;
        }
        else if('A'<=*p && *p<='Z')
        {
            int xx=*p-'A';
            int yy=*(p+1)-'0';
            if(!solve(xx,yy))return node.solvable=false;
            ans+=sign*sheet[xx][yy].value;
            p+=2;
        }
        else
        {
            int tmp=0;
            while('0'<=*p && *p<='9')
            {
                tmp=tmp*10+(*p&0xF);
                p++;
            }
            ans+=sign*tmp;
        }
    }
    node.value=ans;
    return node.solvable=true;
}
int main()
{
    while(scanf("%d %d",&nRow,&nCol)!=EOF && nRow && nCol)
    {
        memset(sheet,0,sizeof(sheet));
        memset(vis,false,sizeof(vis));
        for(int x=0;x<nRow;x++)
        {
            for(int y=0;y<nCol;y++)
            {
                scanf("%s",sheet[x][y].s);
            }
        }
        bool flag=true;
        for(int x=0;x<nRow;x++)
        {
            for(int y=0;y<nCol;y++)
            {
                flag = solve(x,y) && flag;
            }
        }
        if(flag)
        {
            putchar(' ');
            for(int y=0;y<nCol;y++)
            {
                printf("%6d",y);
            }
            putchar('\n');
            for(int x=0;x<nRow;x++)
            {
                printf("%c",x+'A');
                for(int y=0;y<nCol;y++)
                {
                    printf("%6d",sheet[x][y].value);
                }
                putchar('\n');
            }
        }
        else
        {
            for(int x=0;x<nRow;x++)
            {
                for(int y=0;y<nCol;y++)
                {
                    if(!sheet[x][y].solvable)
                    {
                        printf("%c%c: ",x+'A',y+'0');
                        printf("%s\n",sheet[x][y].s);
                    }
                }
            }
        }
        putchar('\n');
    }
    return 0;
}