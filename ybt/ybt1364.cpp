/**
* Number:ybt1364
* Title:二叉树遍历(flist)
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
char level[200];
int inorder[200];
int ord[200];
void traverse(int left, int right)
{
    if (left >= right)
        return;
    int root = min_element(inorder + left, inorder + right) - inorder;
    putchar(s[root]);
    traverse(left, root);
    traverse(root + 1, right);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%s", s);
    scanf("%s", level);
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        ord[level[i]] = i;
    }
    scanf("%s", s);
    for (int i = 0; i < len; i++)
    {
        inorder[i] = ord[s[i]];
    }
    traverse(0, len);
    return 0;
}