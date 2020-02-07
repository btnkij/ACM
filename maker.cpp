#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <ctime>
#define RI register int
#define CI const int &
#define Tp template <typename T>
using namespace std;
const int N = 100000, R = 1e9;
class FileInputOutput
{
private:
    static const int S = 1 << 21;
#define pc(ch) (Ftop < S ? Fout[Ftop++] = ch : (fwrite(Fout, 1, S, stdout), Fout[(Ftop = 0)++] = ch))
    char Fout[S];
    int Ftop, pt[15];

public:
    Tp inline void write(T x, const char &ch)
    {
        if (!x)
            return (void)(pc('0'), pc(ch));
        if (x < 0)
            x = -x, pc('-');
        RI ptop = 0;
        while (x)
            pt[++ptop] = x % 10, x /= 10;
        while (ptop)
            pc(pt[ptop--] + 48);
        pc(ch);
    }
    inline void Fend(void)
    {
        fwrite(Fout, 1, Ftop, stdout);
    }
#undef pc
} F;
inline int Rand(CI x, CI opt = 1)
{
    if (x == 1)
        return x * opt;
    return opt * (1LL * rand() * rand() % (x - 1) + 1);
}
int main()
{
    freopen("in.txt", "w", stdout);
    srand(time(0));
    RI i;
    for (F.write(N, '\n'), i = 2; i <= N; ++i)
        F.write(Rand(i - 1), ' '), F.write(i, '\n');
    for (i = 1; i <= N; ++i)
        F.write(rand() % 2, i != N ? ' ' : '\n');
    for (i = 1; i <= N; ++i)
        F.write(Rand(R, rand() % 2 ? 1 : -1), i != N ? ' ' : '\n');
    for (F.write(N, '\n'), i = 1; i <= N; ++i)
    {
        int opt = Rand(3) - 1, x = Rand(N);
        F.write(opt, ' ');
        if (opt <= 1)
            F.write(x, '\n');
        else
            F.write(x, ' '), F.write(Rand(R, rand() % 2 ? 1 : -1), '\n');
    }
    return F.Fend(), 0;
}