/**
* Number:ybt1199
* Title:全排列
* Status:AC
* Tag:[dfs]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

char s[100];
int max_dep;
bool vis[100];
char ans[100];
void dfs(int dep)
{
    if (dep == max_dep)
    {
        printf("%s\n", ans);
        return;
    }
    for (int i = 0; i < max_dep; i++)
    {
        if (vis[i])
            continue;
        ans[dep] = s[i];
        vis[i] = true;
        dfs(dep + 1);
        vis[i] = false;
    }
}
int main()
{
    scanf("%s", &s);
    max_dep = strlen(s);
    dfs(0);
    return 0;
}