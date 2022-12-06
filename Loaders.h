#pragma once
#include "Matrix.h"
#include <fstream>
#include <sstream>

double string_to_double(const std::string & s) {
    std::istringstream i(s);
    double x;

    if (!(i >> x)) {
        return 0;
    }

    return x;
}

namespace linalg {
    template<class T>
    struct BinaryMode { };

    template<class T>
    struct TextMode { };

    template<>
    struct BinaryMode<int> {
        static void write(const std::string & file_name, const linalg::Matrix<int> & object) {
            std::ofstream file(file_name, std::fstream::binary);

            file << object.rows() << object.cols();
            for (int i = 0; i < object.rows(); ++i) {
                for (int j = 0; j < object.cols(); ++j) {
                    file << object(i, j);
                }
            }

            file.close();
        }

        static Matrix<int> read(const std::string & file_name) {
            std::ifstream file(file_name, std::fstream::binary);

            int r, c;
            file >> r >> c;

            Matrix<int> tmp(r, c);
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    file >> tmp(i, j);
                }
            }

            return tmp;
        }
    };

    template<>
    struct BinaryMode<double> {
        static void write(const std::string & file_name, const linalg::Matrix<double> & object) {
            std::ofstream file(file_name, std::ios::binary);

            file << object.rows() << object.cols();
            for (int i = 0; i < object.rows(); ++i) {
                for (int j = 0; j < object.cols(); ++j) {
                    file << object(i, j);
                }
            }

            file.close();
        }

        static Matrix<double> read(const std::string & file_name) {
            std::ifstream file(file_name, std::ios::binary);

            int r, c;
            file >> r >> c;

            Matrix<double> tmp(r, c);
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    file >> tmp(i, j);
                }
            }

            return tmp;
        }
    };

    template<>
    struct BinaryMode<Complex<int>> {
        static void write(const std::string & file_name, const linalg::Matrix<Complex<int>> & object) {
            std::ofstream file(file_name, std::ios::binary);

            file << object.rows() << object.cols();
            for (int i = 0; i < object.rows(); ++i) {
                for (int j = 0; j < object.cols(); ++j) {
                    file << object(i, j).real() << object(i, j).real();
                }
            }

            file.close();
        }

        static Matrix<Complex<int>> read(const std::string & file_name) {
            std::ifstream file(file_name, std::ios::binary);

            int r, c;
            file >> r >> c;

            Matrix<Complex<int>> tmp(r, c);
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    int re, im;
                    file >> re >> im;
                    tmp(i, j).real(re);
                    tmp(i, j).imag(im);
                }
            }

            return tmp;
        }
    };

    template<>
    struct BinaryMode<Complex<double>> {
        static void write(const std::string & file_name, const linalg::Matrix<Complex<double>> & object) {
            std::ofstream file(file_name, std::ios::binary);

            file << object.rows() << object.cols();
            for (int i = 0; i < object.rows(); ++i) {
                for (int j = 0; j < object.cols(); ++j) {
                    file << object(i, j).real() << object(i, j).real();
                }
            }

            file.close();
        }

        static Matrix<Complex<double>> read(const std::string & file_name) {
            std::ifstream file(file_name, std::ios::binary);

            int r, c;
            file >> r >> c;

            Matrix<Complex<double>> tmp(r, c);
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    int re, im;
                    file >> re >> im;
                    tmp(i, j).real(re);
                    tmp(i, j).imag(im);
                }
            }

            return tmp;
        }
    };

    template<>
    struct TextMode<int> {
        static void write(const std::string & file_name, const linalg::Matrix<int> & object) {
            std::ofstream file(file_name);

            file << "type: int\n" << "rows: " << object.rows() << "\n" << "columns: " << object.cols() << "\n";
            file << object;

            file.close();
        }

        static Matrix<int> read(const std::string & file_name) {
            std::ifstream file(file_name);

            std::string line;
            std::getline(file, line);
            std::getline(file, line);
            int r = line[line.length() - 1] - '0';
            std::getline(file, line);
            int c = line[line.length() - 1] - '0';

            Matrix<int> tmp(r, c);

            for (int i = 0; i < r; ++i) {
                int j = 0;
                std::getline(file, line);
                std::string number = "";
                for (char symbol : line) {
                    if ((symbol - '0') >= 0 && (symbol - '0') <= 9 || symbol == '-') {
                        number += symbol;
                    }
                    else if (!number.empty()) {
                        tmp(i, j) = std::stoi(number);
                        number = "";
                        j++;
                    }
                }
            }

            return tmp;
        }
    };

    template<>
    struct TextMode<double> {
        static void write(const std::string & file_name, const linalg::Matrix<double> & object) {
            std::ofstream file(file_name);

            file << "type: double\n" << "rows: " << object.rows() << "\n" << "columns: " << object.cols() << "\n";
            file << object;

            file.close();
        }

        static Matrix<double> read(const std::string & file_name) {
            std::ifstream file(file_name);

            std::string line;
            std::getline(file, line);
            std::getline(file, line);
            int r = line[line.length() - 1] - '0';
            std::getline(file, line);
            int c = line[line.length() - 1] - '0';

            Matrix<double> tmp(r, c);

            for (int i = 0; i < r; ++i) {
                int j = 0;
                std::getline(file, line);
                std::string number = "";
                for (char symbol : line) {
                    if ((symbol - '0') >= 0 && (symbol - '0') <= 9 || symbol == '.' || symbol == '-' || symbol == 'e' || symbol == '+') {
                        number += symbol;
                    }
                    else if (!number.empty()) {
                        tmp(i, j) = string_to_double(number);
                        number = "";
                        j++;
                    }
                }
            }

            return tmp;
        }
    };

    template<>
    struct TextMode<Complex<int>> {
        static void write(const std::string & file_name, const linalg::Matrix<Complex<int>> & object) {
            std::ofstream file(file_name);

            file << "type: Complex<int>\n" << "rows: " << object.rows() << "\n" << "columns: " << object.cols() << "\n";
            file << object;

            file.close();
        }

        static Matrix<Complex<int>> read(const std::string & file_name) {
            std::ifstream file(file_name);

            std::string line;
            std::getline(file, line);
            std::getline(file, line);
            int r = line[line.length() - 1] - '0';
            std::getline(file, line);
            int c = line[line.length() - 1] - '0';

            Matrix<Complex<int>> tmp(r, c);

            for (int i = 0; i < r; ++i) {
                char re_or_im = 'r';
                int j = 0;
                std::getline(file, line);
                std::string number = "";
                for (char symbol : line) {
                    if ((symbol - '0') >= 0 && (symbol - '0') <= 9 || symbol == '-') {
                        number += symbol;
                    }
                    else if (!number.empty()) {
                        if (re_or_im == 'r') {
                            tmp(i, j).real(std::stoi(number));
                            number = "";
                            re_or_im = 'i';
                        }
                        else if (re_or_im == 'i') {
                            tmp(i, j).imag(std::stoi(number));
                            number = "";
                            re_or_im = 'r';
                            j++;
                        }
                    }
                }
            }

            return tmp;
        }
    };

    template<>
    struct TextMode<Complex<double>> {
        static void write(const std::string & file_name, const linalg::Matrix<Complex<double>> & object) {
            std::ofstream file(file_name);

            file << "type: Complex<double>\n" << "rows: " << object.rows() << "\n" << "columns: " << object.cols() << "\n";
            file << object;

            file.close();
        }

        static Matrix<Complex<double>> read(const std::string & file_name) {
            std::ifstream file(file_name);

            std::string line;
            std::getline(file, line);
            std::getline(file, line);
            int r = line[line.length() - 1] - '0';
            std::getline(file, line);
            int c = line[line.length() - 1] - '0';

            Matrix<Complex<double>> tmp(r, c);

            for (int i = 0; i < r; ++i) {
                char re_or_im = 'r';
                char prev = '\0';
                int j = 0;
                std::getline(file, line);
                std::string number = "";
                for (char symbol : line) {
                    if ((symbol - '0') >= 0 && (symbol - '0') <= 9 || symbol == '.' || symbol == '-' || symbol == 'e' || (symbol == '+' && prev != ' ')) {
                        number += symbol;
                    }
                    else if (!number.empty()) {
                        if (re_or_im == 'r') {
                            tmp(i, j).real(string_to_double(number));
                            number = "";
                            re_or_im = 'i';
                        }
                        else if (re_or_im == 'i') {
                            tmp(i, j).imag(string_to_double(number));
                            number = "";
                            re_or_im = 'r';
                            j++;
                        }
                    }
                    prev = symbol;
                }
            }

            return tmp;
        }
    };
}
