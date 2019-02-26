/**
* Number:ybt1339
* Title:求后序遍历
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

char s[30];
int inorder[30];
int ord[30];
void traverse(int left, int right)
{
    if (left >= right)
        return;
    else if (left + 1 == right)
    {
        putchar(s[left]);
        return;
    }
    int root = min_element(inorder + left, inorder + right) - inorder;
    traverse(left, root);
    traverse(root + 1, right);
    putchar(s[root]);
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
        ord[s[i] - 'a'] = i;
    }
    scanf("%s", s);
    for (int i = 0; i < len; i++)
    {
        inorder[i] = ord[s[i] - 'a'];
    }
    traverse(0, len);
    return 0;
}