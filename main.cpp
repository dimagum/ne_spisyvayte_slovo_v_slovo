#include <iostream>
#include "Matrix.h"
#include "Loaders.h"



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

    Complex<int> c1(3, 4);  // проверка комплексных чисел
    std::cout << c1 << "\n" << c1 * c1 << "\n" << c1.abs() << "\n" << c1.sqr_abs() << "\n";
    Complex<int> c2(5, 2);
    std::cout << c1 * c2 << "\n" << c1 + c2 << "\n" << c1 - c2 << "\n";

    // проверка функционала
    linalg::Matrix<int> to_det = {{1, 1, 1}, {2, 2, 1}, {1, 2, 2}};

    std::cout << "det: " << to_det.det() << "\n";

    linalg::Matrix<int> to_rank1 = {{1, 2, 3, 4}, {5, 2, 6, 7}, {9, 3, 5, 1}};

    std::cout << "rank: " << to_rank1.rank() << "\n";

    linalg::Matrix<Complex<int>> to_rank_complex1 = {{Complex<int>(7, 1), Complex<int>(5, 1), Complex<int>(1, 5), Complex<int>(9, 2)},
                                                    {Complex<int>(9, 2), Complex<int>(7, 2), Complex<int>(4, 8), Complex<int>(4, 3)},
                                                    {Complex<int>(4, 1), Complex<int>(8, 3), Complex<int>(7, 2), Complex<int>(1, 5)}};
    linalg::Matrix<Complex<int>> to_rank_complex2 = {{Complex<int>(7, 1), Complex<int>(5, 1), Complex<int>(1, 5), Complex<int>(9, 2)},
                                                     {Complex<int>(9, 2), Complex<int>(7, 2), Complex<int>(4, 8), Complex<int>(4, 3)},
                                                     {Complex<int>(7, 1), Complex<int>(5, 1), Complex<int>(1, 5), Complex<int>(9, 2)}};

    std::cout << "ranks complex: " << to_rank_complex1.rank() << " " << to_rank_complex2.rank() << "\n";

    linalg::Matrix<int> to_norm(std::move(to_det));

    std::cout << "norm: " << to_norm.norm() << "\n";

    linalg::Matrix<Complex<int>> to_norm_complex = {{Complex<int>(7, 1), Complex<int>(5, 1), Complex<int>(1, 5)},
                                                    {Complex<int>(9, 2), Complex<int>(7, 2), Complex<int>(4, 8)},
                                                    {Complex<int>(4, 1), Complex<int>(8, 3), Complex<int>(7, 2)}};

    std::cout << "norm complex: " << to_norm_complex.norm() << "\n";

    linalg::Matrix<Complex<int>> to_det_complex(std::move(to_norm_complex));

    std::cout << "det complex: " << to_det_complex.det() << "\n";

    linalg::Matrix<int> inv1 = {{1, 1, 1}, {2, 2, 1}, {1, 2, 2}};

    std::cout << inv1 << "\n" << "inverse:\n" << inv(inv1) << "\n";

    linalg::Matrix<> inv2 = {{1, 1, 1}, {2, 2, 1}, {1, 2, 2}};

    std::cout << "mat * inverse mat:\n" << inv2 * inv(inv2) << "\n";

    linalg::Matrix<Complex<int>> inv_complex(std::move(to_det_complex));

    std::cout << inv_complex << "\n" << "inverse complex:\n" << inv(inv_complex) << "\n";

    linalg::Matrix<Complex<>> inv_complex_double = {{Complex<double>(7, 1), Complex<double>(5, 1), Complex<double>(1, 5)},
                                                    {Complex<double>(9, 2), Complex<double>(7, 2), Complex<double>(4, 8)},
                                                    {Complex<double>(4, 1), Complex<double>(8, 3), Complex<double>(7, 2)}};

    std::cout << "mat complex * inverse mat complex:\n" << inv_complex_double << "\n" << inv(inv_complex_double)
              << "\n" << inv_complex_double * inv(inv_complex_double);

/*
    // тесты вывода в файлы и чтения из файлов
    // текстовые
    linalg::Matrix<int> m_init = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    linalg::TextMode<int>::write("matrix.txt", m_init);

    linalg::Matrix<int> m_new = linalg::TextMode<int>::read("matrix.txt");

    std::cout << m_new;

    linalg::Matrix<double> m_initd = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9}};

    linalg::TextMode<double>::write("matrixd.txt", m_initd);

    linalg::Matrix<double> m_newd = linalg::TextMode<double>::read("matrixd.txt");

    std::cout << m_newd;

    linalg::Matrix<Complex<int>> m_initci = {{Complex<int>(1, 1), Complex<int>(2, 2), Complex<int>(3, 3)},
                                             {Complex<int>(4, 4), Complex<int>(5, 5), Complex<int>(6, 6)},
                                             {Complex<int>(7, 7), Complex<int>(8, 8), Complex<int>(9, 9)}};

    linalg::TextMode<Complex<int>>::write("matrixci.txt", m_initci);

    linalg::Matrix<Complex<int>> m_newci = linalg::TextMode<Complex<int>>::read("matrixci.txt");

    std::cout << m_newci;

    linalg::Matrix<Complex<double>> m_initcd = {{Complex<double>(1.1, 1.1), Complex<double>(2.2, 2.2), Complex<double>(3.3, 3.3)},
                                                {Complex<double>(4.4, 4.4), Complex<double>(5.5, 5.5), Complex<double>(6.6, 6.6)},
                                                {Complex<double>(7.7, 7.7), Complex<double>(8.8, 8.8), Complex<double>(9.9, 9.9)}};

    linalg::TextMode<Complex<double>>::write("matrixcd.txt", m_initcd);

    linalg::Matrix<Complex<double>> m_newcd = linalg::TextMode<Complex<double>>::read("matrixcd.txt");

    std::cout << m_newcd;
*/

/*
    // бинарные
    linalg::Matrix<int> m_init_b = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    linalg::BinaryMode<int>::write("matrix.bin", m_init_b);

    linalg::Matrix<int> m_new1 = linalg::BinaryMode<int>::read("matrix.bin");

    std::cout << m_new1 << "\n";

    linalg::Matrix<Complex<double>> m_init_b_cd = {{Complex<double>(1.1, 1.1), Complex<double>(2.2, 2.2), Complex<double>(3.3, 3.3)},
                                       {Complex<double>(4.4, 4.4), Complex<double>(5.5, 5.5), Complex<double>(6.6, 6.6)},
                                       {Complex<double>(7.7, 7.7), Complex<double>(8.8, 8.8), Complex<double>(9.9, 9.9)}};

    linalg::BinaryMode<Complex<double>>::write("matrix.bin", m_init_b_cd);

    linalg::Matrix<Complex<double>> m_new1_cd = linalg::BinaryMode<Complex<double>>::read("matrix.bin");

    std::cout << m_new1_cd << "\n";

*/

    linalg::Matrix<int> check1 = {{1, 2} , {2, 3}};
    linalg::Matrix<int> check2 = {{1, 2, 3}, {3, 4, 5}};

    try {
        std::cout << check1 + check2 << "\n";
    }
    catch (std::logic_error & e) {
        std::cout << e.what() << "\n";
    }

    // проверка транспозиции
    std::cout << transpose(check2) << "\n";
    // проверка следа
    std::cout << check2.trace() << "\n";

    return 0;
}
