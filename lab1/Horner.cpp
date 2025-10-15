#include <iostream>
#include <vector>
#include <iomanip>

// Функция для вывода многочлена в читаемом виде
void printPolynomial(const std::vector<double>& coeffs) {
    int n = coeffs.size() - 1;
    for (int i = 0; i < coeffs.size(); ++i) {
        if (coeffs[i] != 0) {
            if (i != 0 && coeffs[i] > 0) {
                std::cout << " + ";
            } else if (coeffs[i] < 0) {
                std::cout << " - ";
            }
            
            if (std::abs(coeffs[i]) != 1 || n - i == 0) {
                 std::cout << std::abs(coeffs[i]);
            }

            if (n - i > 0) {
                std::cout << "x";
                if (n - i > 1) {
                    std::cout << "^" << n - i;
                }
            }
        }
    }
    std::cout << " = 0" << std::endl;
}


// Функция для применения схемы Горнера и вывода таблицы
std::vector<double> hornerMethod(const std::vector<double>& coeffs, double c) {
    int n = coeffs.size();
    std::vector<double> result(n);
    result[0] = coeffs[0];

    // Вывод таблицы
    std::cout << std::string(8 * n, '-') << std::endl;
    std::cout << "      |";
    for(const auto& coeff : coeffs) {
        std::cout << std::setw(7) << coeff;
    }
    std::cout << std::endl;

    std::cout << std::setw(5) << c << " |";
    std::cout << std::setw(7) << " ";
    for (int i = 1; i < n; ++i) {
        result[i] = coeffs[i] + result[i - 1] * c;
        std::cout << std::setw(7) << result[i-1] * c;
    }
    std::cout << std::endl << std::string(8 * n, '-') << std::endl;

    std::cout << "      |";
     for(const auto& res : result) {
        std::cout << std::setw(7) << res;
    }
    std::cout << std::endl << std::string(8 * n, '-') << std::endl;

    return result;
}

// Функция для поиска верхней границы
double findUpperBound(const std::vector<double>& coeffs) {
    // Начинаем проверку с 1
    for (int c = 1; c <= 100; ++c) { // Ограничим поиск для примера
        std::cout << "\nПроверка C = " << c << " для верхней границы:" << std::endl;
        std::vector<double> result = hornerMethod(coeffs, c);
        bool all_non_negative = true;
        for (double val : result) {
            if (val < 0) {
                all_non_negative = false;
                break;
            }
        }
        if (all_non_negative) {
            std::cout << "\nВсе коэффициенты в последней строке неотрицательны." << std::endl;
            return c;
        }
    }
    return -1; // Если граница не найдена
}

// Функция для поиска нижней границы
double findLowerBound(const std::vector<double>& coeffs) {
     // Создаем многочлен P(-x)
    std::vector<double> p_neg_x_coeffs = coeffs;
    for (size_t i = 0; i < p_neg_x_coeffs.size(); ++i) {
        if ((p_neg_x_coeffs.size() - 1 - i) % 2 != 0) { // Нечетные степени x
            p_neg_x_coeffs[i] *= -1;
        }
    }

    // Если старший коэффициент отрицательный, меняем знаки у всех
    if (p_neg_x_coeffs[0] < 0) {
        for (double& coeff : p_neg_x_coeffs) {
            coeff *= -1;
        }
    }
    
    std::cout << "\n--- Поиск нижней границы для P(x) ---" << std::endl;
    std::cout << "Для этого найдем верхнюю границу для P(-x)." << std::endl;
    std::cout << "Модифицированный многочлен P(-x): ";
    printPolynomial(p_neg_x_coeffs);


    double upper_bound_for_neg_x = findUpperBound(p_neg_x_coeffs);

    if (upper_bound_for_neg_x != -1) {
        return -upper_bound_for_neg_x;
    }

    return 1; // Если граница не найдена
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Коэффициенты многочлена x^3 + 3x^2 + 12x + 3 = 0
    std::vector<double> coeffs = {1, 3, 12, 3};

    std::cout << "Исходный многочлен: ";
    printPolynomial(coeffs);
    std::cout << std::endl;

    // --- Верхняя граница ---
    std::cout << "--- Поиск верхней границы для P(x) ---" << std::endl;
    bool has_positive_coeffs_only = true;
    for(double coeff : coeffs) {
        if (coeff <= 0) {
            has_positive_coeffs_only = false;
            break;
        }
    }

    if (has_positive_coeffs_only) {
        std::cout << "Все коэффициенты многочлена положительны, следовательно, у него нет положительных действительных корней." << std::endl;
        std::cout << "Верхняя граница действительных корней: 0" << std::endl;
    } else {
         double upperBound = findUpperBound(coeffs);
         std::cout << "Верхняя граница действительных корней: " << upperBound << std::endl;
    }
   

    // --- Нижняя граница ---
    double lowerBound = findLowerBound(coeffs);
    std::cout << "\nНайдена верхняя граница для P(-x): " << -lowerBound << std::endl;
    std::cout << "Следовательно, нижняя граница для P(x) равна: " << lowerBound << std::endl;
    
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "Итог: действительные корни многочлена находятся в интервале [" << lowerBound << ", 0]." << std::endl;
    std::cout << "=======================================================" << std::endl;


    return 0;
}
