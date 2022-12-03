#pragma once
#include "Complex.h"

template<class T>
class Matrix {
    T * m_ptr;
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
    Matrix(const Matrix<T> & other) :  m_rows(other.m_rows), m_cols(other.m_cols) {  // конструктор копирования
        m_ptr = new T[m_rows * m_cols];
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                m_ptr[i * m_cols + j] = other.m_ptr[i * m_cols + j];
            }
        }
    }
    Matrix(Matrix<T> && other) :  m_rows(other.m_rows), m_cols(other.m_cols), m_ptr(other.m_ptr) {  // конструктор копирования
        other.m_ptr = nullptr;
        other.m_rows = other.m_cols = 0;
    }
    Matrix(const std::initializer_list<T> & lst) {  //  конструктор для ситуаций m = {1, 2, 3, 4, 5, 6}
        m_rows = lst.size();
        m_cols = 1;

        m_ptr = new T[m_rows * m_cols];
        for (int i = 0; i < m_rows; ++i) {
            m_ptr[i * m_cols + 0] = *(lst.begin() + i);
        }
    }
    Matrix(const std::initializer_list<std::initializer_list<T>> & lst) {  //  конструктор для ситуаций
        m_rows = lst.size();                                               //  m = {{1}, {2}, {3}, {4}, {5}, {6}}
        m_cols = lst.begin()->size();                                      //  m = {{1, 2, 3}, {4, 5, 6}}

        m_ptr = new T[m_rows * m_cols];
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                m_ptr[i * m_cols + 0] = *((lst.begin() + i)->begin() + j);
            }
        }
    }
};

