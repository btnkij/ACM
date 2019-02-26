/**
* Number:ybt1358
* Title:中缀表达式值(expr)
* Status:AC
* Tag:[递归下降]
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

bool failed;

int find_rbracket(string s, int left)
{
    if (failed)
        return -1;
    int cnt = 1;
    int right = left + 1;
    while (cnt > 0 && right < s.length())
    {
        if (s[right] == '(')
            cnt += 1;
        else if (s[right] == ')')
            cnt -= 1;
        right += 1;
    }
    if (cnt)
    {
        failed = true;
        return -1;
    }
    return right;
}

bool contained(char ch, const char *S)
{
    if (failed)
        return false;
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
    if (failed)
        return -1;
    int ind_op = -1;
    int i = 0;
    while (i < s.length())
    {
        if (s[i] == '(')
        {
            i = find_rbracket(s, i);
            if (failed)
                return -1;
            continue;
        }
        if (contained(s[i], "+-*/") && ind_op == -1 || contained(s[i], "+-") || contained(s[i], "*/") && contained(s[ind_op], "*/"))
            ind_op = i;
        i += 1;
    }
    return ind_op;
}

struct NullableInt
{
    int value;
    int isNull;
};
NullableInt calc(string s)
{
    if (s.length() == 0)
        return (NullableInt){0, 1};
    int ind_op = find_least_prior_op(s);
    if (failed)
        return (NullableInt){0, 1};
    if (ind_op == -1)
    {
        if (s[0] == '(' && s[s.length() - 1] == ')')
            return calc(s.substr(1, s.length() - 2));
        NullableInt ans;
        ans.value = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if ('0' <= s[i] && s[i] <= '9')
                ans.value = ans.value * 10 + (s[i] & 0xF);
            else
            {
                failed = true;
                break;
            }
        }
        ans.isNull = 0;
        return ans;
    }
    NullableInt lhs = calc(s.substr(0, ind_op));
    NullableInt rhs = calc(s.substr(ind_op + 1, s.length() - ind_op - 1));
    if (s[ind_op] == '+')
    {
        if (lhs.isNull)
        {
            lhs.value = 0;
            lhs.isNull = 0;
        }
        if (!lhs.isNull && !rhs.isNull)
        {
            lhs.value += rhs.value;
            return lhs;
        }
    }
    else if (s[ind_op] == '-')
    {
        if (lhs.isNull)
        {
            lhs.value = 0;
            lhs.isNull = 0;
        }
        if (!lhs.isNull && !rhs.isNull)
        {
            lhs.value -= rhs.value;
            return lhs;
        }
    }
    else if (s[ind_op] == '*')
    {
        if (!lhs.isNull && !rhs.isNull)
        {
            lhs.value *= rhs.value;
            return lhs;
        }
    }
    else if (s[ind_op] == '/')
    {
        if (!lhs.isNull && !rhs.isNull && rhs.value != 0)
        {
            lhs.value /= rhs.value;
            return lhs;
        }
    }
    failed = true;
    return (NullableInt){0, 1};
}

int main()
{
    string s;
    cin >> s;
    if (s[s.length() - 1] == '@')
    {
        s = s.substr(0, s.length() - 1);
    }
    failed = false;
    NullableInt ans = calc(s);
    if (failed)
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << ans.value << endl;
    }
    return 0;
}