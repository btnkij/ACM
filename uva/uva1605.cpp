/**
* Number:uva1605
* Title:Building for UN
* Status:WA
* Tag:[构造]
**/

//Why WA
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

char alphabet[80];
char ans[1000010];
int main()
{
    for (int i = 0; i < 26; i++)
        alphabet[i] = 'A' + i;
    for (int i = 0; i < 26; i++)
        alphabet[i + 26] = 'a' + i;
    int n;
    while (scanf("%d", &n) != EOF)
    {
        char *p = ans;
        int l = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                *p = alphabet[i];
                p++;
                *p = alphabet[j];
                p++;
                *p = '\n';
                p++;
                l++;
            }
        }
        *p = '\0';
        printf("1 2 %d\n", l);
        printf("%s\n", ans);
    }
    return 0;
}