///////////////////////////////////////////////////////////////////////////////
// Class: Vec                                                                //
// Mathematical Vectors with standard arithmetic operations                  //
//                                                                           //
// Example:                                                                  //
//      Vec<3, int> a = {1, 2, 3};                                           //
//      Vec<3, int> b = {2, 4, 6};                                           //
//      std::cout << a + b << std::endl;                                     //
// Output:                                                                   //
//      <3, 6, 9>                                                            //
///////////////////////////////////////////////////////////////////////////////

#ifndef VEC_HPP
#define VEC_HPP

#include <iostream>
#include <sstream>
#include <cstdint>
#include <cmath>
#include <algorithm>

template <typename T, uint8_t dim>
class Vec {
    public:
        Vec();
        Vec(const std::initializer_list<T> &);
        ~Vec();

        T & operator[](uint8_t index);
        const T & operator[](uint8_t index) const;

        T * begin();
        const T * begin() const;
        T * end();
        const T * end() const;

        double magnitude() const;
        Vec<T, dim> unit_vector() const;
        double dist_to(const Vec &other) const;
        double angle_between(const Vec &other) const;
        
        void operator=(const Vec &rhs);
        void operator+=(const Vec &rhs);
    private:
        T *m_data;
};

template <typename T, uint8_t dim>
Vec<T, dim>::Vec() {
    m_data = new T[dim]();
}

template <typename T, uint8_t dim>
Vec<T, dim>::Vec(const std::initializer_list<T> &c) {
    m_data = new T[dim];
    std::copy(c.begin(), c.end(), m_data);
}

template <typename T, uint8_t dim>
Vec<T, dim>::~Vec() {
    delete[] m_data;
}

template <typename T, uint8_t dim>
T & Vec<T, dim>::operator[](uint8_t index) {
    return m_data[index];
}

template <typename T, uint8_t dim>
const T & Vec<T, dim>::operator[](uint8_t index) const {
    return m_data[index];
}

template <typename T, uint8_t dim>
T * Vec<T, dim>::begin() {
    return m_data;
}

template <typename T, uint8_t dim>
const T * Vec<T, dim>::begin() const {
    return m_data;
}

template <typename T, uint8_t dim>
T * Vec<T, dim>::end() {
    return m_data + dim;
}

template <typename T, uint8_t dim>
const T * Vec<T, dim>::end() const {
    return m_data + dim;
}

///////////////////////////////////////////////////////////////////////////////
// Arithmetic Operators                                                      //
///////////////////////////////////////////////////////////////////////////////
// Vector addition
template <typename T, uint8_t dim>
Vec<T, dim> operator+(const Vec<T, dim> &lhs, const Vec<T, dim> &rhs) {
    Vec<T, dim> result;
    for (uint8_t i = 0; i < dim; ++i)
        result[i] = lhs[i] + rhs[i];
    
    return result;
}

template <typename T, uint8_t dim>
Vec<T, dim> operator-(const Vec<T, dim> &lhs, const Vec<T, dim> &rhs) {
    Vec<T, dim> result;
    for (uint8_t i = 0; i < dim; ++i)
        result[i] = lhs[i] - rhs[i];
    
    return result;
}

// Scalar multiplication (scalar * Vec)
template <typename TVec, typename Tscalar, uint8_t dim>
Vec<TVec, dim> operator*(const Tscalar &lhs, const Vec<TVec, dim> &rhs) {
    Vec<TVec, dim> result;
    for (uint8_t i = 0; i < dim; ++i)
        result[i] = static_cast<TVec>(lhs) * rhs[i];
    
    return result;
}

// Scalar multiplication (Vec * scalar)
template <typename TVec, typename Tscalar, uint8_t dim>
Vec<TVec, dim> operator*(const Vec<TVec, dim> &lhs, const Tscalar &rhs) {
    Vec<TVec, dim> result;
    for (uint8_t i = 0; i < dim; ++i)
        result[i] = lhs[i] * static_cast<TVec>(rhs);
    
    return result;
}

// Dot product
template <typename T, uint8_t dim>
T operator*(const Vec<T, dim> &lhs, const Vec<T, dim> &rhs) {
    T result = T();
    for (uint8_t i = 0; i < dim; ++i)
        result += lhs[i] * rhs[i];
    
    return result;
}

// Cross Product
template <typename T>
Vec<T, 3> operator^(const Vec<T, 3> &lhs, const Vec<T, 3> &rhs) {
    return Vec<T, 3> {
        lhs[1] * rhs[2] - lhs[2] * rhs[1],
        lhs[2] * rhs[0] - lhs[0] * rhs[2],
        lhs[0] * rhs[1] - lhs[1] * rhs[0]
    };
}

///////////////////////////////////////////////////////////////////////////////
// Special Formulae                                                          //
///////////////////////////////////////////////////////////////////////////////
template <typename T, uint8_t dim>
double Vec<T, dim>::magnitude() const {
    double result = 0;
    for (uint8_t i = 0; i < dim; ++i)
        result += std::pow(static_cast<double>(m_data[i]), 2.0);
    
    return std::sqrt(result);
}

template <typename T, uint8_t dim>
Vec<T,dim> Vec<T, dim>::unit_vector() const {
    T magnitude = this->magnitude();

    return Vec<T, 3> {
        this->m_data[0] / magnitude,
        this->m_data[1] / magnitude,
        this->m_data[2] / magnitude
    };
}

template <typename T, uint8_t dim>
double Vec<T, dim>::dist_to(const Vec<T, dim> &other) const {
    return (*this - other).magnitude();
}

template <typename T, uint8_t dim>
double Vec<T, dim>::angle_between(const Vec<T, dim> &other) const {
    return std::acos( (*this * other) / (this->magnitude() * other.magnitude()) );
}

///////////////////////////////////////////////////////////////////////////////
// Assignment Operators                                                      //
///////////////////////////////////////////////////////////////////////////////
template <typename T, uint8_t dim>
void Vec<T, dim>::operator=(const Vec<T, dim> &rhs) {
    std::copy(rhs.begin(), rhs.end(), this->m_data);
}

template <typename T, uint8_t dim>
void Vec<T, dim>::operator+=(const Vec<T, dim> &rhs) {
    for (uint8_t i = 0; i < dim; ++i)
        this->m_data[i] += rhs[i];
}

///////////////////////////////////////////////////////////////////////////////
// Comparison Operators                                                      //
///////////////////////////////////////////////////////////////////////////////
template <typename T, uint8_t dim>
bool operator==(const Vec<T, dim> &lhs, const Vec<T, dim> &rhs) {
    for (uint8_t i = 0; i < dim; ++i)
        if (lhs[i] != rhs[i])
            return false;
    
    return true;
}

template <typename T, uint8_t dim>
bool operator!=(const Vec<T, dim> &lhs, const Vec<T, dim> &rhs) {
    for (uint8_t i = 0; i < dim; ++i)
        if (lhs[i] != rhs[i])
            return true;
    
    return false;
}

// std::ostream compatability
template <typename T, uint8_t dim>
std::ostream &operator<<(std::ostream &out, const Vec<T, dim> &Vec) {
    std::ostringstream result;
    result << "<";
    for (uint8_t i = 0; i < dim; ++i) {
        result << Vec[i];

        if (i != dim - 1)
            result << ", ";
    }

    result << ">";  
    out << result.str(); 

    return out;
}

#endif