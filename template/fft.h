/**
 * 
 * FFT 快速傅里叶变换
 * 
**/

#include <cmath>
#include <algorithm>

const double PI = acos(-1);

template<typename T>
struct Complex
{
    T real, img;
    friend Complex operator+(const Complex& lhs, const Complex& rhs)
    {
        return (Complex){lhs.real + rhs.real, lhs.img + rhs.img};
    }
    friend Complex operator-(const Complex& lhs, const Complex& rhs)
    {
        return (Complex){lhs.real - rhs.real, lhs.img - rhs.img};
    }
    friend Complex operator*(const Complex& lhs, const Complex& rhs)
    {
        return (Complex){
            lhs.real * rhs.real - lhs.img * rhs.img, 
            lhs.img * rhs.real + lhs.real * rhs.img};
    }
};

typedef Complex<double> C;
struct FFT
{
    int r[(1 << 20) + 10];
    void init(int logn)
    {
        int n = 1 << logn;
        logn--;
        for(int i = 0; i < n; i++)
            r[i] = (r[i >> 1] >> 1) | ((i & 1) << logn);
    }
    void operator()(C* poly, int n, int op)
    {
        for(int i = 0; i < n; i++)
            if(i < r[i])std::swap(poly[i], poly[r[i]]);
        for(int i = 1; i < n; i <<= 1)
        {
            C x = {cos(PI / i), op * sin(PI / i)};
            for(int j = 0; j < n; j += (i << 1))
            {
                C y = {1, 0};
                for(int k = 0; k < i; k++, y = x * y)
                {
                    C p = poly[j + k], q = y * poly[i + j + k];
                    poly[j + k] = p + q;
                    poly[i + j + k] = p - q;
                }
            }
        }
        if(op == -1)
            for(int i = 0; i < n; i++)
                poly[i].real /= n;
    }
}fft;