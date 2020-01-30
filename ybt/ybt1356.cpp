/**
* Number:ybt1356
* Title:计算(calc)
* Status:AC
* Tag:[递归下降]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef long long ll;

int find_rbracket(string s, int left)
{
    int cnt = 1;
    int right = left + 1;
    while (cnt > 0)
    {
        if (s[right] == '(')
            cnt += 1;
        else if (s[right] == ')')
            cnt -= 1;
        right += 1;
    }
    return right;
}

bool contained(char ch, const char *S)
{
    while (*S != '\0')
    {
        if (ch == *S)
            return true;
        S++;
    }
    return false;
}

int find_least_prior_op(const string &s)
{
    int ind_op = -1;
    int i = 0;
    while (i < s.length())
    {
        if (s[i] == '(')
        {
            i = find_rbracket(s, i);
            continue;
        }
        if (contained(s[i], "+-*/^") && ind_op == -1 || contained(s[i], "+-") || contained(s[i], "*/") && contained(s[ind_op], "*/^"))
            ind_op = i;
        i += 1;
    }
    return ind_op;
}

int calc(string s)
{
    if (s.length() == 0)
        return 0;
    int ind_op = find_least_prior_op(s);
    if (ind_op == -1)
    {
        if (s[0] == '(')
            return calc(s.substr(1, s.length() - 2));
        return atoi(s.c_str());
    }
    string lhs = s.substr(0, ind_op);
    string rhs = s.substr(ind_op + 1, s.length() - ind_op - 1);
    if (s[ind_op] == '+')
    {
        return calc(lhs) + calc(rhs);
    }
    else if (s[ind_op] == '-')
    {
        return calc(lhs) - calc(rhs);
    }
    else if (s[ind_op] == '*')
    {
        return calc(lhs) * calc(rhs);
    }
    else if (s[ind_op] == '/')
    {
        return calc(lhs) / calc(rhs);
    }
    else if (s[ind_op] == '^')
    {
        return pow(calc(lhs), calc(rhs));
    }
}

int main()
{
    string s;
    cin >> s;
    cout << calc(s);
    return 0;
}