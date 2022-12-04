#include <iostream>
#include "Matrix.h"



int main() {
    Matrix<int> m1(3, 4);  // проверка конструкторов
    Matrix<int> m2(m1);
    Matrix<int> m3(std::move(m2));

    Matrix<int> m4 = {1, 2, 3, 4, 5, 6};
    Matrix<int> m5 = {{1, 2, 3}, {1, 2, 3}};

    Matrix<int> mul1 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {5, 2, 6, 7}, {8, 5, 8, 9}};

    std::cout << mul1 << "\n";
    std::cout << mul1 * 3 << "\n" << 3 * mul1 << "\n";
    std::cout << mul1 * mul1 << "\n";

    Matrix<int> add1(std::move(mul1));
    Matrix<int> add2 = {{1, 5, 2, 5}, {8, 5, 6, 1}, {2, 3, 6, 9}, {5, 2, 7, 8}};

    std::cout << add1 + add2 << "\n";
    add1 += add2;
    std::cout << add1 << "\n";


    return 0;
}
