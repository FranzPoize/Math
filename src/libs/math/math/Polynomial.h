#pragma once


#include "Utilities.h"

#include <array>

#include <cmath>


namespace ad {
namespace math {


template <int N_degree, class T_number=double>
class Polynomial
{
    /// \brief The number of element in the mCoefficients array, thus including the constant.
    constexpr static int coefficient_count = N_degree+1;

public:
    /// \parameter aCoefficients the constant and polynomials coefficients. Given in increasing degree.
    template <class... VT_coefficients>
    Polynomial(VT_coefficients... aCoefficients);

    T_number evaluate(T_number aVariableValue);

    T_number coefficient(std::size_t aIndex) const;

private:
    std::array<T_number, coefficient_count> mCoefficients;
};


template <int N_degree, class T_number>
template <class... VT_coefficients>
Polynomial<N_degree, T_number>::Polynomial(VT_coefficients... aCoefficients) :
        mCoefficients{{aCoefficients...}}
{}


template <int N_degree, class T_number>
T_number Polynomial<N_degree, T_number>::evaluate(T_number aVariableValue)
{
    T_number accumulator = mCoefficients.front();
    for(std::size_t degree = 1; degree != coefficient_count; ++degree)
    {
        accumulator += std::pow(aVariableValue, degree)*coefficient(degree);
    }
    return accumulator;
}


template <int N_degree, class T_number>
T_number Polynomial<N_degree, T_number>::coefficient(std::size_t aIndex) const
{
    return mCoefficients.at(aIndex);
}


/***
 * Solvers
 ***/

/// \return A vector containing the roots, in ascending order.
template <class T_number>
std::vector<T_number> solve(const Polynomial<2, T_number> &aPolynomial)
{
    const T_number A = aPolynomial.coefficient(2);
    const T_number B = aPolynomial.coefficient(1);
    const T_number C = aPolynomial.coefficient(0);

    T_number delta = std::pow(B, 2) - 4*A*C;

    if (delta > 0)
    {
        T_number signedRoot = (B >= 0) ? -std::sqrt(delta) : std::sqrt(delta);
        T_number aRoot = (-B + signedRoot) / (2*A);
        T_number bRoot = (2*C) / (-B + signedRoot);
        // By exhaustively writing all cases, we realize that when sign(A)==sign(B),
        // aRoot is always the smallest, bRoot otherwise
        return sameSign(A, B) ? std::vector<T_number>{aRoot, bRoot}
                              : std::vector<T_number>{bRoot, aRoot};
    } 
    else if (delta == 0)
    {
        return { {-B / (2*A)} };
    }
    else
    {
        return {};
    }
}


}} // namspace ad::math
