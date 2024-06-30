/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imag;

public:
    // Constructor
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Getter for the real part
    double getReal() const {
        return real;
    }

    // Getter for the imaginary part
    double getImag() const {
        return imag;
    }

    // Addition operator
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Subtraction operator
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // Multiplication operator
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    // Division operator
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
                       (imag * other.real - real * other.imag) / denominator);
    }

    // Conjugate of the complex number
    Complex conjugate() const {
        return Complex(real, -imag);
    }

    // Absolute value (magnitude) of the complex number
    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

    // Output stream operator
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};
