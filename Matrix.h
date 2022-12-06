#pragma once

#include <limits>
#include <iomanip>
#include "Complex.h"

namespace linalg {
    template<class T = double>
    class Matrix {
        T *m_ptr;
        unsigned m_rows;
        unsigned m_cols;
    public:
        Matrix(int r = 0, int c = 1) {  // конструктор по умолчанию
            m_rows = r;
            m_cols = c;

            m_ptr = new T[m_rows * m_cols];
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_cols + j] = 0;
                }
            }
        }

        Matrix(const Matrix<T> &other) : m_rows(other.m_rows), m_cols(other.m_cols) {  // конструктор копирования
            m_ptr = new T[m_rows * m_cols];
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_cols + j] = other.m_ptr[i * m_cols + j];
                }
            }
        }

        Matrix(Matrix<T> &&other) noexcept: m_rows(other.m_rows), m_cols(other.m_cols),
                                            m_ptr(other.m_ptr) {  // конструктор копирования
            other.m_ptr = nullptr;
            other.m_rows = other.m_cols = 0;
        }

        Matrix(const std::initializer_list<T> &lst) {  //  конструктор для ситуаций m = {1, 2, 3, 4, 5, 6}
            m_rows = lst.size();
            m_cols = 1;

            m_ptr = new T[m_rows * m_cols];
            for (int i = 0; i < m_rows; ++i) {
                m_ptr[i * m_cols + 0] = *(lst.begin() + i);
            }
        }

        Matrix(const std::initializer_list<std::initializer_list<T>> &lst) {  //  конструктор для ситуаций
            m_rows = lst.size();                                               //  m = {{1}, {2}, {3}, {4}, {5}, {6}}
            m_cols = lst.begin()->size();                                      //  m = {{1, 2, 3}, {4, 5, 6}}

            m_ptr = new T[m_rows * m_cols];
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_cols + j] = *((lst.begin() + i)->begin() + j);
                }
            }
        }

        ~Matrix() {
            delete[] m_ptr;
        }

        // геттеры
        unsigned rows() { return m_rows; }
        unsigned rows() const { return m_rows; }
        unsigned cols() { return m_cols; }
        unsigned cols() const { return m_cols; }


        // перегрузка операторов
        Matrix<T> &operator=(const Matrix<T> &rhs) {  // копирующее присваивание
            if (this == &rhs) {
                return *this;
            }

            delete[] m_ptr;
            m_rows = rhs.m_rows;
            m_cols = rhs.m_cols;

            m_ptr = new T[m_rows * m_cols];
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_cols + j] = rhs.m_ptr[i * rhs.m_cols + j];
                }
            }
            return *this;
        }

        Matrix<T> &operator=(Matrix<T> &&rhs) noexcept {  // перемещающее присваивание
            if (this == &rhs) {
                return *this;
            }

            delete[] m_ptr;

            m_rows = rhs.m_rows;
            m_cols = rhs.m_cols;

            m_ptr = rhs.m_ptr;

            rhs.m_ptr = nullptr;
            rhs.m_rows = rhs.m_cols = 0;

            return *this;
        }

        //operator Matrix<T>() {

        //}

        // доступ к элементам
        class Proxy {
            T *ptr;
        public:
            Proxy(T *ptr) : ptr(ptr) {}

            T &operator[](unsigned idx) {
                return ptr[idx];
            }

            const T &operator[](unsigned idx) const {
                return ptr[idx];
            }
        };

        Proxy operator[](
                unsigned idx) {  // доступ к элементам через квадратные скобки (есть недостаток: проверка второго индекса)
            if (idx >= m_rows) {
                throw std::logic_error("index out of range\n");
            }
            return Proxy(&m_ptr[idx * m_cols]);
        }

        Proxy operator[](
                unsigned idx) const { // доступ к элементам для константной матрицы через квадратные скобки (есть недостаток: проверка второго индекса)
            if (idx >= m_rows) {
                throw std::logic_error("index out of range\n");
            }
            return Proxy(&m_ptr[idx * m_cols]);
        }

        T &operator()(int i, int j) {  // доступ к элементам через круглые скобки (вызов функции)
            if (i >= m_rows || j >= m_cols) {
                throw std::logic_error("index out of range\n");
            }
            return m_ptr[i * m_cols + j];
        }

        const T &operator()(int i,
                            int j) const { // доступ к элементам для константной матрицы через круглые скобки (вызов функции)
            if (i >= m_rows || j >= m_cols) {
                throw std::logic_error("index out of range\n");
            }
            return m_ptr[i * m_cols + j];
        }

        // арифметические операции
        Matrix<T> operator+=(const Matrix<T> &rhs) {
            if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
                throw std::logic_error("matrix dimensions are not matching\n");
            }

            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_rows + j] += rhs.m_ptr[i * rhs.m_rows + j];
                }
            }

            return *this;
        }

        friend Matrix<T> operator+(Matrix<T> lhs, const Matrix<T> &rhs) {
            lhs += rhs;
            return lhs;
        }

        Matrix<T> operator-=(const Matrix<T> &rhs) {
            if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
                throw std::logic_error("matrix dimensions are not matching\n");
            }

            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_rows + j] -= rhs.m_ptr[i * rhs.m_rows + j];
                }
            }

            return *this;
        }

        friend Matrix<T> operator-(Matrix<T> lhs, const Matrix<T> &rhs) {
            lhs -= rhs;
            return lhs;
        }

        friend Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs) {
            if (lhs.m_cols != rhs.m_rows) {
                throw std::logic_error("matrix dimensions are not matching\n");
            }

            Matrix<T> tmp(lhs.m_rows, rhs.m_cols);
            for (int i = 0; i < lhs.m_rows; ++i) {
                for (int j = 0; j < rhs.m_cols; ++j) {
                    for (int k = 0; k < lhs.m_cols; ++k) {
                        tmp(i, j) += lhs(i, k) * rhs(k, j);
                    }
                }
            }

            return tmp;
        }

        Matrix<T> &operator*=(T k) {
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_ptr[i * m_cols + j] *= k;
                }
            }

            return *this;
        }

        friend Matrix<T> operator*(T k, Matrix<T> rhs) {
            rhs *= k;
            return rhs;
        }

        friend Matrix<T> operator*(Matrix<T> lhs, T k) {
            lhs *= k;
            return lhs;
        }

        // взаимодействие с потоком вывода и оператором <<
        friend std::ostream &operator<<(std::ostream &out, const Matrix<T> &m) {
            for (int i = 0; i < m.m_rows; ++i) {
                out << '|';
                for (int j = 0; j < m.m_cols; ++j) {
                    out << std::scientific << std::setprecision(4) << " " << std::right << std::setw(7) << m(i, j);
                    if (j != m.m_cols - 1) {
                        out << " ";
                    }
                }
                out << "|\n";
            }
            return out;
        }

        // функционал матрицы
        friend void getDecreasedMatrix(const Matrix<T> & mat, Matrix<T> & tmp, int p, int q) { // вырезаем строчку и столбец
            unsigned n = mat.m_rows;
            int i = 0, j = 0;

            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    if (row != p && col != q) {
                        tmp(i, j++) = mat(row, col);
                        if (j == n - 1) {
                            j = 0;
                            i++;
                        }
                    }
                }
            }
        }

        T det() const {  // определитель (раскладываем по первой строчке, рекурентно)
            if (m_rows != m_cols) {
                throw std::logic_error("not a square matrix\n");
            }

            if (m_rows == 1) {
                return (*this)(0, 0);
            }

            T d = 0;
            int sgn = 1;
            Matrix<T> tmp(m_rows - 1, m_rows - 1);
            for (int i = 0; i < m_rows; ++i) {
                getDecreasedMatrix(*this, tmp, 0, i);
                d += sgn * (*this)(0, i) * tmp.det();
                sgn *= -1;
            }

            return d;
        }

        friend void row_swap(Matrix<T> & to_swap, int r1, int r2, int c) {  // меняем строчки
            for (int i = 0; i < c; ++i) {
                std::swap(to_swap(r1, i), to_swap(r2, i));
            }
        }

        // специализация поиска ранга для комплексных чисел
        template<class T_>
        struct rows_manipulation {
            static void change(Matrix<> & tmp, int col, int row, int r) {
                double m = (double) tmp(col, row) / tmp(row, row);
                for (int i = 0; i < tmp.cols(); ++i) {
                    tmp(col, i) -= m * tmp(row, i);
                }
            }
            static void row_reducing(Matrix<T_> res, int r, int m_rows, int m_cols) {
                Matrix<> tmp(res.rows(), res.cols());
                for (int i = 0; i < tmp.rows(); ++i) {
                    for (int j = 0; j < tmp.cols(); ++j) {
                        tmp(i, j) = (double) res(i, j);
                    }
                }
                for (int row = 0; row < r; ++row) {
                    if (tmp(row, row) != 0) {
                        for (int col = 0; col < m_rows; ++col) {
                            if (col != row) {
                                rows_manipulation<T_>::change(tmp, col, row, r);
                            }
                        }
                    }
                    else {
                        bool to_reduce = true;
                        for (int i = row + 1; i < m_rows; ++i) {
                            if (tmp(i, row) <= std::numeric_limits<T_>::epsilon()) {
                                row_swap(tmp, row, i, r);
                                to_reduce = false;
                                break;
                            }
                        }

                        if (to_reduce) {
                            r--;
                            for (int i = 0; i < m_rows; ++i) {
                                tmp(i, row) = tmp(i, r);
                            }
                        }
                        row--;
                    }
                }
                std::cout << "\n" << tmp;
            }
        };
        template<class T_>
        struct rows_manipulation<Complex<T_>> {
            static void change(Matrix<Complex<>> & tmp, int col, int row, int r) {
                T_ a = tmp(col, row).real();
                T_ b = tmp(col, row).imag();
                T_ c = tmp(row, row).real();
                T_ d = tmp(row, row).imag();
                Complex<> m((a * c + b * d) / (c * c + d * d), (b * c + a * d) / (c * c + d * d));
                for (int i = 0; i < tmp.cols(); ++i) {
                    Complex<> to_subtract(tmp(row, i).real(), tmp(row, i).imag());
                    tmp(col, i) -= m * to_subtract;
                }
            }
            static void row_reducing(Matrix<Complex<T_>> & res, int & r, int m_rows, int m_cols) {
                Matrix<Complex<>> tmp(res.rows(), res.cols());
                for (int i = 0; i < tmp.rows(); ++i) {
                    for (int j = 0; j < tmp.cols(); ++j) {
                        tmp(i, j).real((double) res(i, j).real());
                        tmp(i, j).imag((double) res(i, j).imag());
                    }
                }
                for (int row = 0; row < r; ++row) {
                    if (tmp(row, row) != 0) {
                        for (int col = 0; col < m_rows; ++col) {
                            if (col != row) {
                                rows_manipulation<Complex<T_>>::change(tmp, col, row, r);
                            }
                        }
                    }
                    else {
                        bool to_reduce = true;
                        for (int i = row + 1; i < m_rows; ++i) {
                            if (tmp(i, row) <= std::numeric_limits<T_>::epsilon()) {
                                row_swap(tmp, row, i, r);
                                to_reduce = false;
                                break;
                            }
                        }

                        if (to_reduce) {
                            r--;
                            for (int i = 0; i < m_rows; ++i) {
                                tmp(i, row) = tmp(i, r);
                            }
                        }
                        row--;
                    }
                }
            }
        };

        // сама функция ранга
        int rank() {
            Matrix<T> tmp = (*this);
            int r = std::min(m_rows, m_cols);

            rows_manipulation<T>::row_reducing(tmp, r, m_rows, m_cols);

            return r;
        }

        // структуры для спецификации вычисления нормы у матрицы с комплексными числами
        template <class T_>
        struct sqr_func {
            static double sqr_abs(T_ el) {
                return el * el;
            }
        };

        template <class T_>
        struct sqr_func<Complex<T_>> {
            static double sqr_abs(Complex<T_> el) {
                return el.sqr_abs();
            }
        };

        // норма матрицы
        double norm() {
            double n = 0;

            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    n += sqr_func<T>::sqr_abs((*this)[i][j]);
                }
            }

            return sqrt(n);
        }

        // след матрицы
        T trace() {
            T tr = 0;
            for (int i = 0; i < std::min(m_rows, m_cols); ++i) {
                tr += m_ptr[i * m_cols + i];
            }

            return tr;
        }

        // транспонирование матрицы
        friend Matrix<T> transpose(const Matrix<T> & m) {
            Matrix<T> tmp(m.m_cols, m.m_rows);

            for (int i = 0; i < m.m_cols; ++i) {
                for (int j = 0; j < m.m_rows; ++j) {
                    tmp(i, j) = m(j, i);
                }
            }

            return tmp;
        }

        // специализация поиска обратной матрицы для комплексных чисел
        template<class T_>
        struct adj_func {
            static void getDecreasedMatrix(const Matrix<T_> & mat, Matrix<T_> & tmp, int p, int q) {
                unsigned n = mat.rows();
                int i = 0, j = 0;

                for (int row = 0; row < n; row++) {
                    for (int col = 0; col < n; col++) {
                        if (row != p && col != q) {
                            tmp(i, j++) = mat(row, col);
                            if (j == n - 1) {
                                j = 0;
                                i++;
                            }
                        }
                    }
                }
            }
            static void get_adj(const Matrix<T_> & mat, Matrix<> & res) {
                if (mat.rows() != res.rows() || mat.cols() != res.cols()) {
                    throw std::logic_error("matrix dimensions are not matching\n");
                }
                if (mat.rows() != res.cols()) {
                    throw std::logic_error("not a square matrix\n");
                }
                T_ mat_det = mat.det();
                for (int i = 0; i < res.rows(); ++i) {
                    for (int j = 0; j < res.cols(); ++j) {
                        Matrix<T> tmp(mat.rows() - 1, mat.rows() - 1);
                        getDecreasedMatrix(mat, tmp, i, j);
                        int sgn = (i + j) % 2 == 0 ? 1 : -1;
                        res(j, i) = (double) sgn * tmp.det() / mat_det;
                    }
                }
            }
        };
        template<class T_>
        struct adj_func<Complex<T_>> {
            static void getDecreasedMatrix(const Matrix<Complex<T_>> & mat, Matrix<Complex<T_>> & tmp, int p, int q) {
                unsigned n = mat.rows();
                int i = 0, j = 0;

                for (int row = 0; row < n; row++) {
                    for (int col = 0; col < n; col++) {
                        if (row != p && col != q) {
                            tmp(i, j++) = mat(row, col);
                            if (j == n - 1) {
                                j = 0;
                                i++;
                            }
                        }
                    }
                }
            }
            static void get_adj(const Matrix<Complex<T_>> & mat, Matrix<Complex<>> & res) {
                if (mat.rows() != res.rows() || mat.cols() != res.cols()) {
                    throw std::logic_error("matrix dimensions are not matching\n");
                }
                if (mat.rows() != res.cols()) {
                    throw std::logic_error("not a square matrix\n");
                }
                Complex<T_> mat_det = mat.det();
                for (int i = 0; i < res.rows(); ++i) {
                    for (int j = 0; j < res.cols(); ++j) {
                        Matrix<Complex<T_>> tmp(mat.rows() - 1, mat.rows() - 1);
                        getDecreasedMatrix(mat, tmp, i, j);
                        int sgn = (i + j) % 2 == 0 ? 1 : -1;
                        Complex<T_> tmp_det = tmp.det();
                        res(j, i).real((double) sgn * tmp_det.real());
                        res(j, i).imag((double) sgn * tmp_det.imag());
                        T_ a = res(j, i).real();
                        T_ b = res(j, i).imag();
                        T_ c = mat_det.real();
                        T_ d = mat_det.imag();

                        res(j, i).real((double) (a * c + b * d) / (c * c + d * d));
                        res(j, i).imag((double) (b * c - a * d) / (c * c + d * d));
                    }
                }
            }
        };

        // реализацию вынесем за класс
        template<class T1>
        friend Matrix<> inv(const Matrix<T1> & m);
        template<class T1>
        friend Matrix<Complex<>> inv(const Matrix<Complex<T1>> & m);

        // возведение в степень
        friend Matrix<T> pow(const Matrix<T> & m, int n) {
            Matrix<T> tmp(m);
            for (int i = 0; i < n - 1; ++i) {
                tmp = tmp * m;
            }

            return tmp;
        }

        // бинарное возведение в степень
        friend Matrix<T> bin_pow(const Matrix<T> & m, int n) {
            if (n == 1) {
                return m;
            }

            Matrix<T> tmp(m);
            if (n % 2 != 0) {
                return tmp * bin_pow(tmp, n - 1);
            }
            tmp = bin_pow(tmp, n / 2);
            return tmp * tmp;
        }
    };

    // реализация поиска обратной матрицы
    template<class T>
    Matrix<> inv(const Matrix<T> & m) {
        if (Matrix<T>::template sqr_func<T>::sqr_abs(m.det()) <= std::numeric_limits<double>::epsilon()) {
            throw std::logic_error("matrix is singular\n");
        }

        Matrix<> res(m.m_rows, m.m_cols);

        Matrix<T>::template adj_func<T>::get_adj(m, res);

        return res;
    }
    template<class T>
    Matrix<Complex<>> inv(const Matrix<Complex<T>> & m) {
        if (Matrix<Complex<T>>::template sqr_func<Complex<T>>::sqr_abs(m.det()) <= std::numeric_limits<double>::epsilon()) {
            throw std::logic_error("matrix is singular\n");
        }

        Matrix<Complex<>> res(m.m_rows, m.m_cols);

        Matrix<Complex<T>>::template adj_func<Complex<T>>::get_adj(m, res);

        return res;
    }
}
