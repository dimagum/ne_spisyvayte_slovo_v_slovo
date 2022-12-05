#pragma once

#include <cmath>

template<class T = double>
class Complex {
    T re;
    T im;
public:
    Complex(T re = 0, T im = 0) : re(re), im(im) {}
    Complex(const Complex<T> & other) : re(other.re), im(other.im) {}

    T real() { return re; }
    T imag() { return im; }

    void real(T val) { this->re = val; }
    void imag(T val) { this->im = val; }

    Complex<T> & operator=(const Complex<T> & rhs) {
        this->re = rhs.re;
        this->im = rhs.im;
        return *this;
    }

    Complex<T> & operator=(T rhs) {
        this->re = rhs;
        this->im = 0;
        return *this;
    }

    Complex<T> & operator+=(T number) {
        this->re += number;
        return *this;
    }

    friend Complex<T> operator+(Complex<T> lhs, T number) {
        lhs += number;
        return lhs;
    }

    Complex<T> & operator-=(T number) {
        this->re -= number;
        return *this;
    }

    friend Complex<T> operator-(Complex<T> lhs, T number) {
        lhs -= number;
        return lhs;
    }

    Complex<T> & operator*=(T number) {
        this->re *= number;
        this->im *= number;
        return *this;
    }

    friend Complex<T> operator*(Complex<T> lhs, T rhs) {
        lhs *= rhs;
        return lhs;
    }

    Complex<T> & operator+=(const Complex<T> & rhs) {
        this->re += rhs.re;
        this->im += rhs.im;
        return *this;
    }

    friend Complex<T> operator+(Complex<T> lhs, const Complex<T> & rhs) {
        lhs += rhs;
        return lhs;
    }

    Complex<T> & operator-=(const Complex<T> & rhs) {
        this->re -= rhs.re;
        this->im -= rhs.im;
        return *this;
    }

    friend Complex<T> operator-(Complex<T> lhs, const Complex<T> & rhs) {
        lhs -= rhs;
        return lhs;
    }

    Complex<T> & operator*=(const Complex<T> & rhs) {
        T a = this->re;
        T b = this->im;
        T c = rhs.re;
        T d = rhs.im;
        this->re = a * c - b * d;
        this->im = b * c + a * d;
        return *this;
    }

    friend Complex<T> operator*(Complex<T> lhs, const Complex<T> & rhs) {
        lhs *= rhs;
        return lhs;
    }


    friend bool operator==(const Complex<T> & lhs, const Complex<T> & rhs) {
        return (std::abs(lhs.re - rhs.re) <= std::numeric_limits<T>::epsilon() && std::abs(lhs.im - rhs.im) <= std::numeric_limits<T>::epsilon());
    }
    friend bool operator!=(const Complex<T> & lhs, const Complex<T> & rhs) {
        return !(lhs == rhs);
    }
    friend bool operator>(const Complex<T> & lhs, const Complex<T> & rhs) {
        return ((lhs.re * lhs.re + lhs.im * lhs.im) > (rhs.re * rhs.re + rhs.im * rhs.im));
    }
    friend bool operator<=(const Complex<T> & lhs, const Complex<T> & rhs) {
        return !(lhs > rhs);
    }
    friend bool operator<(const Complex<T> & lhs, const Complex<T> & rhs) {
        return ((lhs.re * lhs.re + lhs.im * lhs.im) < (rhs.re * rhs.re + rhs.im * rhs.im));
    }
    friend bool operator>=(const Complex<T> & lhs, const Complex<T> & rhs) {
        return !(lhs < rhs);
    }

    friend bool operator==(const Complex<T> & lhs, T rhs) {
        return (std::abs(lhs.re - rhs) <= std::numeric_limits<T>::epsilon() && std::abs(lhs.im - 0) <= std::numeric_limits<T>::epsilon());
    }
    friend bool operator!=(const Complex<T> & lhs, T rhs) {
        return !(lhs == rhs);
    }
    friend bool operator>(const Complex<T> & lhs, T rhs) {
        return ((lhs.re * lhs.re + lhs.im * lhs.im) > (rhs * rhs + 0 * 0));
    }
    friend bool operator<=(const Complex<T> & lhs, T rhs) {
        return !(lhs > rhs);
    }
    friend bool operator<(const Complex<T> & lhs, T rhs) {
        return ((lhs.re * lhs.re + lhs.im * lhs.im) < (rhs * rhs + 0 * 0));
    }
    friend bool operator>=(const Complex<T> & lhs, T rhs) {
        return !(lhs < rhs);
    }

    friend bool operator==(T lhs, const Complex<T> & rhs) {
        return rhs == lhs;
    }
    friend bool operator!=(T lhs, const Complex<T> & rhs) {
        return rhs != lhs;
    }
    friend bool operator>(T lhs, const Complex<T> & rhs) {
        return rhs < lhs;
    }
    friend bool operator<=(T lhs, const Complex<T> & rhs) {
        return rhs >= lhs;
    }
    friend bool operator<(T lhs, const Complex<T> & rhs) {
        return rhs > lhs;
    }
    friend bool operator>=(T lhs, const Complex<T> & rhs) {
        return rhs <= lhs;
    }


    friend Complex<T> operator!(Complex<T> c) {
        return Complex<T>(c.re, -c.im);
    }

    T sqr_abs() {
        Complex<T> p = (*this) * !(*this);
        return p.re + p.im;
    }
    T sqr_abs() const {
        Complex<T> p = (*this) * !(*this);
        return p.re + p.im;
    }

    double abs() {
        return sqrt(this->sqr_abs());
    }
    double abs() const {
        return sqrt(this->sqr_abs());
    }

    Complex<T> & operator/=(const Complex<T> & rhs) {
        if (rhs.sqr_abs()) {
            std::cout << "division by zero ";
            return *this;
        }
        (*this) = (*this) * (!rhs) / rhs.sqr_abs();
        return *this;
    }

    friend Complex<T> operator/(Complex<T> lhs, const Complex<T> & rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend std::ostream & operator<<(std::ostream & out, const Complex<T> & c) {

        if (c.re >= 0) {
            if (c.im >= 0) {
                out << std::scientific << std::setprecision(4) << " " << c.re << " " << "+ " << c.im << " * i ";
            }
            else {
                out << std::scientific << std::setprecision(4) << " " << c.re << " " << "- " << -c.im << " * i ";
            }
        }
        else {
            if (c.im >= 0) {
                out << std::scientific << std::setprecision(4) << "-" << -c.re << " " << "+ " << c.im << " * i ";
            }
            else {
                out << std::scientific << std::setprecision(4) << "-" << -c.re << " " << "- " << -c.im << " * i ";
            }
        }

        return out;
    }
};

