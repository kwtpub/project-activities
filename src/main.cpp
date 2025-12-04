#include "../include/function.h"
#include "../include/integration.h"
#include <iostream>
#include <iomanip>
#include <vector>

void printHeader(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << title << "\n";
    std::cout << std::string(60, '=') << "\n";
}

void task1_exactIntegral() {
    printHeader("ЗАДАНИЕ 1: Точное значение интеграла на интервале A = [0, 1]");
    
    double a = 0.0, b = 1.0;
    
    std::cout << "Функция: f(x) = 1/(x^2 + 4x + 3)\n";
    std::cout << "Первообразная: F(x) = 1/2 * ln|(x+1)/(x+3)|\n";
    std::cout << "Интервал: [" << a << ", " << b << "]\n\n";
    
    try {
        double exact = Function::exactIntegral(a, b);
        std::cout << "Точное значение интеграла: " << std::fixed << std::setprecision(10) 
                  << exact << "\n";
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void task2_leftRectangle(int n) {
    printHeader("ЗАДАНИЕ 2: Левое правило для n узлов");
    
    double a = 0.0, b = 1.0;
    
    std::cout << "Интервал: [" << a << ", " << b << "]\n";
    std::cout << "Количество узлов: n = " << n << "\n\n";
    
    try {
        double result = Integration::leftRectangle(Function::evaluate, a, b, n);
        double exact = Function::exactIntegral(a, b);
        double error = std::abs(result - exact);
        
        std::cout << "Результат (левое правило): " << std::fixed << std::setprecision(10) 
                  << result << "\n";
        std::cout << "Точное значение:            " << exact << "\n";
        std::cout << "Абсолютная погрешность:     " << error << "\n";
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void task3_midpointRule(int n) {
    printHeader("ЗАДАНИЕ 3: Правило средних точек для n узлов");
    
    double a = 0.0, b = 1.0;
    
    std::cout << "Интервал: [" << a << ", " << b << "]\n";
    std::cout << "Количество узлов: n = " << n << "\n\n";
    
    try {
        double result = Integration::midpointRule(Function::evaluate, a, b, n);
        double exact = Function::exactIntegral(a, b);
        double error = std::abs(result - exact);
        
        std::cout << "Результат (средние точки):  " << std::fixed << std::setprecision(10) 
                  << result << "\n";
        std::cout << "Точное значение:            " << exact << "\n";
        std::cout << "Абсолютная погрешность:     " << error << "\n";
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void task4_nonConvergence(int m) {
    printHeader("ЗАДАНИЕ 4: Особенности на B = [-1, 0] и отсутствие сходимости");
    
    double a = -1.0, b = 0.0;
    
    std::cout << "Интервал: [" << a << ", " << b << "]\n";
    std::cout << "Особенность: x = -1 (полюс функции)\n";
    std::cout << "Функция: f(x) = 1/((x+1)(x+3)) имеет особенность в x = -1\n\n";
    
    if (Function::hasSingularity(a, b)) {
        std::cout << "ПОДТВЕРЖДЕНО: На интервале есть особенность!\n\n";
    }
    
    std::cout << "Демонстрация отсутствия сходимости метода трапеций:\n";
    std::cout << std::setw(10) << "n" << std::setw(20) << "Значение интеграла" << "\n";
    std::cout << std::string(30, '-') << "\n";
    
    auto results = Integration::demonstrateNonConvergence(Function::evaluate, a, b, m);
    
    for (const auto& [n, value] : results) {
        std::cout << std::setw(10) << n << std::setw(20) << std::fixed << std::setprecision(6);
        if (std::isnan(value)) {
            std::cout << "NaN (ошибка)\n";
        } else {
            std::cout << value << "\n";
        }
    }
    
    std::cout << "\nВывод: Значения не стабилизируются, что указывает на отсутствие сходимости\n";
    std::cout << "из-за наличия особенности в точке x = -1.\n";
}

void task5_cauchyPrincipalValue(int n) {
    printHeader("ЗАДАНИЕ 5: Главное значение интеграла по Коши на C = [-2, 0]");
    
    double a = -2.0, b = 0.0;
    double singularity = -1.0;  // Особенность в точке x = -1
    
    std::cout << "Интервал: [" << a << ", " << b << "]\n";
    std::cout << "Особенность: x = " << singularity << "\n";
    std::cout << "Количество узлов: n = " << n << "\n\n";
    
    std::cout << "Главное значение по Коши вычисляется как:\n";
    std::cout << "P.V. ∫[-2,0] f(x)dx = lim(ε→0) [∫[-2,-1-ε] f(x)dx + ∫[-1+ε,0] f(x)dx]\n\n";
    
    // Вычисляем для разных значений epsilon, чтобы показать сходимость
    std::cout << std::setw(15) << "Epsilon" << std::setw(20) << "Главное значение" << "\n";
    std::cout << std::string(35, '-') << "\n";
    
    std::vector<double> epsilons = {1e-2, 1e-3, 1e-4, 1e-5, 1e-6};
    
    for (double eps : epsilons) {
        try {
            double pv = Integration::cauchyPrincipalValue(Function::evaluate, a, b, singularity, n, eps);
            std::cout << std::setw(15) << std::scientific << std::setprecision(1) << eps
                      << std::setw(20) << std::fixed << std::setprecision(10) << pv << "\n";
        } catch (const std::exception& e) {
            std::cout << std::setw(15) << eps << std::setw(20) << "Ошибка\n";
        }
    }
    
    std::cout << "\nВывод: При уменьшении epsilon значения стабилизируются,\n";
    std::cout << "что подтверждает существование главного значения по Коши.\n";
}

void interactiveMode() {
    printHeader("ИНТЕРАКТИВНЫЙ РЕЖИМ");
    
    int choice;
    do {
        std::cout << "\nВыберите операцию:\n";
        std::cout << "1. Вычислить интеграл методом левых прямоугольников\n";
        std::cout << "2. Вычислить интеграл методом средних точек\n";
        std::cout << "3. Вычислить интеграл методом трапеций\n";
        std::cout << "4. Вычислить главное значение по Коши\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";
        
        std::cin >> choice;
        
        if (choice == 0) break;
        
        double a, b;
        int n;
        
        std::cout << "Введите нижний предел a: ";
        std::cin >> a;
        std::cout << "Введите верхний предел b: ";
        std::cin >> b;
        std::cout << "Введите количество узлов n: ";
        std::cin >> n;
        
        try {
            double result = 0.0;
            bool computed = false;
            
            switch (choice) {
                case 1:
                    result = Integration::leftRectangle(Function::evaluate, a, b, n);
                    std::cout << "\nРезультат (левое правило): " << std::fixed 
                              << std::setprecision(10) << result << "\n";
                    computed = true;
                    break;
                    
                case 2:
                    result = Integration::midpointRule(Function::evaluate, a, b, n);
                    std::cout << "\nРезультат (средние точки): " << std::fixed 
                              << std::setprecision(10) << result << "\n";
                    computed = true;
                    break;
                    
                case 3:
                    result = Integration::trapezoidalRule(Function::evaluate, a, b, n);
                    std::cout << "\nРезультат (трапеции): " << std::fixed 
                              << std::setprecision(10) << result << "\n";
                    computed = true;
                    break;
                    
                case 4: {
                    double singularity;
                    std::cout << "Введите точку особенности: ";
                    std::cin >> singularity;
                    result = Integration::cauchyPrincipalValue(Function::evaluate, a, b, 
                                                              singularity, n);
                    std::cout << "\nГлавное значение по Коши: " << std::fixed 
                              << std::setprecision(10) << result << "\n";
                    computed = true;
                    break;
                }
                    
                default:
                    std::cout << "Неверный выбор!\n";
            }
            
            // Пытаемся вычислить точное значение если нет особенностей
            if (computed && choice >= 1 && choice <= 3 && !Function::hasSingularity(a, b)) {
                double exact = Function::exactIntegral(a, b);
                std::cout << "Точное значение:           " << exact << "\n";
                std::cout << "Абсолютная погрешность:    " << std::abs(result - exact) << "\n";
            }
            
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
        
    } while (choice != 0);
}

int main(int argc, char* argv[]) {
    std::cout << std::fixed << std::setprecision(10);
    
    printHeader("ЧИСЛЕННОЕ ИНТЕГРИРОВАНИЕ");
    std::cout << "Функция: f(x) = 1/(x^2 + 4x + 3) = 1/((x+1)(x+3))\n";
    std::cout << "Параметры: n = 7, m = 10\n";
    
    const int n = 7;  // Количество узлов для заданий 2, 3, 5
    const int m = 10; // Количество итераций для задания 4
    
    // Выполняем все задания
    task1_exactIntegral();
    task2_leftRectangle(n);
    task3_midpointRule(n);
    task4_nonConvergence(m);
    task5_cauchyPrincipalValue(n);
    
    // Интерактивный режим (опционально)
    if (argc > 1 && std::string(argv[1]) == "--interactive") {
        interactiveMode();
    }
    
    return 0;
}
