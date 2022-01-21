#include "matrix.h"


//print
std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
  if(matrix.getRow() == 0 && matrix.getCol() == 0)
  {
    os << "This matrix has zero elements" << std::endl;
    return os;
  }
  for(int r = 1; r <= matrix.getRow(); r++)
  {
    for(int c = 1; c <= matrix.getCol(); c++)
    {
      Complex number = matrix(r,c);
      os << std::left << number;
    }
    os << std::endl;
  }
  return os;
}

//scaling
Matrix operator*(Complex scalarFactor, Matrix& matrixFactor)
{ 
  Matrix mult(matrixFactor.getRow(), matrixFactor.getCol());

  // multiply each matrix element by tne scale factor
  for(int r = 1; r <= mult.getRow(); r++)
  {
    for(int c = 1; c <= mult.getCol(); c++)
    {
      mult(r,c) = scalarFactor * matrixFactor(r,c);
    }
  }

  return mult;
}

//constructors
Matrix::Matrix()
{
  cols = 0;
  rows = 0;
  complexPtr = NULL;
}

Matrix::Matrix(int squareRows): rows(squareRows), cols(squareRows)
{
  complexPtr = new Complex[rows * cols];
  for(int i = 0; i < (rows * cols); i++)
  {
    complexPtr[i] = Complex();
  }
}

Matrix::Matrix(int inRows, int inCols): rows(inRows), cols(inCols)
{
  complexPtr = new Complex[rows * cols];

  for(int i = 0; i < (rows * cols); i++)
  {
    complexPtr[i] = Complex();
  }
}

Matrix::Matrix(const Matrix& rhs)
{
  rows = rhs.getRow();
  cols = rhs.getCol();

  complexPtr = new Complex[getRow() *getCol()];
  for(int i = 0; i < (getRow() * getCol()); i++)
    complexPtr[i] = rhs.complexPtr[i];
}

//destructor 
Matrix::~Matrix()
{
  delete[] complexPtr;
}

//overload () 
Complex& Matrix::operator()(int row, int col) const
{
  int index = (row - 1) * cols + (col - 1);
  return complexPtr[index];
}

//transpose 
void Matrix::transpose()
{
  
  for(int currR = 0; currR < getRow(); currR++)
  {
    for(int currC = 0; currC < currR; currC++)
    {
      int i = currR * getRow() + currC;
      int newIndex = currC * getCol() + currR;
      Complex tempVal = complexPtr[newIndex];
      complexPtr[newIndex] = complexPtr[i];
      complexPtr[i] = tempVal;
    }
  }

  int tempRows = getRow();
  rows = getCol();
  cols = tempRows;
}

//print 
void Matrix::printMatrix()
{
  if(getRow() == 0 || getCol() == 0)
  {
    std::cout << "This matrix has zero elements" << std::endl;
    return;
  }

  for(int r = 1; r <= getRow(); r++)
  {
    for(int c = 1; c <= getCol(); c++)
    {
      std::cout << std::left << std::setw(30);
      (*this)(r,c).coutRect();
    }
    std::cout << std::endl;
  }
}

//addition 
Matrix Matrix::operator+(Matrix rhs)
{
  if(getRow() != rhs.getRow() || getCol() != rhs.getCol())
  {
    std::cout << "Matrix Mismatch Error!" << std::endl;
    return Matrix();
  }

  Matrix sum(getRow(), getCol());
  for(int r = 1; r <= getRow(); r++)
  {
    for(int c = 1; c <= getCol(); c++)
    {
      sum(r,c) = (*this)(r,c) + rhs(r,c);
    }
  }

  return sum;
}

//subtraction 
Matrix Matrix::operator-(Matrix rhs)
{
  if(getRow() != rhs.getRow() || getCol() != rhs.getCol())
  {
    std::cout << "Matrix Mismatch Error!" << std::endl;
    return Matrix();
  }

  Matrix difference(getRow(), getCol());
  for(int r = 1; r <= getRow(); r++)
  {
    for(int c = 1; c <= getCol(); c++)
    {
      difference(r,c) = (*this)(r,c) - rhs(r,c);
    }
  }

  return difference;
}

//multiplication 
Matrix Matrix::operator*(Matrix rhs)
{
  if(getCol() != rhs.getRow()) {
    std::cout << "Matrix Mismatch Error!" << std::endl;
    return Matrix();
  }

  Matrix product(getRow(), rhs.getCol());
  for(int r = 1; r <= product.getRow(); r++)
  {
    for(int c = 1; c <= product.getCol(); c++)
    {
      Complex dotProduct = Complex(0,0);
      for(int i = 1; i <= getCol(); i++)
      {
        dotProduct = dotProduct + (*this)(r,i) * rhs(i,c);
      }
      product(r,c) = dotProduct;
    }
  }

  return product;
}

//scale 
Matrix Matrix::operator*(Complex number)
{
  Matrix mult(getRow(), getCol());

  for(int r = 1; r <= getRow(); r++)
  {
    for(int c = 1; c <= getCol(); c++)
    {
      mult(r,c) = (*this)(r,c) * number;
    }
  }

  return mult;
}

//transpose 
Matrix Matrix::operator~()
{
  
  Matrix transpose(getCol(), getRow());
  for(int r = 1; r <= getRow(); r++)
  {
    for(int c = 1; c <= getCol(); c++)
    {
      transpose(c,r) = (*this)(r,c);
    }
  }
  return transpose;
}

//complex conjugate transpose 
Matrix Matrix::operator!()
{
  Matrix conj(getRow(), getCol());
  for(int r = 1; r <= getRow(); r++)
  {
    for(int c = 1; c <= getCol(); c++)
    {
      Complex temp = (*this)(r,c);
      temp.setImag(temp.getImag() * -1);
      conj(r,c) = temp;
    }
  }
  conj.transpose();
  return conj;
}

//assignment
Matrix& Matrix::operator=(const Matrix& rhs)
{
  if(&rhs == this) return *this;

  if(getRow() != rhs.rows || getCol() != rhs.cols)
  {
    delete[] complexPtr;
    rows = rhs.rows;
    cols = rhs.cols;
    complexPtr = new Complex[getRow() * getCol()];
  }

  for(int i = 0; i < (rows * cols); i++)
    complexPtr[i] = rhs.complexPtr[i];

  return *this;
}

int Matrix::getRow() const
{
  return rows;
}

int Matrix::getCol() const
{
  return cols;
}
