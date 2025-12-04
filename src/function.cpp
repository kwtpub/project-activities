#include "../include/function.h"
#include <stdexcept>
#include <string>

using namespace std;

double Function::evaluate(double x) {
    // f(x) = 1/(x^2 + 4x + 3) = 1/((x+1)(x+3))
    double denominator = x * x + 4 * x + 3;
    
    // Проверка на особенности
    if (abs(denominator) < 1e-10) {
        throw runtime_error("Singularity detected at x = " + to_string(x));
    }
    
    return 1.0 / denominator;
}

double Function::antiderivative(double x) {
    // Используем метод частичных дробей:
    // 1/((x+1)(x+3)) = 1/2 * (1/(x+1) - 1/(x+3))
    // F(x) = 1/2 * (ln|x+1| - ln|x+3|) = 1/2 * ln|(x+1)/(x+3)|
    
    double numerator = abs(x + 1);
    double denominator = abs(x + 3);
    
    if (numerator < 1e-10 || denominator < 1e-10) {
        throw runtime_error("Singularity in antiderivative at x = " + to_string(x));
    }
    
    return 0.5 * log(numerator / denominator);
}

double Function::exactIntegral(double a, double b) {
    // Вычисляем по формуле Ньютона-Лейбница: ∫[a,b] f(x)dx = F(b) - F(a)
    try {
        return antiderivative(b) - antiderivative(a);
    } catch (const runtime_error& e) {
        throw runtime_error("Cannot compute exact integral: " + string(e.what()));
    }
}

bool Function::hasSingularity(double a, double b) {
    // Особенности (полюсы) функции находятся в точках x = -1 и x = -3
    // где знаменатель x^2 + 4x + 3 = (x+1)(x+3) = 0
    
    const double singularities[] = {-1.0, -3.0};
    const double epsilon = 1e-10;
    
    for (double singularity : singularities) {
        // Проверяем, находится ли особенность строго внутри или на границе интервала
        if (singularity >= a - epsilon && singularity <= b + epsilon) {
            return true;
        }
    }
    
    return false;
}
