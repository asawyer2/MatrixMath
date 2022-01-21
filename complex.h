#ifndef COMPLEX_H
#define COMPLEX_H
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>

class Complex;
std::ostream& operator<<(std::ostream&, const Complex&);

class Complex
{

public:
  friend std::ostream& operator<<(std::ostream&, const Complex&);

  //constructors
  Complex();
  Complex(double, double);
  Complex(double);
  Complex(const Complex&);		

  Complex operator+(Complex);
  Complex operator-(Complex);
  Complex operator*(Complex);
  Complex operator/(Complex);

  Complex operator*(double);
  Complex operator/(double);
  Complex& operator=(const Complex&);

  double getReal() const;
  double getImag() const;
  bool getNaN() const;
  double getMagnitude() const;
  double getAngle() const;

  void setReal(double);
  void setImag(double);
  void setNaN(bool);
  void setComplex(double, double);		

  void displayRect() const;
  void coutRect() const;
  void displayPolar() const;

private:
  double real;
  double imag;
  bool NaN;

};

#endif
