#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <functional>
#include <vector>

/**
 * @brief Класс с методами численного интегрирования
 */
class Integration {
public:
    /**
     * @brief Метод левых прямоугольников
     * @param f Интегрируемая функция
     * @param a Нижний предел
     * @param b Верхний предел
     * @param n Количество узлов (разбиений)
     * @return Приближенное значение интеграла
     */
    static double leftRectangle(std::function<double(double)> f, double a, double b, int n);
    
    /**
     * @brief Метод средних прямоугольников (средних точек)
     * @param f Интегрируемая функция
     * @param a Нижний предел
     * @param b Верхний предел
     * @param n Количество узлов (разбиений)
     * @return Приближенное значение интеграла
     */
    static double midpointRule(std::function<double(double)> f, double a, double b, int n);
    
    /**
     * @brief Метод трапеций
     * @param f Интегрируемая функция
     * @param a Нижний предел
     * @param b Верхний предел
     * @param n Количество узлов (разбиений)
     * @return Приближенное значение интеграла
     */
    static double trapezoidalRule(std::function<double(double)> f, double a, double b, int n);
    
    /**
     * @brief Демонстрирует отсутствие сходимости метода трапеций при наличии особенностей
     * @param f Интегрируемая функция
     * @param a Нижний предел
     * @param b Верхний предел
     * @param maxIterations Максимальное число итераций
     * @return Вектор пар (количество узлов, значение интеграла)
     */
    static std::vector<std::pair<int, double>> demonstrateNonConvergence(
        std::function<double(double)> f, double a, double b, int maxIterations);
    
    /**
     * @brief Вычисляет главное значение интеграла по Коши
     * Для функции с особенностью в точке c на интервале [a, b]:
     * P.V. ∫[a,b] f(x)dx = lim(ε→0) [∫[a,c-ε] f(x)dx + ∫[c+ε,b] f(x)dx]
     * 
     * @param f Интегрируемая функция
     * @param a Нижний предел
     * @param b Верхний предел
     * @param singularity Точка особенности
     * @param n Количество узлов для каждого подинтервала
     * @param epsilon Малое значение для исключения окрестности особенности
     * @return Главное значение интеграла по Коши
     */
    static double cauchyPrincipalValue(std::function<double(double)> f, 
                                      double a, double b, 
                                      double singularity,
                                      int n, 
                                      double epsilon = 1e-6);
};

#endif // INTEGRATION_H
