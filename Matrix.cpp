
/*
 *  C++ Assignment01 Matrix.cpp
 */


#include "Matrix.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

// Matrix stores doubles
Matrix::Matrix() : range{ 1 }
{
    numbers = new double[1];
    clear();
}

// Default constructor initializing square 1 x 1 matrix that contains 0.0
Matrix::Matrix(int range) : range{ range }
{
    numbers = new double[range * range];
    clear();

}

// Constructor that accepts array of double
Matrix::Matrix(double first_array[], double size)
{
    range = (double)sqrt(size);
    if (range * range != size) {
        cout << "Invalid." << endl;
    }
    numbers = new double[size];
    for (int i = 0; i < size; ++i) {
        numbers[i] = first_array[i];
    }
}

Matrix::Matrix(const Matrix & more) : range{ more.range }
{
    numbers = new double[range * range];
    for (int i = 0; i < range * range; ++i) {
        numbers[i] = more.numbers[i];
    }
}

// mutator that accepts two integers representing row and column
// and double representing new value for the specified location
 void Matrix::set_value(int row, int column, double value)
{
    int index = row * range + column;
    numbers[index] = value;
}


double Matrix::get_value(int x)
{
    return numbers[x];
}

// mutator that accepts two integers representing row and column
// returns value in the matrix from the specified location
inline double Matrix::get_value(int row, int column) const
{
    return numbers[row * range + column];
}

// Function clear setting all values in the matrix to 0.0
void Matrix::clear()
{
    for (int i = 0; i < range * range; ++i) {
        numbers[i] = 0;
    }
}

Matrix & Matrix::operator++()
{
    for (int i = 0; i < range; ++i) {
        for (int j = 0; j < range; ++j) {
            numbers[i * range + j] =
                    1 + numbers[i * range + j];
        }
    }
    return *this;
}

Matrix Matrix::operator++(int)
{
    Matrix temp(*this);
    operator++();
    return temp;
}

Matrix & Matrix::operator--()
{
    for (int i = 0; i < range; ++i) {
        for (int j = 0; j < range; ++j) {
            numbers[i * range + j] =
                    numbers[i * range + j] - 1;
        }
    }
    return *this;
}

Matrix Matrix::operator--(int)
{
    Matrix temp(*this);
    operator--();
    return temp;
}

Matrix & Matrix::operator=(Matrix right)
{
    swap(*this, right);
    return *this;
}

// Overload operator +=
Matrix & Matrix::operator+=(const Matrix & right)
{
    for (int i = 0; i < range; ++i) {
        for (int j = 0; j < range; ++j) {
            numbers[i * range + j] +=
                    right.numbers[i * range + j];
        }
    }
    return *this;
}

// Overload operator -=
Matrix & Matrix::operator-=(const Matrix & right)
{
    for (int i = 0; i < range; ++i) {
        for (int j = 0; j < range; ++j) {
            numbers[i * range + j] -=
                    right.numbers[i * range + j];
        }
    }
    return *this;
}

// destructor
Matrix::~Matrix()
{
    delete[] numbers;

}

// Overloaded insertion operator so we can print matrix to std::cout or other streams
std::ostream & operator<<(std::ostream & out, const Matrix & matrix)
{
    for (int i = 0; i < matrix.range; ++i) {
        for (int j = 0; j < matrix.range; ++j) {
            out << setw(5) << matrix.numbers[i * matrix.range + j];
        }
        out << "\n";
    }
    return out;
}

bool operator==(const Matrix& left, const Matrix& right) {
    if (left.range != right.range) {
        return false;
    }
    for (int i = 0; i < left.range; i++) {
        for (int j = 0; j < left.range; j++) {
            if (left.get_value(i, j) != right.get_value(i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& left, const Matrix& right)
{
    return !operator==(left, right);
}

// Implementing assignment operator using copy-and-swap algorithm
void swap(Matrix & left, Matrix & right)
{
    using std::swap;
    swap(left.range, right.range);
    swap(left.numbers, right.numbers);
}

// Overload operator+
Matrix operator+(Matrix left, const Matrix & right)
{
    left += right;
    return left;
}

// Overload operator-
Matrix operator-(Matrix left, const Matrix & right)
{
    left -= right;
    return left;
}

// Random Walking
void Matrix::randomWalk(double probability)
{
    for(int i = 0; i < range * range; ++i) {
        numbers[i] *= probability;
    }
}

// Function to get the sum of column and divide each numbers of that column to
// the sum column value
Matrix Matrix::outDegree()
{
    Matrix m(range);
    m.numbers = numbers;

    for (int i = 0; i < range; ++i) {
        double sumColumn = 0;
        for (int j = 0; j < range; ++j) {
            sumColumn += m.numbers[(j * range) + i];
        }
        if (sumColumn > 0) {
            for (int j = 0; j < range; ++j) {
                double rowReplace = m.numbers[(j * range) + i];
                rowReplace = rowReplace / sumColumn;
                m.numbers[(j * range) + i] = rowReplace;
            }
        }
        else if (0 == sumColumn) {
            double rowReplace = (1 / (double)range);
            for (int j = 0; j < range; ++j) {
                m.numbers[(j * range) + i] = rowReplace;
            }
        }
    }
    return m;
}


void Matrix::everyOne()
{
    double temp = 1 / (double)range;
    for(int i = 0; i < range; ++i) {
        for(int j = 0; j < range; ++j) {
            numbers[i * range + j] = temp;
        }
    }
}

Matrix Matrix::multiplication(Matrix& right)
{
    Matrix temp(range);

    for(int i = 0; i < range * range; ++i) {
        double sum = 0;
        for(int j = 0; j < right.range; ++j) {
            double valueM = numbers[j];
            double rightValue = right.numbers[i * right.range + j];
            double valueTemp = valueM * rightValue;
            sum += valueTemp;
        }
        temp.numbers[i] = sum;
    }
    return temp;
}


void Matrix::fillOne()
{
    for (int i = 0; i < range*range; ++i) {
        numbers[i] = 1;
    }
}

// Printing the matrix
void Matrix::print()
{
    for (int i = 0; i < range * range; ++i) {
        cout << numbers[i] << endl;
    }
    cout << endl;
}

// Getting the dimension of the matrix
int Matrix::get_dimension()
{
    return range;
}

// Last step scaling the rank so its elements sum to 1
void Matrix::scaleRank()
{
    double sum = 0;
    for (int i = 0; i < range * range; ++i) {
        sum += numbers[i];
    }
    for (int i = 0; i < range * range; ++i) {
        numbers[i] /= sum;
    }
}


