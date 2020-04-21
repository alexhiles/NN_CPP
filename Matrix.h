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
