#ifndef Matrix_p
#define Matrix_p

#include "Matrix.h"
#include <cassert>

template <class T>
Matrix<T>::Matrix(int sizeX, int sizeY, T initValue)
{
    assert(sizeX > 0 && sizeY > 0);

    dx = sizeX;
    dy = sizeY;
    
    for (int i = 0; i < dx; i++)
    {
        vector<T> temp;
        for (int j = 0; j < dy; j++)
        {
            temp.push_back(initValue);
        }
        data.push_back(temp);
    }
}

template <typename T>
T &Matrix<T>::operator()(int x, int y)
{
    assert(x >= 0 && x < dx && y >=0 && y < dy);
    return data[x][y];
}

template <typename T>
ostream& operator<<(ostream &out, const Matrix<T> &m)
{
    out << endl;
    for (int x =0; x < m.dx; x++)
    {
        for (int y = 0; y < m.dy; y++)
            out << m.data[x][y] << "\t";
        
        out << "\n";

    }
    return out;
}

template <typename T>
Matrix<T> operator+(const Matrix<T>& m1, const Matrix<T>& m2)
{
    assert(m1.dx == m2.dx && m1.dy == m2.dy);
    Matrix<T> result = m1;
    for (int i = 0; i < m1.dx; i++)
    {
        for(int j = 0; j < m1.dy; j++)
            result.data[i][j] = m1.data[i][j] + m2.data[i][j];
    }

    return result;
}

#endif










