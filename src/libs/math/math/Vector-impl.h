#include <cmath>

namespace ad {
namespace math {

/*
 * Vector implementation
 */
template <class T_derived, int N_dimension, class T_number>
template <template <int, class> class TT_derivedVector, class T_targetNumber>
constexpr TT_derivedVector<N_dimension, T_targetNumber>
Vector<T_derived, N_dimension, T_number>::as() const
{
    return static_cast<TT_derivedVector<N_dimension, T_targetNumber>>(*this);
}

template <class T_derived, int N_dimension, class T_number>
constexpr T_number & Vector<T_derived, N_dimension, T_number>::operator[](std::size_t aColumn)
{
    return this->at(aColumn);
}


template <class T_derived, int N_dimension, class T_number>
constexpr T_number Vector<T_derived, N_dimension, T_number>::operator[](std::size_t aColumn) const
{
    return this->at(aColumn);
}


template <class T_derived, int N_dimension, class T_number>
constexpr T_derived & Vector<T_derived, N_dimension, T_number>::operator*=(
        const Matrix<N_dimension, N_dimension, T_number> &aRhs)
{
    (*this) = (*this) * aRhs;
    return *this->derivedThis();
}


template <class T_derived, int N_dimension, class T_number>
constexpr T_derived operator*(const Vector<T_derived, N_dimension, T_number> aLhs,
                    const Matrix<N_dimension, N_dimension, T_number> &aRhs)
{
    return multiplyBase<T_derived>(aLhs, aRhs);
}


template <class T_derived, int N_dimension, class T_number>
constexpr T_number Vector<T_derived, N_dimension, T_number>::dot(const Vector &aRhs) const
{
    T_number result = 0;
    for(std::size_t col = 0; col != N_dimension; ++col)
    {
        result += (*this)[col] * aRhs[col];
    }
    return result;
}

template <class T_derived, int N_dimension, class T_number>
constexpr T_number Vector<T_derived, N_dimension, T_number>::getNormSquared() const
{
    T_number accumulator = 0;
    for(std::size_t col = 0; col != N_dimension; ++col)
    {
        // std::pow is not constexpr
        //accumulator += std::pow((*this)[col], 2);
        accumulator += (*this)[col] * (*this)[col];
    }
    return accumulator;
}

template <class T_derived, int N_dimension, class T_number>
T_number Vector<T_derived, N_dimension, T_number>::getNorm() const
{
    return std::sqrt(getNormSquared());
}

template <class T_derived, int N_dimension, class T_number>
T_derived & Vector<T_derived, N_dimension, T_number>::normalize()
{
    return (*this /= getNorm());
}

/*
 * Cross product implementation
 */
template <int N_dimension, class T_number>
auto Vec<N_dimension, T_number>::crossAssign(const Vec & aRhs) -> Vec &
{
    static_assert(N_dimension==3, "Disabled when dimension != 3");
    *this = this->cross(aRhs);
    return *this->derivedThis();
}


template <int N_dimension, class T_number>
auto Vec<N_dimension, T_number>::cross(const Vec &aRhs) -> Vec
{
    static_assert(N_dimension==3, "Disabled when dimension != 3");
    return {
        y()*aRhs.z() - z()*aRhs.y(),
        z()*aRhs.x() - x()*aRhs.z(),
        x()*aRhs.y() - y()*aRhs.x(),
    };
}

}} // namespace ad::math
