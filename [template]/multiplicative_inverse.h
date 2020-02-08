/**
 * 
 * 乘法逆元
 * 
**/

typedef long long ll;

struct{
    // 线性筛n以内的乘法逆元
    int inv[3000010];
    void init_inv(int n, int mod)
    {
        inv[1] = 1;
        for(int i = 2; i <= n; i++)
            inv[i] = (int)((ll)(mod - mod / i) * inv[mod % i] % mod);
    }
};


struct{
    // 扩展欧几里得算法
    // 解方程 a*x+b*y==1, 返回 gcd(a,b)
    int exgcd(int a, int& x, int b, int& y)
    {
        if(!b)
        {
            x = 1, y = 0;
            return a;
        }
        int r = exgcd(b, y, a % b, x);
        y -= a / b * x;
        return r;
    }
    int inv(int a, int mod)
    {
        int x, y;
        exgcd(a, x, mod, y);
        if(x < 0)x += mod;
        return x;
    }
};


struct{
    // 费马小定理 a^(p-1) === 1 (mod p) iff a, p互质
    int qpow(int base, int exp, int mod)
    {
        ll ans = 1;
        ll t = base % mod;
        while(exp)
        {
            if(exp & 1) ans = ans * t % mod;
            t = t * t % mod;
            exp >>= 1;
        }
        return (int)ans;
    }
    int inv(int a, int mod) // 保证mod为质数
    {
        return qpow(a, mod - 2, mod);
    }
};