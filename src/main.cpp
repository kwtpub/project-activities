#include "../include/function.h"
#include "../include/integration.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void printHeader(const string& title) {
    cout << "\n" << string(60, '=') << "\n";
    cout << title << "\n";
    cout << string(60, '=') << "\n";
}

void task1_exactIntegral() {
    printHeader("ЗАДАНИЕ 1: Точное значение интеграла на интервале A = [0, 1]");
    
    double a = 0.0, b = 1.0;
    
    cout << "Функция: f(x) = 1/(x^2 + 4x + 3)\n";
    cout << "Первообразная: F(x) = 1/2 * ln|(x+1)/(x+3)|\n";
    cout << "Интервал: [" << a << ", " << b << "]\n\n";
    
    try {
        double exact = Function::exactIntegral(a, b);
        cout << "Точное значение интеграла: " << fixed << setprecision(10) 
                  << exact << "\n";
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
}

void task2_leftRectangle(int n) {
    printHeader("ЗАДАНИЕ 2: Левое правило для n узлов");
    
    double a = 0.0, b = 1.0;
    
    cout << "Интервал: [" << a << ", " << b << "]\n";
    cout << "Количество узлов: n = " << n << "\n\n";
    
    try {
        double result = Integration::leftRectangle(Function::evaluate, a, b, n);
        double exact = Function::exactIntegral(a, b);
        double error = abs(result - exact);
        
        cout << "Результат (левое правило): " << fixed << setprecision(10) 
                  << result << "\n";
        cout << "Точное значение:            " << exact << "\n";
        cout << "Абсолютная погрешность:     " << error << "\n";
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
}

void task3_midpointRule(int n) {
    printHeader("ЗАДАНИЕ 3: Правило средних точек для n узлов");
    
    double a = 0.0, b = 1.0;
    
    cout << "Интервал: [" << a << ", " << b << "]\n";
    cout << "Количество узлов: n = " << n << "\n\n";
    
    try {
        double result = Integration::midpointRule(Function::evaluate, a, b, n);
        double exact = Function::exactIntegral(a, b);
        double error = abs(result - exact);
        
        cout << "Результат (средние точки):  " << fixed << setprecision(10) 
                  << result << "\n";
        cout << "Точное значение:            " << exact << "\n";
        cout << "Абсолютная погрешность:     " << error << "\n";
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
}

void task4_nonConvergence(int m) {
    printHeader("ЗАДАНИЕ 4: Особенности на B = [-1, 0] и отсутствие сходимости");
    
    double a = -1.0, b = 0.0;
    
    cout << "Интервал: [" << a << ", " << b << "]\n";
    cout << "Особенность: x = -1 (полюс функции)\n";
    cout << "Функция: f(x) = 1/((x+1)(x+3)) имеет особенность в x = -1\n\n";
    
    if (Function::hasSingularity(a, b)) {
        cout << "ПОДТВЕРЖДЕНО: На интервале есть особенность!\n\n";
    }
    
    cout << "Демонстрация отсутствия сходимости метода трапеций:\n";
    cout << setw(10) << "n" << setw(20) << "Значение интеграла" << "\n";
    cout << string(30, '-') << "\n";
    
    auto results = Integration::demonstrateNonConvergence(Function::evaluate, a, b, m);
    
    for (const auto& [n, value] : results) {
        cout << setw(10) << n << setw(20) << fixed << setprecision(6);
        if (isnan(value)) {
            cout << "NaN (ошибка)\n";
        } else {
            cout << value << "\n";
        }
    }
    
    cout << "\nВывод: Значения не стабилизируются, что указывает на отсутствие сходимости\n";
    cout << "из-за наличия особенности в точке x = -1.\n";
}

void task5_cauchyPrincipalValue(int n) {
    printHeader("ЗАДАНИЕ 5: Главное значение интеграла по Коши на C = [-2, 0]");
    
    double a = -2.0, b = 0.0;
    double singularity = -1.0;  // Особенность в точке x = -1
    
    cout << "Интервал: [" << a << ", " << b << "]\n";
    cout << "Особенность: x = " << singularity << "\n";
    cout << "Количество узлов: n = " << n << "\n\n";
    
    cout << "Главное значение по Коши вычисляется как:\n";
    cout << "P.V. ∫[-2,0] f(x)dx = lim(ε→0) [∫[-2,-1-ε] f(x)dx + ∫[-1+ε,0] f(x)dx]\n\n";
    
    // Вычисляем для разных значений epsilon, чтобы показать сходимость
    cout << setw(15) << "Epsilon" << setw(20) << "Главное значение" << "\n";
    cout << string(35, '-') << "\n";
    
    vector<double> epsilons = {1e-2, 1e-3, 1e-4, 1e-5, 1e-6};
    
    for (double eps : epsilons) {
        try {
            double pv = Integration::cauchyPrincipalValue(Function::evaluate, a, b, singularity, n, eps);
            cout << setw(15) << scientific << setprecision(1) << eps
                      << setw(20) << fixed << setprecision(10) << pv << "\n";
        } catch (const exception& e) {
            cout << setw(15) << eps << setw(20) << "Ошибка\n";
        }
    }
    
    cout << "\nВывод: При уменьшении epsilon значения стабилизируются,\n";
    cout << "что подтверждает существование главного значения по Коши.\n";
}

void interactiveMode() {
    printHeader("ИНТЕРАКТИВНЫЙ РЕЖИМ");
    
    int choice;
    do {
        cout << "\nВыберите операцию:\n";
        cout << "1. Вычислить интеграл методом левых прямоугольников\n";
        cout << "2. Вычислить интеграл методом средних точек\n";
        cout << "3. Вычислить интеграл методом трапеций\n";
        cout << "4. Вычислить главное значение по Коши\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        
        cin >> choice;
        
        if (choice == 0) break;
        
        double a, b;
        int n;
        
        cout << "Введите нижний предел a: ";
        cin >> a;
        cout << "Введите верхний предел b: ";
        cin >> b;
        cout << "Введите количество узлов n: ";
        cin >> n;
        
        try {
            double result = 0.0;
            bool computed = false;
            
            switch (choice) {
                case 1:
                    result = Integration::leftRectangle(Function::evaluate, a, b, n);
                    cout << "\nРезультат (левое правило): " << fixed 
                              << setprecision(10) << result << "\n";
                    computed = true;
                    break;
                    
                case 2:
                    result = Integration::midpointRule(Function::evaluate, a, b, n);
                    cout << "\nРезультат (средние точки): " << fixed 
                              << setprecision(10) << result << "\n";
                    computed = true;
                    break;
                    
                case 3:
                    result = Integration::trapezoidalRule(Function::evaluate, a, b, n);
                    cout << "\nРезультат (трапеции): " << fixed 
                              << setprecision(10) << result << "\n";
                    computed = true;
                    break;
                    
                case 4: {
                    double singularity;
                    cout << "Введите точку особенности: ";
                    cin >> singularity;
                    result = Integration::cauchyPrincipalValue(Function::evaluate, a, b, 
                                                              singularity, n);
                    cout << "\nГлавное значение по Коши: " << fixed 
                              << setprecision(10) << result << "\n";
                    computed = true;
                    break;
                }
                    
                default:
                    cout << "Неверный выбор!\n";
            }
            
            // Пытаемся вычислить точное значение если нет особенностей
            if (computed && choice >= 1 && choice <= 3 && !Function::hasSingularity(a, b)) {
                double exact = Function::exactIntegral(a, b);
                cout << "Точное значение:           " << exact << "\n";
                cout << "Абсолютная погрешность:    " << abs(result - exact) << "\n";
            }
            
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << "\n";
        }
        
    } while (choice != 0);
}

int main(int argc, char* argv[]) {
    cout << fixed << setprecision(10);
    
    printHeader("ЧИСЛЕННОЕ ИНТЕГРИРОВАНИЕ");
    cout << "Функция: f(x) = 1/(x^2 + 4x + 3) = 1/((x+1)(x+3))\n";
    cout << "Параметры: n = 7, m = 10\n";
    
    const int n = 7;  // Количество узлов для заданий 2, 3, 5
    const int m = 10; // Количество итераций для задания 4
    
    // Выполняем все задания
    task1_exactIntegral();
    task2_leftRectangle(n);
    task3_midpointRule(n);
    task4_nonConvergence(m);
    task5_cauchyPrincipalValue(n);
    
    // Интерактивный режим (опционально)
    if (argc > 1 && string(argv[1]) == "--interactive") {
        interactiveMode();
    }
    
    return 0;
}
