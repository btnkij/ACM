#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#define clr(x, y) memset(x, y, sizeof(x))
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
const double eps = 1e-8, pi = acos(-1.0);
const ll maxS = 1e5 + 13;
const ll maxT = 1e3 + 13;
const ll MOD = 835672545;
const ll base = 19260817;
const ll layer = 20;
using namespace std;

inline void read(ll& x) { scanf("%lld", &x); }
inline void read(ll& x, ll& y) {
	read(x);
	read(y);
}
inline void read(ll& x, ll& y, ll& z) {
	read(x, y);
	read(z);
}
inline void read(int& x) { scanf("%d", &x); }
inline void read(int& x, int& y) {
	read(x);
	read(y);
}
inline void read(int& x, int& y, int& z) {
	read(x, y);
	read(z);
}

struct node {
	ll x1, y1, x2, y2, k;
	bool operator <(const node& p) const {
		if (x1 != p.x1)
			return x1 < p.x1;
		else
			return y1 < p.y1;
	}
	// bool operator ==(const node& p) const {
	//	return x == p.x && y == p.y;
	//}
};

struct tree {
	ll l, r, val, sub;
};

struct edge {
	ll to, len;
	bool operator<(const edge& p) const { return len < p.len; }
};

ll n, m, i, j, k, x, y, z, S, T, ii, s, t, l, r, pos, len, dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };
ll tot = 0, ans = 0, kase = 0, cnt = 0, tmp;
bool flag = false, vis[maxS];
string s1, s2, s3;
char ch;

ll a[maxS], f1[maxS][30], f2[maxS][30];

ll val1(ll l, ll r) {
	ll k = -1, len = r - l + 1;
	while (len) {
		k++;
		len >>= 1;
	}
	len = 1ll << k;
	return max(f1[l][k], f1[r - len + 1][k]);
}

ll val2(ll l, ll r) {
	ll k = -1, len = r - l + 1;
	while (len) {
		k++;
		len >>= 1;
	}
	len = 1ll << k;
	return min(f2[l][k], f2[r - len + 1][k]);
}

char c1[maxS], c2[maxS];

int main() {
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
	read(T);
	while (T--) {
		flag = false;
		scanf("%s", c1);
		scanf("%s", c2);
		ll len1 = strlen(c1), len2 = strlen(c2);
		if (c1[0] != c2[0]) {
			printf("No\n");
			continue;
		}
		i = j = 0;
		while (i < len1 - 1 && c1[i] == c1[i + 1])
			i++;
		while (j < len2 - 1 && c2[j] == c2[j + 1])
			j++;
		if (j > i) {
			printf("No\n");
			continue;
		}
		i = j = 0;
		while (i < len1 && j < len2) {
			while (j < len2 && c1[i] != c2[j])
				j++;
			if (c1[i] == c2[j]) {
				i++;
				j++;
			}
		}
		if (i == len1)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}