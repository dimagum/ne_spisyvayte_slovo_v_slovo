#include <iostream>
#include "Matrix.h"



int main() {
    linalg::Matrix<int> m1(3, 4);  // проверка конструкторов
    linalg::Matrix<int> m2(m1);
    linalg::Matrix<int> m3(std::move(m2));

    linalg::Matrix<int> m4 = {1, 2, 3, 4, 5, 6};
    linalg::Matrix<int> m5 = {{1, 2, 3}, {1, 2, 3}};

    linalg::Matrix<int> mul1 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {5, 2, 6, 7}, {8, 5, 8, 9}};

    std::cout << mul1 << "\n";  // проверка перегруженных операторов
    std::cout << mul1 * 3 << "\n" << 3 * mul1 << "\n";
    std::cout << mul1 * mul1 << "\n";

    linalg::Matrix<int> add1(std::move(mul1));
    linalg::Matrix<int> add2 = {{1, 5, 2, 5}, {8, 5, 6, 1}, {2, 3, 6, 9}, {5, 2, 7, 8}};

    std::cout << add1 + add2 << "\n";
    add1 += add2;
    std::cout << add1 << "\n";

    Complex<int> c1(3, 4);
    std::cout << c1 << "\n" << c1 * c1 << "\n" << c1.abs() << "\n" << c1.sqr_abs() << "\n";
    Complex<int> c2(5, 2);
    std::cout << c1 * c2 << "\n" << c1 + c2 << "\n" << c1 - c2 << "\n";

    linalg::Matrix<int> to_det = {{1, 1, 1}, {2, 2, 1}, {1, 2, 2}};

    std::cout << to_det.det();

    linalg::Matrix<int> to_norm(std::move(to_det));

    std::cout << to_norm.norm() << "\n";

    linalg::Matrix<Complex<int>> to_norm_complex = {{Complex<int>(7, 1), Complex<int>(5, 1), Complex<int>(1, 5)},
                                                    {Complex<int>(9, 2), Complex<int>(7, 2), Complex<int>(4, 8)},
                                                    {Complex<int>(4, 1), Complex<int>(8, 3), Complex<int>(7, 2)}};

    std::cout << to_norm_complex.norm() << "\n";
    std::cout << to_norm_complex.det() << "\n";

    linalg::Matrix<int> inv1 = {{1, 1, 1}, {2, 2, 1}, {1, 2, 2}};

    std::cout << inv1 << "\n" << inv(inv1) << "\n";

    linalg::Matrix<> inv2 = {{1, 1, 1}, {2, 2, 1}, {1, 2, 2}};

    std::cout << inv2 * inv(inv2) << "\n";

    return 0;
}
