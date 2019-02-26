/**
* Number:ybt1340
* Title:扩展二叉树
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
    char value;
    int lc, rc;
} nodes[100];
int cntn;

char s[100];
int p;
void build_tree()
{
    int nid = cntn++;
    nodes[nid].value = s[p];
    p++;
    if (s[p] != '.')
    {
        nodes[nid].lc = cntn;
        build_tree();
    }
    p++;
    if (s[p] != '.')
    {
        nodes[nid].rc = cntn;
        build_tree();
    }
}

void inorder(int root)
{
    if (root == 0)
        return;
    inorder(nodes[root].lc);
    putchar(nodes[root].value);
    inorder(nodes[root].rc);
}
void postorder(int root)
{
    if (root == 0)
        return;
    postorder(nodes[root].lc);
    postorder(nodes[root].rc);
    putchar(nodes[root].value);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    cntn = 1;
    scanf("%s", s);
    p = 0;
    build_tree();
    inorder(1);
    putchar('\n');
    postorder(1);
    return 0;
}