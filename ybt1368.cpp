/**
* Number:ybt1368
* Title:对称二叉树(tree_c)
* Status:AC
* Tag:[二叉树]
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

char s[1000];
bool ans;
void sym(int root)
{
    if (!ans || s[root] == '#')
        return;
    int lc = root << 1;
    int rc = lc | 1;
    ans = ans && ((s[lc] == '#' && s[rc] == '#') || (s[lc] != '#' && s[rc] != '#'));
    // printf("%d %d\n", root, ans);
    sym(lc);
    sym(rc);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    memset(s, '#', sizeof(s));
    scanf("%s", s + 1);
    s[strlen(s)] = '#';
    ans = true;
    sym(1);
    printf("%s\n", ans ? "Yes" : "No");
    return 0;
}