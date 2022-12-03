#include <iostream>
#include "Matrix.h"



int main() {
    Matrix<int> m1(3, 4);  // проверка конструкторов
    Matrix<int> m2(m1);
    Matrix<int> m3(std::move(m2));

    Matrix<int> m4 = {1, 2, 3, 4, 5, 6};
    Matrix<int> m5 = {{1, 2, 3}, {1, 2, 3}};


    return 0;
}
