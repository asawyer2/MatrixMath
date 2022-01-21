#ifndef MATRIX_H 
#define MATRIX_H
#include <iostream> 
#include "complex.h" 
#include <string>
#define MATRIX_FIELD 30

class Matrix;
std::ostream & operator<< (std::ostream &, const Matrix &);
Matrix operator* (Complex, Matrix &);

class Matrix
{
  public:
    friend std::ostream & operator<< (std::ostream &, const Matrix &);
    friend Matrix operator* (Complex, Matrix &);

    //you put stuff in here!

    //constructors 
    Matrix();
    Matrix(int);
    Matrix(int, int);
    Matrix(const Matrix&);	
    //destructor 
    ~Matrix();

    int getRow() const;
    int getCol() const;

    //overloaded (r,c) 
    Complex& operator()(int, int) const;

    //overloaded operators 
    Matrix operator+(Matrix);
    Matrix operator-(Matrix);
    Matrix operator*(Matrix);
    Matrix operator*(Complex);
    Matrix operator~();			
    Matrix operator!();			
    Matrix& operator=(const Matrix&);	

    void transpose();
    void printMatrix();

  private:
    Complex* complexPtr;
    int rows;
    int cols;
    
};

#endif
