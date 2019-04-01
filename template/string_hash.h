/**
 * 
 * 字符串哈希
 * 
**/

typedef unsigned long long ull;

struct string_hash
{
    ull _hashc[2000010], *hashc;
    const ull base = 233;
    ull powb[2000010] = {1};
    void init(char* s)
    {
        hashc = _hashc + 1;
        for(int i = 0; s[i]; i++)
        {
            powb[i + 1] = powb[i] * base;
            hashc[i] = hashc[i - 1] * base + s[i];
        }
    }
    ull range(int lt, int rt)
    {
        return hashc[rt] - hashc[lt - 1] * powb[rt - lt + 1];
    }
    ull concat(int lt1, int rt1, int lt2, int rt2)
    {
        if(lt1 > rt1 && lt2 > rt2)return 0ULL;
        if(lt1 > rt1)return range(lt2, rt2);
        if(lt2 > rt2)return range(lt1, rt1);
        return range(lt1, rt1) * powb[rt2 - lt2 + 1] + range(lt2, rt2);
    }
};