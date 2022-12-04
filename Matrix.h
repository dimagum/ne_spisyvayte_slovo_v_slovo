#pragma once

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
                    out << std::right << std::setw(7) << m(i, j);
                    if (j != m.m_cols - 1) {
                        out << " ";
                    }
                }
                out << "|\n";
            }
            return out;
        }

        // функционал матрицы
        friend void getDecreasedMatrix(const Matrix<T> & mat, Matrix<T> & tmp, int p, int q) {
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

        T det() const {
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

        int rank() {
            int r = std::min(m_rows, m_cols);


            return r;
        }

        // структуры для спецификации вычисления нормы у матрицы с комплексными числами
        template <class T_>
        struct norm_func {
            static double sqr_abs(T_ el) {
                return el * el;
            }
        };

        template <class T_>
        struct norm_func<Complex<T_>> {
            static double sqr_abs(Complex<T_> el) {
                return el.sqr_abs();
            }
        };

        double norm() {
            double n = 0;

            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    n += norm_func<T>::sqr_abs((*this)[i][j]);
                }
            }

            return sqrt(n);
        }

        T trace() {
            T tr = 0;
            for (int i = 0; i < std::min(m_rows, m_cols); ++i) {
                tr += m_ptr[i * m_cols + i];
            }

            return tr;
        }

        friend Matrix<T> transpose(const Matrix<T> & m) {
            Matrix<T> tmp(m.m_cols, m.m_rows);

            for (int i = 0; i < m.m_cols; ++i) {
                for (int j = 0; j < m.m_rows; ++j) {
                    tmp(i, j) = m(j, i);
                }
            }

            return tmp;
        }

        friend void get_adj(const Matrix<T> & mat, Matrix<> & res) {
            if (mat.m_rows != res.m_rows || mat.m_cols != res.m_cols) {
                throw std::logic_error("matrix dimensions are not matching\n");
            }
            if (mat.m_rows != res.m_cols) {
                throw std::logic_error("not a square matrix\n");
            }
            for (int i = 0; i < res.m_rows; ++i) {
                for (int j = 0; j < res.m_cols; ++j) {
                    Matrix<T> tmp(mat.m_rows - 1, mat.m_rows - 1);
                    getDecreasedMatrix(mat, tmp, i, j);
                    int sgn = (i + j) % 2 == 0 ? 1 : -1;
                    res(j, i) = (double) sgn * tmp.det();
                }
            }
        }

        friend Matrix<> inv(const Matrix<T> & m) {
            if (m.det() == 0) {
                throw std::logic_error("matrix is singular\n");
            }

            Matrix<> res(m.m_rows, m.m_cols);

            get_adj(m, res);

            // res *= ((double) 1 / m.det());

            return res;
        }
        // friend Matrix<Complex<>> inv(Matrix<Complex<T>> m);

        friend Matrix<T> pow(const Matrix<T> & m, int n) {
            Matrix<T> tmp(m);
            for (int i = 0; i < n - 1; ++i) {
                tmp = tmp * m;
            }

            return tmp;
        }
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
}
