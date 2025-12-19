#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

const double PI = acos(-1.0);

// Объявление переменных (глобальных констант)
const int N_DEFAULT = 5; // для методов на интервале A
const int M_DEFAULT = 8; // для метода трапеций на интервале B

// Функция f(x) = 1 / cos(x)
double f(double x) 
{
    double c = cos(x);
    if (abs(c) < 1e-12) 
    {
        // Возвращаем бесконечность, если cos(x) близок к нулю
        return numeric_limits<double>::infinity();
    }
    return 1.0 / c;
}

// Первообразная: F(x) = ln |sec x + tg x|, эквивалентно ln|tg(x/2 + pi/4)| (для x в [-pi/2, pi/2])
double F(double x) 
{
    double sec = 1.0 / cos(x);
    double tan = sin(x) / cos(x);
    return log(abs(sec + tan));
}

// Точное значение интеграла на [a, b]
double exact_integral(double a, double b) 
{
    return F(b) - F(a);
}

// Левое правило прямоугольников
double left_rectangles(double a, double b, int n) 
{
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; ++i) 
    {
        double x = a + i * h;
        double fx = f(x);
        if (!isfinite(fx)) 
        {
            cerr << "Ошибка: особенность в узле x = " << x << " при вычислении левого правила.\n";
            return numeric_limits<double>::quiet_NaN(); // Возвращаем NaN при проблемах
        }
        sum += fx;
    }
    return sum * h;
}

// Правило средних точек
double midpoint_rule(double a, double b, int n) 
{
    double h = (b - a) / n;

    double sum = 0.0;
    for (int i = 0; i < n; ++i) 
    {

        double x = a + (i + 0.5) * h;
        double fx = f(x);
        if (!isfinite(fx)) 
        {
            cerr << "Ошибка: особенность в узле x = " << x << " при вычислении правила средней точки.\n";
            return numeric_limits<double>::quiet_NaN();
        }
        sum += fx;
    }
    return sum * h;
}

// Правило трапеций
double trapezoidal_rule(double a, double b, int m) 
{
    double h = (b - a) / m;
    double fa = f(a);
    double fb = f(b);
    // Проверяем концы интервала на особенности

    if (!isfinite(fa) || !isfinite(fb)) 
    {
        cerr << "Ошибка: особенность на границе интервала [" << a << ", " << b << "] при вычислении трапеций.\n";
        return numeric_limits<double>::quiet_NaN();
    }
    double sum = 0.5 * (fa + fb);
    for (int i = 1; i < m; ++i) 
    {
        double x = a + i * h;
        double fx = f(x);
        if (!isfinite(fx)) 
        {
            cerr << "Ошибка: особенность внутри интервала в точке x = " << x << " при вычислении трапеций.\n";
            return numeric_limits<double>::quiet_NaN();
        }
        sum += fx;
    }
    return sum * h;
}

// Главное значение по Коши (с малым ε)
double cauchy_principal_value(double a, double b, double singular_point, double epsilon = 1e-6) 
{
    if (singular_point <= a || singular_point >= b) 
    {
        cerr << "Ошибка: особенность не находится внутри интервала [" << a << ", " << b << "].\n";
        return exact_integral(a, b);
    }
    double left_part = exact_integral(a, singular_point - epsilon);
    double right_part = exact_integral(singular_point + epsilon, b);
    return left_part + right_part;
}

int main() 
{
    cout << fixed << setprecision(10);

    // Параметры для задания №2
    const string function_desc = "f(x) = 1 / cos(x)";
    const string antiderivative_desc = "F(x) = ln|sec(x) + tan(x)|";
    const double A_start = 0.0, A_end = PI / 4.0;
    const double B_start = 0.0, B_end = PI / 2.0;
    const double C_start = 0.0, C_end = 3.0 * PI / 4.0;
    const int n = N_DEFAULT; // для A
    const int m = M_DEFAULT; // для B
    const double singularity_x = PI / 2.0; // Особенность функции на интервалах B и C

    cout << "=== Задание №2 ===" << endl;
    cout << "Функция: " << function_desc << endl << endl;

    cout << "--- 1. Точное значение интеграла на интервале A = [0, π/4] ---" << endl;

    double exact_A = exact_integral(A_start, A_end);
    cout << "Первообразная: " << antiderivative_desc << endl;
    cout << "Точное значение: " << exact_A << endl << endl;
    cout << "--- 2. Левое правило прямоугольников (n = " << n << ") на интервале A ---" << endl;
    double left_A = left_rectangles(A_start, A_end, n);
    if (isfinite(left_A)) 
    {
        cout << "Приближённое значение: " << left_A << endl;
    }
    else 
    {
        cout << "Не удалось вычислить (NaN или ошибка)." << endl;
    }
    cout << endl;

    cout << "--- 3. Правило средних точек (n = " << n << ") на интервале A ---" << endl;
    double mid_A = midpoint_rule(A_start, A_end, n);
    if (isfinite(mid_A)) 
    {
        cout << "Приближённое значение: " << mid_A << endl;
    }
    else 
    {
        cout << "Не удалось вычислить (NaN или ошибка)." << endl;
    }
    cout << endl;

    cout << "--- 4. Правило трапеций (m = " << m << ") на интервале B = [0, π/2] ---" << endl;
    cout << "Интервал B содержит особенность в точке x = π/2." << endl;
    double trap_B = trapezoidal_rule(B_start, B_end, m);
    if (isfinite(trap_B)) {
        cout << "Значение (некорректное): " << trap_B << endl;
        cout << "Это значение неверно, так как интеграл расходится на интервале B." << endl;
    }
    else {
        cout << "Метод трапеций не смог вычислить интеграл на B из-за особенности." << endl;
        cout << "Это подтверждает отсутствие сходимости." << endl;
    }
    cout << endl;

    cout << "--- 5. Главное значение по Коши на интервале C = [0, 3π/4] ---" << endl;
    cout << "Интервал C содержит особенность в точке x = π/2." << endl;
    double cpv_C = cauchy_principal_value(C_start, C_end, singularity_x);
    if (isfinite(cpv_C)) {
        cout << "Приближённое главное значение (ε = 1e-6): " << cpv_C << endl;
        cout << "Примечание: Это значение условное, так как истинное главное значение не существует." << endl;
        cout << "Интеграл расходится с обеих сторон от особенности." << endl;
    }
    else {
        cout << "Не удалось вычислить главное значение (интеграл расходится)." << endl;
    }
    cout << endl;

    cout << "=== Конец расчётов ===" << endl;

    return 0;
}
