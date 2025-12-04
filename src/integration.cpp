#include "../include/integration.h"
#include <cmath>
#include <stdexcept>

double Integration::leftRectangle(std::function<double(double)> f, double a, double b, int n) {
    if (n <= 0) {
        throw std::invalid_argument("Number of nodes must be positive");
    }
    
    double h = (b - a) / n;  // Ширина одного интервала
    double sum = 0.0;
    
    // Суммируем значения функции в левых концах интервалов
    for (int i = 0; i < n; ++i) {
        double x = a + i * h;
        sum += f(x);
    }
    
    return sum * h;
}

double Integration::midpointRule(std::function<double(double)> f, double a, double b, int n) {
    if (n <= 0) {
        throw std::invalid_argument("Number of nodes must be positive");
    }
    
    double h = (b - a) / n;  // Ширина одного интервала
    double sum = 0.0;
    
    // Суммируем значения функции в средних точках интервалов
    for (int i = 0; i < n; ++i) {
        double x_mid = a + (i + 0.5) * h;  // Средняя точка i-го интервала
        sum += f(x_mid);
    }
    
    return sum * h;
}

double Integration::trapezoidalRule(std::function<double(double)> f, double a, double b, int n) {
    if (n <= 0) {
        throw std::invalid_argument("Number of nodes must be positive");
    }
    
    double h = (b - a) / n;  // Ширина одного интервала
    double sum = 0.5 * (f(a) + f(b));  // Граничные точки с коэффициентом 1/2
    
    // Суммируем значения функции во внутренних узлах
    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += f(x);
    }
    
    return sum * h;
}

std::vector<std::pair<int, double>> Integration::demonstrateNonConvergence(
    std::function<double(double)> f, double a, double b, int maxIterations) {
    
    std::vector<std::pair<int, double>> results;
    
    // Начинаем с малого числа узлов и постепенно увеличиваем
    for (int n = 2; n <= maxIterations; ++n) {
        try {
            double integral = trapezoidalRule(f, a, b, n);
            results.push_back({n, integral});
        } catch (const std::exception& e) {
            // Если возникает ошибка (например, деление на ноль в особой точке),
            // записываем NaN
            results.push_back({n, std::nan("")});
        }
    }
    
    return results;
}

double Integration::cauchyPrincipalValue(std::function<double(double)> f, 
                                        double a, double b, 
                                        double singularity,
                                        int n, 
                                        double epsilon) {
    
    // Проверяем, что особенность находится внутри интервала
    if (singularity <= a || singularity >= b) {
        throw std::invalid_argument("Singularity must be inside the interval (a, b)");
    }
    
    // Проверяем параметры
    if (epsilon <= 0 || epsilon >= std::min(singularity - a, b - singularity)) {
        throw std::invalid_argument("Epsilon must be positive and smaller than distance to boundaries");
    }
    
    // Разбиваем интеграл на два подинтервала, исключая окрестность особенности:
    // ∫[a, singularity-ε] f(x)dx + ∫[singularity+ε, b] f(x)dx
    
    double integral1 = 0.0;
    double integral2 = 0.0;
    
    // Первый интервал: [a, singularity - epsilon]
    if (singularity - epsilon > a) {
        integral1 = midpointRule(f, a, singularity - epsilon, n);
    }
    
    // Второй интервал: [singularity + epsilon, b]
    if (singularity + epsilon < b) {
        integral2 = midpointRule(f, singularity + epsilon, b, n);
    }
    
    return integral1 + integral2;
}
