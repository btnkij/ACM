#include <iostream>
#include <cstdio>
using namespace std;
int n, a[210], b[210], f[210][210], ans = 0;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i - 1] = b[i + n - 1] = a[i + n] = a[i];
        f[i][i] = f[i + n][i + n] = 0;
    }
    b[n] = b[n * 2] = a[1];
    for (int t = 1; t <= n - 1; t++) {
        for (int i = 1; i <= 2 * n - t; i++) {
            int j = i + t;
            for (int k = i; k < j; k++) {
                f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + a[i] * b[j] * b[k]);
            }
        }
    }
    for (int i = 1; i <= n; i++) ans = max(ans, f[i][i + n - 1]);
    printf("%d\n", ans);
    return 0;
}