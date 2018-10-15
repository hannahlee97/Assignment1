
/*
 *  C++ Assignment01 Matrix.hpp
 */

#pragma once

#include <iostream>

class Matrix
{
    int range;
    double * numbers;

public:
    Matrix();
    Matrix(int);
    Matrix(double[], double);
    Matrix(const Matrix&);
    ~Matrix();
    inline void set_value(int, int, double);
    double get_value(int);
    inline double get_value(int, int) const;
    void clear();
    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);
    friend bool operator==(const Matrix& lhs, const Matrix& rhs);
    friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
    Matrix& operator++();
    Matrix operator++(int);
    Matrix& operator--();
    Matrix operator--(int);
    Matrix& operator=(Matrix rhs);
    friend void swap(Matrix& lhs, Matrix& rhs);
    Matrix& operator+=(const Matrix& rhs);
    friend Matrix operator+(Matrix lhs, const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    friend Matrix operator-(Matrix lhs, const Matrix& rhs);
    void everyOne();
    void randomWalk(double);
    Matrix multiplication(Matrix& rhs);
    void fillOne();
    void print();
    int get_dimension();
    Matrix outDegree();
    void scaleRank();
};