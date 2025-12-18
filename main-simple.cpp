#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

// Функция f(x) = 1/(x^2 + 4x + 3) = 1/((x+1)(x+3))
double f(double x) {
    double denominator = x * x + 4.0 * x + 3.0;
    if (abs(denominator) < 1e-10) {
        cout << "Ошибка: особенность в точке x = " << fixed << setprecision(10) << x << endl;
        return nan("");
    }
    return 1.0 / denominator;
}

// Первообразная F(x) = 1/2 * ln|(x+1)/(x+3)|
double F(double x) {
    double num = abs(x + 1.0);
    double den = abs(x + 3.0);
    if (num < 1e-10 || den < 1e-10) {
        cout << "Ошибка: особенность в первообразной при x = " << fixed << setprecision(10) << x << endl;
        return nan("");
    }
    return 0.5 * log(num / den);
}

// Точное значение интеграла по формуле Ньютона-Лейбница
double exact_integral(double a, double b) {
    double Fa = F(a);
    double Fb = F(b);
    if (isnan(Fa) || isnan(Fb)) {
        return nan("");
    }
    return Fb - Fa;
}

// Метод левых прямоугольников
double left_rectangle(double a, double b, int n) {
    if (n <= 0) {
        cout << "Ошибка: n должно быть положительным" << endl;
        return nan("");
    }
    
    double h = (b - a) / n;
    double sum = 0.0;
    
    for (int i = 0; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    
    return sum * h;
}

// Метод средних точек
double midpoint_rule(double a, double b, int n) {
    if (n <= 0) {
        cout << "Ошибка: n должно быть положительным" << endl;
        return nan("");
    }
    
    double h = (b - a) / n;
    double sum = 0.0;
    
    for (int i = 0; i < n; i++) {
        double x_mid = a + (i + 0.5) * h;
        sum += f(x_mid);
    }
    
    return sum * h;
}

// Метод трапеций
double trapezoidal_rule(double a, double b, int n) {
    if (n <= 0) {
        cout << "Ошибка: n должно быть положительным" << endl;
        return nan("");
    }
    
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    
    return sum * h;
}

// Проверка наличия особенности на интервале
int has_singularity(double a, double b) {
    double singularities[] = {-1.0, -3.0};
    double epsilon = 1e-10;
    
    for (int i = 0; i < 2; i++) {
        if (singularities[i] >= a - epsilon && singularities[i] <= b + epsilon) {
            return 1;
        }
    }
    return 0;
}

void print_header(const string& title) {
    cout << "\n" << string(60, '=') << "\n";
    cout << title << "\n";
    cout << string(60, '=') << "\n";
}

int main() {
    cout << fixed << setprecision(10);
    
    const int n = 7;
    const int m = 10;
    
    cout << "ЧИСЛЕННОЕ ИНТЕГРИРОВАНИЕ\n";
    cout << "Функция: f(x) = 1/(x^2 + 4x + 3) = 1/((x+1)(x+3))\n";
    cout << "Параметры: n = " << n << ", m = " << m << "\n";
    
    // Задание 1: Точное значение интеграла на [0, 1]
    print_header("ЗАДАНИЕ 1: Точное значение интеграла на интервале A = [0, 1]");
    double a1 = 0.0, b1 = 1.0;
    cout << "Функция: f(x) = 1/(x^2 + 4x + 3)\n";
    cout << "Первообразная: F(x) = 1/2 * ln|(x+1)/(x+3)|\n";
    cout << "Интервал: [" << a1 << ", " << b1 << "]\n\n";
    
    double exact1 = exact_integral(a1, b1);
    if (!isnan(exact1)) {
        cout << "Точное значение интеграла: " << exact1 << "\n";
    }
    
    // Задание 2: Левое правило
    print_header("ЗАДАНИЕ 2: Левое правило для n узлов");
    cout << "Интервал: [" << a1 << ", " << b1 << "]\n";
    cout << "Количество узлов: n = " << n << "\n\n";
    
    double result2 = left_rectangle(a1, b1, n);
    if (!isnan(result2)) {
        cout << "Результат (левое правило): " << result2 << "\n";
        cout << "Точное значение:            " << exact1 << "\n";
        cout << "Абсолютная погрешность:     " << abs(result2 - exact1) << "\n";
    }
    
    // Задание 3: Правило средних точек
    print_header("ЗАДАНИЕ 3: Правило средних точек для n узлов");
    cout << "Интервал: [" << a1 << ", " << b1 << "]\n";
    cout << "Количество узлов: n = " << n << "\n\n";
    
    double result3 = midpoint_rule(a1, b1, n);
    if (!isnan(result3)) {
        cout << "Результат (средние точки):  " << result3 << "\n";
        cout << "Точное значение:            " << exact1 << "\n";
        cout << "Абсолютная погрешность:     " << abs(result3 - exact1) << "\n";
    }
    
    // Задание 4: Особенности на [-1, 0]
    print_header("ЗАДАНИЕ 4: Особенности на B = [-1, 0] и отсутствие сходимости");
    double a4 = -1.0, b4 = 0.0;
    cout << "Интервал: [" << a4 << ", " << b4 << "]\n";
    cout << "Особенность: x = -1 (полюс функции)\n";
    cout << "Функция: f(x) = 1/((x+1)(x+3)) имеет особенность в x = -1\n\n";
    
    if (has_singularity(a4, b4)) {
        cout << "ПОДТВЕРЖДЕНО: На интервале есть особенность!\n\n";
    }
    
    cout << "Демонстрация отсутствия сходимости метода трапеций:\n";
    cout << setw(10) << "n" << " " << setw(20) << "Значение интеграла" << "\n";
    cout << string(31, '-') << "\n";
    
    for (int k = 2; k <= m; k++) {
        double integral = trapezoidal_rule(a4, b4, k);
        cout << setw(10) << k << " ";
        if (isnan(integral)) {
            cout << setw(20) << "NaN (ошибка)" << "\n";
        } else {
            cout << setw(20) << fixed << setprecision(6) << integral << "\n";
        }
    }
    
    cout << "\nВывод: Значения не стабилизируются, что указывает на отсутствие сходимости\n";
    cout << "из-за наличия особенности в точке x = -1.\n";
    
    return 0;
}

