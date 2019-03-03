/**
 * 
 * 预处理组合数
 * 
**/

const int MOD = 1000000007;
int comb[1010][1010];
void init_comb(int n)
{
    for(int i = 1; i <= n; i++)
    {
        comb[i][0] = comb[i][i] = 1;
        for(int j = 1; j < i; j++)
        {
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
        }
    }
}