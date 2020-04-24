#ifndef MATRIX_HEADER
#endif
#define MATRIX_HEADER

#include <iostream>
#include <random>
#include <vector>

class Matrix
//creates class Matrix
{ //opens class
public:
    //opens public section of class
    Matrix() : nRows(0), nCols(0) {}
    Matrix(int n,int m, double x = 0) : nRows(n), nCols(m), A(n * m, x)
    {}
    //defines Matrix
    Matrix &operator=(double x)
    {
        for (int i=0; i < (nRows * nCols); i++) A[i]=x;
        return *this;
    }
    double operator()(int i, int j) const
    {
        return A[j + i * nCols];
    }
    double &operator()(int i, int j)
    {
        return A[j + i * nCols];
    }

    Matrix setNormal(Matrix A)
    {
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      std::default_random_engine generator (seed);
      std::normal_distribution<double> distribution (0.0,1.0);

      for (int i = 0; i < A.Rows(); i++)
      {
        for (int j = 0; j < A.Cols(); j++)
        {
          A(i, j) = static_cast<double>(distribution(generator));
        }
      }
      return A;
    };

    int Rows() const { return nRows; }
    int Cols() const { return nCols; }
    void SetX(double x_) {x=x_;}
    double GetX ()
    //creates constructor
    {
        return x;
        //constructor that returns x
    }
private:
    //private part of class
    unsigned int nRows, nCols;
    //unsigned inters nRows & nCols
    std::vector <double> A;
    //private vector A
    double x;
    //private variable double x
}; //closes class

inline Matrix operator +(const Matrix &right, const Matrix &left);
//overloads + operator that adds Matrix with an Matrix
inline Matrix operator -(const Matrix &left, const Matrix &right);
//overloads operator - for Matrix subtract an Matrix
inline Matrix operator *(const Matrix &left, const double &right);
//overloads * operator for an Matrix on the left and a double
//variable on the right

inline Matrix operator -(Matrix left);

inline Matrix operator ^(const Matrix left, const Matrix right);

inline Matrix operator *(const double &left, const Matrix &right);
//overloads operator * where a double variable is on the left
//and a Matrix is on the right
inline Matrix operator /(const Matrix &left, const double &right);
//overloads / operator where a Matrix is on the left and a double
//variable is on the right
inline Matrix operator *(const Matrix &left, const Matrix &right);

inline Matrix operator -(double x, Matrix left);

inline Matrix operator!(Matrix A);


inline Matrix operator +(const Matrix &right, const Matrix &left)
{
    Matrix temp(left);
    if ( right.Rows() != left.Rows() || right.Cols() != left.Cols() )
    {
        std::cout << "Error while adding matrices, the two must have the same dimensions." << '\n';
    }
    else
    {
        for ( int r=0; r < temp.Rows(); r++ )
        {
            for ( int c=0; c < temp.Cols(); c++ )
            {
                temp(r,c) = left(r,c) + right(r,c);
            }
        }
    }
    return temp;
}
//overloads + operator that adds Matrix with an Matrix
inline Matrix operator -(const Matrix &left, const Matrix &right)
{
    Matrix temp(left);
    if ( right.Rows() != left.Rows() || right.Cols() != left.Cols() )
    {
        std::cout << "\nError while adding matrices, the two must have the same dimensions.\n";
    }
    else
    {
        for ( int r=0; r < temp.Rows(); r++ )
        {
            for ( int c=0; c < temp.Cols(); c++ )
            {
                temp(r,c) = left(r,c) - right(r,c);
            }
        }
    }
    return temp;
}
//overloads operator - for Matrix subtract an Matrix
inline Matrix operator *(const Matrix &left, const double &right)
{
    Matrix temp(left);
    {
        for ( int r=0; r < temp.Rows(); r++ )
        {
            for ( int c=0; c < temp.Cols(); c++ )
            {
                temp(r,c) = right*left(r,c);
            };
        };
    };
    return temp;
};
//overloads * operator for an Matrix on the left and a double
//variable on the right

inline Matrix operator -(Matrix left)
{
  for (int i = 0; i < left.Rows(); i++)
  {
    for (int j = 0; j < left.Cols(); j++)
    {
      left(i, j) = - left(i, j);
    };
  };
  return left;
};

inline Matrix operator ^(const Matrix left, const Matrix right)
{
  if (left.Rows() != right.Rows())
  {
    std::cout << "Dimensions must agree!" << '\n';
    exit(0);
  }

  Matrix temp(left.Rows(), left.Cols());

  for (int i = 0; i < left.Rows(); i++)
  {
    for (int j = 0; j < left.Cols(); j++)
    {
      temp(i, j) = left(i, j) * right(i, j);
    };
  };
  return temp;
};

inline Matrix operator *(const double &left, const Matrix &right)
{
    Matrix temp(right);
    {
        for ( int r=0; r < temp.Rows(); r++ )
        {
            for ( int c=0; c < temp.Cols(); c++ )
            {
                temp(r,c) = left*right(r,c);
            }
        }
    }
    return temp;
}
//overloads operator * where a double variable is on the left
//and a Matrix is on the right
inline Matrix operator /(const Matrix &left, const double &right)
{
    Matrix temp(left);
    {
        for ( int r=0; r < temp.Rows(); r++ )
        {
            for ( int c=0; c < temp.Cols(); c++ )
            {
                temp(r,c) = left(r,c)/right;
            }
        }
    }
    return temp;
}
//overloads / operator where a Matrix is on the left and a double
//variable is on the right
inline Matrix operator *(const Matrix &left, const Matrix &right)
{
    if (left.Cols()!=right.Rows())
    {
        std::cout << " MATRIX-MATRIX MULTIPLICATION ERROR: Inner dimensions must agree!" << '\n';
        abort();
    }
    Matrix X(left.Rows(),right.Cols(),0);
    for (int i=0; i < left.Rows();i++)
    {
    for (int j=0;j < right.Cols();j++)
     {
         for (int k=0; k < left.Cols();k++)
         {
         X(i,j)+=left(i,k)*right(k,j);
     }
}
}
return X;
}

inline Matrix operator -(double x, Matrix left)
{
  for (int i = 0; i < left.Rows(); i++)
  {
    for (int j = 0; j < left.Cols(); j++)
    {
      left(i, j) = x - left(i, j);
    };
  };
  return left;
};

inline Matrix operator!(Matrix A)
{
  Matrix B(A.Cols(), A.Rows());

  for (int i = 0; i < A.Cols();i++)
  {
    for (int j = 0; j < A.Rows();j++)
    {
      B(i, j) = A(j, i);
    }
  };
  return B;

};

