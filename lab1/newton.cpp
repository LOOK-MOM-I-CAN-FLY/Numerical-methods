#include <iostream>
#include <cmath>
#include <iomanip> // Для форматирования вывода

// Функция f(x) = (2-x)e^x
double f(double x) {
    return (2.0 - x) * exp(x);
}

// Производная f'(x) = (1-x)e^x
double f_prime(double x) {
    return (1.0 - x) * exp(x);
}

int main() {
    setlocale(LC_ALL, "Russian"); // Установка русской локали для вывода
    std::cout << "Метод Ньютона для уточнения корня уравнения (2-х)е^х=0" << std::endl;

    double x0; // Начальное приближение
    double epsilon = 0.001; // Требуемая точность
    int maxIterations = 100; // Максимальное количество итераций для предотвращения зацикливания

    // Поскольку графически мы отделили корень на x=2, выберем начальное приближение близко к нему.
    x0 = 2.5; 
    std::cout << "Начальное приближение x0: " << x0 << std::endl;
    std::cout << "Требуемая точность: " << epsilon << std::endl;

    double x_prev = x0;
    double x_next;
    int iteration = 0;

    std::cout << std::fixed << std::setprecision(5); // Установка точности вывода

    while (iteration < maxIterations) {
        // Проверка на ноль в знаменателе (f_prime(x_prev))
        if (f_prime(x_prev) == 0) {
            std::cerr << "Ошибка: Производная равна нулю в точке x = " << x_prev << ". Метод Ньютона неприменим." << std::endl;
            return 1;
        }

        x_next = x_prev - f(x_prev) / f_prime(x_prev);
        
        std::cout << "Итерация " << iteration + 1 << ": x = " << x_next << ", |x_next - x_prev| = " << std::abs(x_next - x_prev) << std::endl;

        if (std::abs(x_next - x_prev) < epsilon) {
            std::cout << "\nКорень найден с заданной точностью." << std::endl;
            std::cout << "Приближенное значение корня: " << x_next << std::endl;
            break;
        }

        x_prev = x_next;
        iteration++;
    }

    if (iteration == maxIterations) {
        std::cout << "\nДостигнуто максимальное количество итераций. Корень не найден с заданной точностью." << std::endl;
        std::cout << "Последнее приближенное значение корня: " << x_next << std::endl;
    }

    return 0;
}
