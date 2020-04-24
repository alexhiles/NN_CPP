#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <ctime>
#include "Matrix.h"

class TrainingData
{
public:

    TrainingData() : higham{true}, X(10, 2, 0), Y(10, 2, 0) {}

    TrainingData(int datapoints) :

    X(datapoints,2, 0), Y(datapoints, 2, 0)

    {}

    Matrix genPoints()
    {
      if (higham)
      {
        X(0,0) = 0.1;
        X(1,0) = 0.3;
        X(2,0) = 0.1;
        X(3,0) = 0.6;
        X(4,0) = 0.4;
        X(5,0) = 0.6;
        X(6,0) = 0.5;
        X(7,0) = 0.9;
        X(8,0) = 0.4;
        X(9,0) = 0.7;

        X(0,1) = 0.1;
        X(1,1) = 0.4;
        X(2,1) = 0.5;
        X(3,1) = 0.9;
        X(4,1) = 0.2;
        X(5,1) = 0.3;
        X(6,1) = 0.6;
        X(7,1) = 0.2;
        X(8,1) = 0.4;
        X(9,1) = 0.6;
        return X;
      }

      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      std::default_random_engine generator (seed);

      for (int i = 0; i < X.Rows(); i++)
      {
        for (int j = 0; j < X.Cols(); j++)
        {
          std::uniform_real_distribution<double> distribution (0.0,1.0);
          X(i, j) = static_cast<double>(distribution(generator));
        };
      };

      return X;
    };

    Matrix getX(){return X;}

    Matrix getY(){return Y;}

    Matrix genClass()
    {
      for (int i = 0; i < Y.Rows() / 2; i++)
      {
        Y(i, 0) = 1;
        Y(i + Y.Rows() / 2, 1) = 1;
      };
      return Y;
    };

    Matrix GetX()
    {
      return X;
    };

    Matrix GetY()
    {
      return Y;
    }

    int GetN()
    {
      return N;
    }

private:

  int N;
  Matrix X;
  Matrix Y;
  bool higham{false};
};

class Layer
{
public:

    Layer() : W(0, 0), b(0, 0) {}
    Layer(int m, int n) : W(m, n), b(m, 1)  {}

    void setNormal()
    {
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      std::default_random_engine generator (seed);

      for (int i = 0; i < W.Rows(); i++)
      {
        std::normal_distribution<double> distribution (0.0, 1.0);
        for (int j = 0; j < W.Cols(); j++)
        {
          W(i, j) = static_cast<double>(distribution(generator));
        }
        b(i, 1) = static_cast<double>(distribution(generator));
      }
    };

    Matrix getW()
    {
      return W;
    }

    Matrix getb()
    {
      return b;
    }

    void setW(Matrix A)
    {
      W = A;
    }

    void setb(Matrix A)
    {
      b = A;
    }

private:
  Matrix W;
  Matrix b;
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

double cost_function(Matrix W2, Matrix W3, Matrix W4, Matrix b2, Matrix b3, Matrix b4, Matrix data, Matrix y)
{
  Matrix cost(10, 1);
  Matrix x(2, 1);

  for (int i = 0; i < cost.Rows();i++)
  {
    x(0, 0)    = data(i, 0);
    x(1, 0)    = data(i, 1);

    Matrix A2  = activation(W2, b2, x);
    Matrix A3  = activation(W3, b3, A2);
    Matrix A4  = activation(W4, b4, A3);

    Matrix YData(y.Cols(), 1);
    YData(0, 0) = y(i, 0);
    YData(1, 0) = y(i, 1);

    cost(i, 0) = Euclidean(A4 - YData);

  };

  return Sum(cost);

};
int main()
{
  clock_t time_req;
  time_req = clock();

  TrainingData DataPoints;
  TrainingData Class;

  Matrix X      = DataPoints.genPoints();
  Matrix Y      =      Class.genClass();

  // General network parameters

  int number_of_layers = 3;
  std::vector<int> neurons_per_layer = {2, 3, 2};

  // Classifiers
  std::vector<Layer>        Data(number_of_layers);
  std::vector<Matrix> Activation(number_of_layers);
  std::vector<Matrix>     Errors(number_of_layers);

  for (int i = 0; i < neurons_per_layer.size(); i++)
  {
    if (i == 0)
    {
      Data[i] = Layer(neurons_per_layer[i], neurons_per_layer[i]);
    }
    else
    {
    Data[i] = Layer(neurons_per_layer[i], neurons_per_layer[i - 1]);
    }
    Data[i].setNormal();
  };


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
  double learningrate{0.1};

  // number of iterations to do gradient descent
  int training_steps{100000};

  Matrix XVec(2, 1, 0);
  Matrix YVec(2, 1, 0);

  Matrix Cost(training_steps, 1, 0);


  for (int i = 0; i < training_steps; i++)
  {
    int k = rand() % 10;

    XVec(0,0)  = X(k, 0);
    XVec(1,0)  = X(k, 1);

    YVec(0, 0) = Y(k, 0);
    YVec(1, 0) = Y(k, 1);

    // forward pass

  //  for (int i = 0; i < number_of_layers; i++)
  //  {
  //    Matrix A = activation(Data[i].getW(), Data[i].getb(), XVec);
  //    break;
  //    XVec = A;
  //  };
    Activation[0] = activation(Data[0].getW(), Data[0].getb(), XVec);
    for (int i = 1; i < Activation.size(); i++)
    {
      Activation[i] = activation(Data[i].getW(), Data[i].getb(), Activation[i - 1]);
    }
    Matrix Ones(Activation[Activation.size() - 1].Rows(), Activation[Activation.size() - 1].Cols(), 1);

    Errors[0] = Activation[Activation.size() - 1] ^ (Ones - Activation[Activation.size() - 1] ) ^ (Activation[Activation.size() - 1] - YVec);

    // UP TO HERE ***ERRORS ARE HERE 
    for (int i = 1; i < Activation.size(); i++)
    {
      Matrix Ones(Activation[Activation.size() - 1 - i].Rows(), Activation[Activation.size() - 1 - i].Cols(), 1);

      Errors[i] = Activation[Activation.size() - 1 - i] ^ (Ones - Activation[Activation.size() - 1 - i]) ^ (!Data[Data.size() - 1].getW() * Errors[i-1]);
    }


    Matrix A2 = activation(Data[0].getW(), Data[0].getb(), XVec);

std::cout << "A3 W: " << Data[1].getW().Rows() << " " << Data[1].getW().Cols() << '\n';
std::cout << "A3 b: " << Data[1].getb().Rows() << " " << Data[1].getb().Cols() << '\n';
    Matrix A3 = activation(Data[1].getW(), Data[1].getb(), A2);

    std::cout << "A3 W: " << Data[1].getW().Rows() << " " << Data[1].getW().Cols() << '\n';
    std::cout << "A3 b: " << Data[1].getb().Rows() << " " << Data[1].getb().Cols() << '\n';
    Matrix A4 = activation(Data[2].getW(), Data[2].getb(), A3);
  //  std::cout << "A4 W: " << Data[2].getW().Rows() << " " << Data[2].getW().Cols() << '\n';
  //  std::cout << "A4 b: " << Data[2].getb().Rows() << " " << Data[2].getb().Cols() << '\n';




//    Matrix A2 = activation(W2, b2, XVec);
//    Matrix A3 = activation(W3, b3, A2);
//    Matrix A4 = activation(W4, b4, A3);
//    Matrix Ones(A4.Rows(), A4.Cols(), 1);


    // backward pass
    Matrix delta4 = (A4 ^ (Ones - A4)) ^ (A4 - YVec);
    Matrix Ones1(A3.Rows(), A3.Cols(), 1);
    Matrix delta3 = (A3 ^ (Ones1 - A3)) ^ (!W4 * delta4);
    Matrix Ones2(A2.Rows(), A2.Cols(), 1);
    Matrix delta2 = (A2 ^ (Ones2 - A2)) ^ (!W3 * delta3);

    // update
    Data[0].setW(Data[0].getW() - learningrate * delta2 * !XVec);
    Data[1].setW(Data[1].getW() - learningrate * delta3 * !A2);
    Data[2].setW(Data[2].getW() - learningrate * delta4 * !A3);

    Data[0].setb(Data[0].getb() - learningrate * delta2);
    Data[1].setb(Data[1].getb() - learningrate * delta3);
    Data[2].setb(Data[2].getb() - learningrate * delta4);

//    W2 = W2 - learningrate * delta2 * !XVec;
//    W3 = W3 - learningrate * delta3 * !A2;
//    W4 = W4 - learningrate * delta4 * !A3;

//    b2 = b2 - learningrate * delta2;
//    b3 = b3 - learningrate * delta3;
//    b4 = b4 - learningrate * delta4;


//    Cost(i, 0) = cost_function(Data, X, Y);

  };
  time_req = clock() - time_req;

  std::cout << (float)time_req/CLOCKS_PER_SEC << '\n';
};
