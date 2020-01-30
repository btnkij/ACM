/**
* Number:ybt1367
* Title:查找二叉树(tree_a)
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

struct Node
{
    int value;
    int lc, rc;
} nodes[104];

int key, cnt;
bool found;
void inorder(int root)
{
    if (found || root == 0)
        return;
    inorder(nodes[root].lc);
    if (found)
        return;
    cnt++;
    if (nodes[root].value == key)
    {
        found = true;
        return;
    }
    inorder(nodes[root].rc);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    scanf("%d %d", &n, &key);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d %d", &nodes[i].value, &nodes[i].lc, &nodes[i].rc);
    }
    inorder(1);
    printf("%d\n", cnt);
    return 0;
}