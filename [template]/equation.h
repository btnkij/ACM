
#include <cmath>

const double eps = 1e-10;

//解一元三次方程, 返回实根个数
int cubic_eq(double a, double b, double c, double d, double x[])
{
    double A = b * b - 3 * a * c;
    double B = b * c - 9 * a * d;
    double C = c * c - 3 * b * d;
    double D = B * B - 4 * A * C;
    if (fabs(A) < eps && (fabs(B) < eps || fabs(D) < eps))
    {
        x[0] = -b / (3 * a);
        return 1; // 3个相等实根
    }
    else if (fabs(D) < eps && fabs(A) > eps)
    {
        double K = B / A;
        x[0] = -b / a + K;
        x[1] = x[2] = -K / 2;
        return 2; // 2个不等实根
    }
    else if (D > 0)
    {
        double Y1 = A * b + 3 * a * ((-B + sqrt(D)) / 2);
        double Y2 = A * b + 3 * a * ((-B - sqrt(D)) / 2);
        bool s1 = Y1 < 0, s2 = Y2 < 0;
        Y1 = pow(Y1, 1.0 / 3.0);
        if (s1)
            Y1 = -Y1;
        Y2 = pow(Y2, 1.0 / 3.0);
        if (s2)
            Y2 = -Y2;
        x[0] = (-b - (Y1 + Y2)) / (3 * a);
        return 1; // 1个实根, 2个复数根
    }
    else if (D < 0)
    {
        double x[3];
        double T = (2 * A * b - 3 * a * B) / (2 * A * sqrt(A));
        double theta = acos(T) / 3;
        x[0] = (-b - 2 * sqrt(A) * cos(theta)) / (3 * a);
        x[1] = (-b + sqrt(A) * (cos(theta) - sqrt(3) * sin(theta))) / (3 * a);
        x[2] = (-b + sqrt(A) * (cos(theta) + sqrt(3) * sin(theta))) / (3 * a);
        return 3; // 3个不等实根
    }
}