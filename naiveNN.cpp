#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <ctime>
#include "Matrix.h"
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

Matrix activation(Matrix W, Matrix b, Matrix x)
{
  Matrix Temp(W.Rows(), 1);

  Temp = -(W * x + b);

  for (int i = 0; i < Temp.Rows(); i++)
  {
    Temp(i, 0) = exp(Temp(i, 0));
    Temp(i, 0) = 1 / (1 + Temp(i, 0));
  }

  return Temp;
};



double Euclidean(Matrix vec)
{
  double norm{0};

  for (int i = 0; i < vec.Rows(); i++)
  {
    norm += vec(i, 0) * vec(i, 0);
  }

  return norm;
};

double Sum (Matrix vec)
{
  double sum{0};

  for (int i = 0; i < vec.Rows(); i++)
  {
    sum += vec(i, 0);
  }
  return sum;
}

Matrix prediction(Matrix W2, Matrix W3, Matrix W4, Matrix b2, Matrix b3, Matrix b4, Matrix XVec)
{
  Matrix A2 = activation(W2, b2, XVec);
  Matrix A3 = activation(W3, b3, A2);
  Matrix A4 = activation(W4, b4, A3);

  return A4;
};

double cost_function(Matrix W2, Matrix W3, Matrix W4, Matrix b2, Matrix b3, Matrix b4, Matrix x1, Matrix x2, Matrix y)
{
  Matrix cost(10, 1);
  Matrix x(2, 1);

  for (int i = 0; i < cost.Rows();i++)
  {
    x(0, 0)    = x1(i, 0);
    x(1, 0)    = x2(i, 0);

    Matrix A2  = activation(W2, b2, x);
    Matrix A3  = activation(W3, b3, A2);
    Matrix A4  = activation(W4, b4, A3);

    Matrix YData(y.Rows(), 1);
    YData(0, 0) = y(0, i);
    YData(1, 0) = y(1, i);

//    std::cout << "A4 dimensions : (" << A4.Rows() << "," << A4.Cols() << ")" << '\n';
//    std::cout << "Y  Data : ("       << YData.Rows() << "," << YData.Cols() << ")" << '\n';
    Matrix A = A4 - YData;

    cost(i, 0) = Euclidean(A4 - YData);
  //  std::cout << cost(i, 0) << '\n';

//    std::cout << cost(i, 0) << '\n';


  };

  return Sum(cost);

};
int main()
{
  clock_t time_req;
  time_req = clock();

  // Data
  Matrix D1(10, 1);

  D1(0,0) = 0.1;
  D1(1,0) = 0.3;
  D1(2,0) = 0.1;
  D1(3,0) = 0.6;
  D1(4,0) = 0.4;
  D1(5,0) = 0.6;
  D1(6,0) = 0.5;
  D1(7,0) = 0.9;
  D1(8,0) = 0.4;
  D1(9,0) = 0.7;

  Matrix D2(10, 1);

  D2(0,0) = 0.1;
  D2(1,0) = 0.4;
  D2(2,0) = 0.5;
  D2(3,0) = 0.9;
  D2(4,0) = 0.2;
  D2(5,0) = 0.3;
  D2(6,0) = 0.6;
  D2(7,0) = 0.2;
  D2(8,0) = 0.4;
  D2(9,0) = 0.6;

  // Classifiers

  Matrix Y(2, 10, 0);
  Y(0, 0) = 1;
  Y(0, 1) = 1;
  Y(0, 2) = 1;
  Y(0, 3) = 1;
  Y(0, 4) = 1;

  Y(1, 5) = 1;
  Y(1, 6) = 1;
  Y(1, 7) = 1;
  Y(1, 8) = 1;
  Y(1, 9) = 1;




  // Weight matrices
  Matrix W2(2, 2, 1);
  W2 = W2.setNormal(W2);
  Matrix W3(3, 2, 1);
  W3 = W3.setNormal(W3);
  Matrix W4(2, 3, 1);
  W4 = W4.setNormal(W4);



  // biases
  Matrix b2(2, 1, 1);
  b2 = b2.setNormal(b2);
  Matrix b3(3, 1, 1);
  b3 = b3.setNormal(b3);
  Matrix b4(2, 1, 1);
  b4 = b4.setNormal(b4);

  // learning rate
  double learningrate{0.75};

  // number of iterations to do gradient descent
  int training_steps{100000};

  Matrix XVec(2, 1, 0);
  Matrix YVec(2, 1, 0);

  Matrix Cost(training_steps, 1, 0);


  for (int i = 0; i < training_steps; i++)
  {
    int k = rand() % 10;

    XVec(0,0)  = D1(k, 0);
    XVec(1,0)  = D2(k, 0);

    YVec(0, 0) = Y(0, k);
    YVec(1, 0) = Y(1, k);

    // forward pass
    Matrix A2 = activation(W2, b2, XVec);
    Matrix A3 = activation(W3, b3, A2);
    Matrix A4 = activation(W4, b4, A3);
    Matrix Ones(A4.Rows(), A4.Cols(), 1);


    // backward pass
    Matrix delta4 = (A4 ^ (Ones - A4)) ^ (A4 - YVec);
    Matrix Ones1(A3.Rows(), A3.Cols(), 1);
    Matrix delta3 = (A3 ^ (Ones1 - A3)) ^ (!W4 * delta4);
    Matrix Ones2(A2.Rows(), A2.Cols(), 1);
    Matrix delta2 = (A2 ^ (Ones2 - A2)) ^ (!W3 * delta3);

    W2 = W2 - learningrate * delta2 * !XVec;
    W3 = W3 - learningrate * delta3 * !A2;
    W4 = W4 - learningrate * delta4 * !A3;

    b2 = b2 - learningrate * delta2;
    b3 = b3 - learningrate * delta3;
    b4 = b4 - learningrate * delta4;


    Cost(i, 0) = cost_function(W2, W3, W4, b2, b3, b4, D1, D2, Y);
//    std::cout << Cost(i, 0) << '\n';

  };
  time_req = clock() - time_req;

  std::cout << (float)time_req/CLOCKS_PER_SEC << '\n';
};
