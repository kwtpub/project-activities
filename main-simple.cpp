#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <limits> // For numeric_limits

using namespace std;

// Функция f(x) = 1/(x^2 + 4x + 3) 
double f(double x) {
    double denominator = x * x + 4.0 * x + 3.0;
    return 1.0 / denominator;
}

// Первообразная F(x) = 1/2 * ln|(x+1)/(x+3)|
double F(double x) {
    double num = abs(x + 1.0);
    double den = abs(x + 3.0);
    return 0.5 * log(num / den);
}

// Точное значение интеграла по формуле Ньютона-Лейбница
double exact_integral(double a, double b) {
    double Fa = F(a);
    double Fb = F(b);
    return Fb - Fa;
}

// Метод левых прямоугольников
double rectangles(double start, double end, int parts) 
{
   // Вычисляем ширину одного прямоугольника
   double step = (end - start) / parts;
   // Сумма площадей прямоугольников
   double total = 0;
   
   // Суммируем площади всех прямоугольников
   for (int i = 0; i < parts; i++) 
   {
   // Вычисляем x-координату левой стороны прямоугольника
   double x = start + i * step;
   // Добавляем высоту прямоугольника (значение функции)
   total += f(x);
   }
   
   // Умножаем сумму высот на ширину для получения общей площади
   return total * step;
}

// Метод средних точек
double midpoint_rule(double a, double b, int n) {
    if (n <= 0) {
        cout << "Ошибка: n должно быть положительным" << endl;
        return numeric_limits<double>::quiet_NaN();
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
double trapezoid(double start, double end, int parts) // parts - на сколько частей разбиваем интервал
{
  // Вычисляем ширину одного отрезка
  double step = (end - start) / parts;
  // Начальная сумма - полусумма значений на краях
  double total = (f(start) + f(end)) / 2;

  // Суммируем значения функции во всех внутренних точках
  for (int i = 1; i < parts; i++) 
  {
  total += f(start + i * step);
  }

  // Умножаем накопленную сумму на ширину шага и получаем приближённое значение интеграла.
  return total * step;
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

// Численное вычисление главного значения по Коши с использованием симметричного обхода особенности
double cauchy_principal_value(double a, double b, int n, double singularity) {
    // Разбиваем интервал на две части, избегая особенность
    double epsilon = 1e-8; // Малое значение для обхода особенности
    double left_end = singularity - epsilon;
    double right_start = singularity + epsilon;
    
    // Если особенность находится вне интервала, вычисляем обычный интеграл
    if (singularity <= a || singularity >= b) {
        return rectangles(a, b, n);
    }
    
    // Вычисляем количество узлов для каждой части
    double total_length = (left_end - a) + (b - right_start);
    int n_left = static_cast<int>(n * (left_end - a) / total_length);
    int n_right = n - n_left;
    
    if (n_left <= 0) n_left = 1;
    if (n_right <= 0) n_right = 1;
    
    // Вычисляем интеграл на левой и правой частях
    double left_integral = rectangles(a, left_end, n_left);
    double right_integral = rectangles(right_start, b, n_right);
    
    return left_integral + right_integral;
}

int main() {
    
    const int n = 7;
    const int m = 10;

    double A[2] = {0.0, 1.0}; // по условию задания 
    double B[2] = {-1, 0}; 
    double C[2] = {-2, 0};
    
    cout << "ЧИСЛЕННОЕ ИНТЕГРИРОВАНИЕ\n";
    cout << "Функция: f(x) = 1/(x^2 + 4x + 3)\n";
    cout << "Параметры: n = " << n << ", m = " << m << "\n";
    
    // Задание 1: Точное значение интеграла на [0, 1]
    cout << "ЗАДАНИЕ 1: Точное значение интеграла на интервале A = [0, 1]" << endl;
    cout << "Функция: f(x) = 1/(x^2 + 4x + 3)\n";
    cout << "Первообразная: F(x) = 1/2 * ln|(x+1)/(x+3)|\n";
    cout << "Интервал: [" << A[0] << ", " << A[1] << "]\n\n";
    
    double result1 = exact_integral(A[0], A[1]);

    cout << "Точное значение интеграла: " << result1 << endl;

    cout << endl;     
    // Задание 2: Левое правило
    cout << "ЗАДАНИЕ 2: Левое правило для n узлов" << endl;
    cout << "Интервал: [" << A[0] << ", " << A[1] << "]" << endl;
    cout << "Количество узлов: n = " << n << "\n\n";
    
    double result2 = rectangles(A[0], A[1], n);
    if (!isnan(result2)) {
        cout << "Результат по левому правилу: " << result2 << endl;
    }

    cout << endl;
    
    // Задание 3: Правило средних точек
    cout << "ЗАДАНИЕ 3: Правило средних точек для n узлов" << endl;
    cout << "Интервал: [" << A[0] << ", " << A[1] << "]" << endl;
    cout << "Количество узлов: n = " << n << "\n\n";
    
    double result3 = midpoint_rule(A[0], A[1], n);
    cout << "Результат (средние точки):  " << result3 << "\n";

    cout << endl;
    
    // Задание 4: Особенности на [-1, 0] 
    cout << "ЗАДАНИЕ 4: Особенности на B = [-1, 0] и отсутствие сходимости" << endl;
    cout << "Интервал: [" << B[0] << ", " << B[1] << "]\n";
    
    if (has_singularity(B[0], B[1])) {
        cout << "ПОДТВЕРЖДЕНО: На интервале есть особенность!\n\n";
    }
    
    cout << "Демонстрация отсутствия сходимости метода трапеций:\n";
    cout << setw(10) << "n" << " " << setw(20) << "Значение интеграла" << "\n";
    cout << string(31, '-') << "\n";
    
    for (int k = 2; k <= m; k++) {
        double integral = trapezoid(B[0], B[1], k);
        cout << setw(10) << k << " ";
        if (isnan(integral)) {
            cout << setw(20) << "NaN (ошибка)" << "\n";
        } else {
            cout << setw(20) << fixed << setprecision(6) << integral << "\n";
        }
    }

    // Задание 5: Главное значение интеграла по Коши на интервале C = [-2, 0]
    cout << endl;
    cout << "ЗАДАНИЕ 5: Главное значение интеграла по Коши на интервале C = [-2, 0]" << endl;
    cout << "Интервал: [" << C[0] << ", " << C[1] << "]\n";
    
    // Точное значение главного значения
    double exact_pv = exact_integral(C[0], C[1]);
    cout << "Точное главное значение: " << exact_pv << endl;
    
    // Численное вычисление главного значения с использованием m узлов
    double numerical_pv = cauchy_principal_value(C[0], C[1], m, -1.0);
    cout << "Численное главное значение (m = " << m << " узлов): " << numerical_pv << endl;
    
    return 0;
}