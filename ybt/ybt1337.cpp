/**
* Number:ybt1337
* Title:单词查找树
* Status:?
* Tag:[trie, 字典树]
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
    int next[26];
} trie[40000];
int tot;
char s[100];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    tot = 1;
    while (cin >> s)
    {
        int node = 0;
        for (char *p = s; *p != '\0'; p++)
        {
            if (trie[node].next[*p - 'A'])
            {
                node = trie[node].next[*p - 'A'];
            }
            else
            {
                trie[node].next[*p - 'A'] = tot;
                node = tot;
                tot++;
            }
        }
    }
    printf("%d\n", tot);
    return 0;
}