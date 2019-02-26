/**
 * Number:noi1750
 * Title:全排列 
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
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

char s[8],perm[8];
bool vis[128];
int len;

void dfs(int n)
{
    if(n==len)
    {
        printf("%s\n",perm);
        return;
    }
    for(int i=0;i<len;i++)
    {
        if(!vis[s[i]])
        {
            vis[s[i]]=true;
            perm[n]=s[i];
            dfs(n+1);
            vis[s[i]]=false;
        }
    }
}

int main()
{
    scanf("%s",s);
    len=strlen(s);
    dfs(0);
    return 0;
}