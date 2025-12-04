#ifndef FUNCTION_H
#define FUNCTION_H

#include <cmath>

/**
 * @brief Класс для работы с функцией f(x) = 1/(x^2 + 4x + 3)
 */
class Function {
public:
    /**
     * @brief Вычисляет значение функции f(x) = 1/(x^2 + 4x + 3)
     * @param x Аргумент функции
     * @return Значение функции в точке x
     */
    static double evaluate(double x);
    
    /**
     * @brief Вычисляет первообразную F(x) = 1/2 * ln|(x+1)/(x+3)|
     * @param x Аргумент функции
     * @return Значение первообразной в точке x
     */
    static double antiderivative(double x);
    
    /**
     * @brief Вычисляет точное значение определенного интеграла
     * @param a Нижний предел интегрирования
     * @param b Верхний предел интегрирования
     * @return Точное значение интеграла
     */
    static double exactIntegral(double a, double b);
    
    /**
     * @brief Проверяет наличие особенностей на интервале
     * @param a Нижний предел
     * @param b Верхний предел
     * @return true, если есть особенности (полюсы)
     */
    static bool hasSingularity(double a, double b);
};

#endif // FUNCTION_H
