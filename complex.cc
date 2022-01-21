#include "complex.h"


//overload << to print complex number 
std::ostream& operator<<(std::ostream& os, const Complex& number)
{
  if(number.getNaN())
  {
    os << "NaN";
  }
  else
  {
    os << std::setprecision(6);

    int realInt = std::to_string((int)number.getReal()).length() + 7;
    int imagInt = std::to_string((int)number.getImag()).length() + 7;

    if(number.getReal() != 0.0 && number.getImag() != 0.0)
    {
      
      os << std::setw(realInt) << number.getReal();
      os << " + ";
      os << std::setw(imagInt) << number.getImag() << "j";
      os << std::setw(26 - realInt - imagInt) << "";
    }
    else if(number.getImag() != 0.0)
    {
      os << std::setw(imagInt) << number.getImag() << "j";
      os << std::setw(29 - imagInt) << "";
    }
    else
    {
      os << std::setw(30) << number.getReal();
    }
  }
  return os;
}

//constructors
Complex::Complex(): real(0.0), imag(0.0), NaN(false)
{ }

Complex::Complex(double newReal, double newImag): real(newReal), imag(newImag), NaN(false)
{ }

Complex::Complex(double newReal): real(newReal), imag(0.0), NaN(false)
{ }

Complex::Complex(const Complex& rhs): real(rhs.getReal()), imag(rhs.getImag()), NaN(rhs.getNaN())
{ }

//addition 
Complex Complex::operator+(Complex rhs)
{
  double newReal = getReal() + rhs.getReal();
  double newImag = getImag() + rhs.getImag();
  return Complex(newReal, newImag);
}

//subtraction 
Complex Complex::operator-(Complex rhs)
{
  double newReal = getReal() - rhs.getReal();
  double newImag = getImag() - rhs.getImag();
  return Complex(newReal, newImag);
}

//multiplication 
Complex Complex::operator*(Complex rhs)
{
  double mag = getMagnitude() * rhs.getMagnitude();
  double ang = getAngle() + rhs.getAngle();
  return Complex(mag * cos(ang), mag * sin(ang));
}

//division 
Complex Complex::operator/(Complex rhs)
{
  Complex quotient = Complex();
  if(rhs.getReal() == 0)
  {
    quotient.setNaN(true);
    return quotient;
  }
  double mag = getMagnitude() / rhs.getMagnitude();
  double ang = getAngle() - rhs.getAngle();
  quotient.setReal(mag * cos(ang));
  quotient.setImag(mag * sin(ang));
  return quotient;
}

//scale up
Complex Complex::operator*(double scale)
{
  return Complex(scale * getReal(), scale * getImag());
}

//scale down
Complex Complex::operator/(double scale)
{
  if(scale == 0.0)
  {
    Complex err = Complex();
    err.setNaN(true);
    return err;
  }
  return Complex(getReal() / scale, getImag() / scale);
}

//assignment
Complex& Complex::operator=(const Complex& rhs)
{
  setComplex(rhs.getReal(), rhs.getImag());
  setNaN(rhs.getNaN());
  return *this;
}


double Complex::getReal() const
{
  return real;
}

double Complex::getImag() const
{
  return imag;
}

bool Complex::getNaN() const
{
  return NaN;
}

//calculate magnitude 
double Complex::getMagnitude() const
{
  return( sqrt(getReal() * getReal() + getImag() * getImag()) );
}

//calculate angle 
double Complex::getAngle() const
{
  double angle;
  if (getReal() != 0)
  {
    angle = atan(getImag() / getReal());
    if(getReal() < 0) angle = (getImag() > 0) ? (asin(1) * 2) + angle : (asin(-1) * 2) + angle;
  }
  else if(getImag() != 0)
    angle = (getImag() > 0) ? asin(1) : asin(-1);
  else
    angle = 0;
  return angle;
}

void Complex::setReal(double newReal)
{
  real = newReal;
}

void Complex::setImag(double newImag)
{
  imag = newImag;
}

void Complex::setNaN(bool newNan)
{
  NaN = newNan;
}

void Complex::setComplex(double newReal, double newImag)
{
  real = newReal;
  imag = newImag;
  NaN = false;		
}

void Complex::displayRect() const
{
  coutRect();
  std::cout << std::endl;
}

void Complex::coutRect() const
{
  if(NaN)
  {
    std::cout << "NaN";
    return;
  }

  std::cout << std::setprecision(6);

  int realInt = std::to_string((int)getReal()).length() + 7;
  int imagInt = std::to_string((int)getImag()).length() + 7;

  if(getReal() != 0.0 && getImag() != 0.0)
  {
    std::cout << std::setw(realInt) << getReal();
    std::cout << " + ";
    std::cout << std::setw(imagInt) << getImag() << "j";
    std::cout << std::setw(26 - realInt - imagInt) << "";
  }
  else if(getImag() != 0.0)
  {
    std::cout << std::setw(imagInt) << getImag() << "j";
    std::cout << std::setw(29 - imagInt) << "";
  }
  else
  {
    std::cout << std::setw(30) << getReal();
  }
}

void Complex::displayPolar() const
{
  if(NaN)
  {
    std::cout << "NaN" << std::endl;
    return;
  }

  std::cout << std::fixed << std::setprecision(6) << getMagnitude() << " < " << getAngle() << std::endl;
}
