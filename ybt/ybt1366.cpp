/**
* Number:ybt1366
* Title:二叉树输出(btout)
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

char s[200];
int inorder[200];
int ord[200];
int weight[200];
int dfs(int left, int right)
{
    if (left >= right)
        return 0;
    if (left + 1 == right)
        return weight[left] = 1;
    int root = min_element(inorder + left, inorder + right) - inorder;
    weight[root] += dfs(left, root);
    weight[root] += dfs(root + 1, right);
    return weight[root];
}
void rep(char ch, int n)
{
    while (n--)
    {
        putchar(ch);
    }
}
void show(int left, int right)
{
    if (left >= right)
        return;
    int root = min_element(inorder + left, inorder + right) - inorder;
    rep(s[root], weight[root]);
    putchar('\n');
    show(left, root);
    show(root + 1, right);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        ord[s[i]] = i;
    }
    scanf("%s", s);
    for (int i = 0; i < len; i++)
    {
        inorder[i] = ord[s[i]];
    }
    dfs(0, len);
    show(0, len);
    return 0;
}