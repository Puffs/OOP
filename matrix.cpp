#include <iostream>
#include "matrix.h"

MatrixClass::MatrixClass() {};
MatrixClass::MatrixClass(int columnMatr, int rowsMatr) // Конструктор
{
    row = rowsMatr;
    column = columnMatr;

    matr = (double**) new double* [row]; //Создаем массив указателей (На одномерные массивы)

    
    for (int counter = 0; counter < row; counter++) // И выделяем память для каждого из них
        matr[counter] = (double*)new double[column];

  
    for (int counter = 0; counter < row; counter++)   // Заполним нашу матрицу незначащими нулями
        for (int secCounter = 0; secCounter < column; secCounter++)
            matr[counter][secCounter] = 0;
};


MatrixClass::~MatrixClass()  // Деструктор
{
    if (column > 0)
    {
        for (int counter = 0; counter < row; counter++)
            delete[] matr[counter];
    }
    if (row > 0)
        delete[] matr;
}
MatrixClass::MatrixClass(const MatrixClass& _matrix) // скопируем нашу матрицу 
{
    row = _matrix.row;
    column = _matrix.column;

    matr = (double**) new double* [row];

    for (int counter = 0; counter < row; counter++)
        matr[counter] = (double*)new double[column];

    for (int counter = 0; counter < row; counter++)
        for (int secCounter = 0; secCounter < column; secCounter++)
            matr[counter][secCounter] = _matrix.matr[counter][secCounter];
}
//Создадим геттеры и сеттеры для доступа к данным
double MatrixClass::Get(int i, int j)
{
    if ((row > 0) && (column > 0))
        return matr[i][j];
    else
        return 0;
}
void MatrixClass::Set(int _rows, int _cols, double value)
{
    if ((_rows < 0) || (_rows >= row))
        return;
    if ((_cols < 0) || (_cols >= column))
        return;
    matr[_rows][_cols] = value;
}

MatrixClass MatrixClass::operator=(const MatrixClass& _matrix)
{
    if (column > 0)
    {
        
        for (int counter = 0; counter < row; counter++) // освобождаем
            delete[] matr[counter];
    }

    if (row > 0)
    {
        delete[] matr;
    }

    row = _matrix.row;
    column = _matrix.column;

    matr = (double**) new double* [row]; // количество строк, количество указателей
    for (int counter = 0; counter < row; counter++)
        matr[counter] = (double*) new double[column];

   
    for (int counter = 0; counter < row; counter++)  // заполняем
        for (int secCounter = 0; secCounter < column; secCounter++)
            matr[counter][secCounter] = _matrix.matr[counter][secCounter];
    return *this;
}

// Операции над матрицами..........................

 //Инкременты

MatrixClass operator++(MatrixClass& M) // Инкремент префиксный
{
    for (int counter = 0; counter < M.row; counter++)
        for (int secCounter = 0; secCounter < M.column; secCounter++)
            M.matr[counter][secCounter] = M.matr[counter][secCounter] + 1;
    return M;
}

MatrixClass operator++(MatrixClass& M, int) // Инкремент постфиксный
{
    MatrixClass oldValue(M);
    for (int counter = 0; counter < M.row; counter++)
        for (int secCounter = 0; secCounter < M.column; secCounter++)
            M.matr[counter][secCounter] = M.matr[counter][secCounter] + 1;
    return oldValue;
}

MatrixClass operator--(MatrixClass& M) // Декремент префиксный
{
    for (int counter = 0; counter < M.row; counter++)
        for (int secCounter = 0; secCounter < M.column; secCounter++)
            M.matr[counter][secCounter] = M.matr[counter][secCounter] - 1;
    return M;
}

MatrixClass operator--(MatrixClass& M, int) // Декремент постфиксный 
{
    MatrixClass oldValue(M);
    for (int counter = 0; counter < M.row; counter++)
        for (int secCounter = 0; secCounter < M.column; secCounter++)
            M.matr[counter][secCounter] = M.matr[counter][secCounter] - 1;
    return oldValue;
}
MatrixClass operator-(double left, const MatrixClass& right)
{
    MatrixClass temp(right.column, right.row);
    for (int counter = 0; counter < right.row; counter++)
        for (int secCounter = 0; secCounter < right.column; secCounter++)
            temp.matr[counter][secCounter] = left - right.matr[counter][secCounter];
    return temp;
}
MatrixClass operator-(const MatrixClass& left, double right)
{
    MatrixClass temp(left.column, left.row);
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            temp.matr[counter][secCounter] = left.matr[counter][secCounter] - right;
    return temp;
}
MatrixClass operator-(const MatrixClass& left, const MatrixClass& right)
{
    MatrixClass temp(left.column, left.row);
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            temp.matr[counter][secCounter] = left.matr[counter][secCounter] - right.matr[counter][secCounter];
    return temp;
}
MatrixClass operator+(const MatrixClass& left, const MatrixClass& right)
{
    MatrixClass temp(left.column, left.row);
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            temp.matr[counter][secCounter] = left.matr[counter][secCounter] + right.matr[counter][secCounter];
    return temp;
}
MatrixClass operator+(const MatrixClass& left, double right)
{
    MatrixClass temp(left.column, left.row);
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            temp.matr[counter][secCounter] = left.matr[counter][secCounter] + right;
    return temp;
}
MatrixClass operator+(double left, const MatrixClass& right)
{
    MatrixClass temp(right.column, right.row);
    for (int counter = 0; counter < right.row; counter++)
        for (int secCounter = 0; secCounter < right.column; secCounter++)
            temp.matr[counter][secCounter] = left + right.matr[counter][secCounter];
    return temp;
}
MatrixClass operator*(const MatrixClass& left, const MatrixClass& right)
{
    MatrixClass temp(left.column, left.row);
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            temp.matr[counter][secCounter] = left.matr[counter][secCounter] * right.matr[counter][secCounter];
    return temp;
}
MatrixClass operator*(const MatrixClass& left, double right)
{
    MatrixClass temp(left.column, left.row);
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            temp.matr[counter][secCounter] = left.matr[counter][secCounter] * right;
    return temp;
}
MatrixClass operator*(double left, const MatrixClass& right)
{
    MatrixClass temp(right.column, right.row);
    for (int counter = 0; counter < right.row; counter++)
        for (int secCounter = 0; secCounter < right.column; secCounter++)
            temp.matr[counter][secCounter] = left * right.matr[counter][secCounter];
    return temp;
}
MatrixClass operator/(const MatrixClass& left, const MatrixClass& right)
{
    MatrixClass temp(right.column, right.row);
    for (int counter = 0; counter < right.row; counter++)
        for (int secCounter = 0; secCounter < right.column; secCounter++)
            temp.matr[counter][secCounter] = left.matr[counter][secCounter] / right.matr[counter][secCounter];
    return temp;
}
MatrixClass operator/(const MatrixClass& left, double right)
{
    MatrixClass temp(left.column, left.row);
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            temp.matr[counter][secCounter] = left.matr[counter][secCounter] / right;
    return temp;
}
MatrixClass operator/(double left, const MatrixClass& right)
{
    MatrixClass temp(right.column, right.row);
    for (int counter = 0; counter < right.row; counter++)
        for (int secCounter = 0; secCounter < right.column; secCounter++)
            temp.matr[counter][secCounter] = left / right.matr[counter][secCounter];
    return temp;
}
MatrixClass operator+=(MatrixClass& left, const MatrixClass& right)
{
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            left.matr[counter][secCounter] += right.matr[counter][secCounter];
    return left;
}
MatrixClass operator-=(MatrixClass& left, const MatrixClass& right)
{
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            left.matr[counter][secCounter] -= right.matr[counter][secCounter];
    return left;
}
MatrixClass operator*=(MatrixClass& left, const MatrixClass& right)
{
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            left.matr[counter][secCounter] *= right.matr[counter][secCounter];
    return left;
}
MatrixClass operator/=(MatrixClass& left, const MatrixClass& right)
{
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            left.matr[counter][secCounter] /= right.matr[counter][secCounter];
    return left;
}
MatrixClass operator+=(MatrixClass& left, const double right)
{
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            left.matr[counter][secCounter] += right;
    return left;
}
MatrixClass operator-=(MatrixClass& left, const double right)
{
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            left.matr[counter][secCounter] -= right;
    return left;
}
MatrixClass operator*=(MatrixClass& left, const double right)
{
    for (int counter = 0; counter < left.row; counter++)
        for (int secCOunter = 0; secCOunter < left.column; secCOunter++)
            left.matr[counter][secCOunter] *= right;
    return left;
}
MatrixClass operator/=(MatrixClass& left, const double right)
{
    for (int counter = 0; counter < left.row; counter++)
        for (int secCounter = 0; secCounter < left.column; secCounter++)
            left.matr[counter][secCounter] /= right;
    return left;
}

 

std::ostream& operator<< (std::ostream& out, const MatrixClass& M)
{
    for (int counter = 0; counter < M.row; counter++)
    {
        for (int secCounter = 0; secCounter < M.column; secCounter++)
            out << M.matr[counter][secCounter] << "\t";
        out << std::endl;
    }
    out << std::endl << std::endl;
    return out;
}