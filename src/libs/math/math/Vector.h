#pragma once

#include "MatrixBase.h"
#include "Matrix.h"

namespace ad {
namespace math {


/// \brief Base class for all vectors (i.e. matrices with exactly one row)
template <class T_derived, int N_dimension, class T_number>
class Vector : public MatrixBase<T_derived, 1, N_dimension, T_number>
{
    typedef MatrixBase<T_derived, 1, N_dimension, T_number> base_type;
    using base_type::base_type;

public:
    T_number &operator[](std::size_t aColumn);
    T_number operator[](std::size_t aColumn) const;

    T_derived & operator*=(const Matrix<N_dimension, N_dimension, T_number> &aRhs);
    using base_type::operator*=;

    /// \brief Dot product
    T_number dot(const Vector &aRhs) const;
};

template <class T_derived, int N_dimension, class T_number>
T_derived operator*(const Vector<T_derived, N_dimension, T_number> aLhs,
                    const Matrix<N_dimension, N_dimension, T_number> &aRhs);


/***
 * Specializations
 ***/
#define ENABLER(condition) \
    template <int N=N_dimension, class = std::enable_if_t<(N condition && N==N_dimension)>> 

#define ACCESSOR(symbol, dimension) \
    ENABLER(>= dimension)           \
    T_number & symbol()/* requires (N_dimension>=dimension)*/ \
    {static_assert(N_dimension>=dimension, "Disabled when dimensions < " #dimension); return this->at(dimension-1);} \
                                    \
    ENABLER(>= dimension)           \
    T_number symbol() const/* requires (N_dimension>=dimension)*/ \
    {static_assert(N_dimension>=dimension, "Disabled when dimensions <" #dimension); return this->at(dimension-1);}


#define BASE Vector<Vec<N_dimension, T_number>, N_dimension, T_number>
template <int N_dimension, class T_number=real_number>
class Vec : public BASE
{
    typedef BASE base_type;
    using base_type::base_type;

public:
    template<class T>
    using derived_type = Vec<N_dimension, T>;

    // This approach has drawbacks:
    // * The error can be hard to read, with many lines of template substition error
    // * It is not fool-proof, because client code can still give explicit value for function template arguments
    // A good solution seems to be `requires` keyword introduced in C++20,
    // but we do with a mix of enbable_if and static_assert for the moment.
    // see: https://stackoverflow.com/q/58068206/1027706
    //
    //template <int N=N_dimension, class = std::enable_if_t<(N>1 && N==N_dimension)>> T_number & y()
    //{return this->at(1);}

    ACCESSOR(x, 1)
    ACCESSOR(y, 2)
    ACCESSOR(z, 3)
    ACCESSOR(w, 4)

    /// \todo Could be extended to all dimensions >= 3?
    Vec & crossAssign(const Vec &aRhs) /*requires(N_dimension==3)*/;
    Vec cross(const Vec &aRhs) /*requires(N_dimension==3)*/;
};
#undef BASE


#define BASE Vector<Position<N_dimension, T_number>, N_dimension, T_number>
template <int N_dimension, class T_number=real_number>
class Position : public BASE
{
    typedef BASE base_type;
    using base_type::base_type;

public:
    template<class T>
    using derived_type = Position<N_dimension, T>;

    ACCESSOR(x, 1)
    ACCESSOR(y, 2)
    ACCESSOR(z, 3)
    ACCESSOR(w, 4)
};
#undef BASE

template <int N_dimension, class T_number>
struct addition_trait<Position<N_dimension, T_number>, Position<N_dimension, T_number>, void>
                     : public std::false_type
{};

template <int N_dimension, class T_number>
struct addition_trait<Position<N_dimension, T_number>, Vec<N_dimension, T_number>, void>
                     : public std::true_type
{};

#define BASE Vector<Size<N_dimension, T_number>, N_dimension, T_number>
template <int N_dimension, class T_number=real_number>
class Size : public BASE
{
    /// \todo Disable most of the available functions
    typedef BASE base_type;
    using base_type::base_type;

public:
    template<class T>
    using derived_type = Size<N_dimension, T>;

    ACCESSOR(width,  1)
    ACCESSOR(height, 2)
    ACCESSOR(depth,  3)

    template <int N=N_dimension, class = std::enable_if_t<(N==2 && N==N_dimension)>> 
    T_number area() const/* requires (N_dimension==2)*/
    {static_assert(N_dimension==2, "Disabled when dimension != 2"); return width()*height();}

    template <int N=N_dimension, class = std::enable_if_t<(N==3 && N==N_dimension)>> 
    T_number volume() const/* requires (N_dimension==3)*/
    {static_assert(N_dimension==3, "Disabled when dimension != 3"); return width()*height()*depth();}
};
#undef BASE

#undef ACCESSOR
#undef ENABLER

#include "Vector-impl.h"


}} // namespace ad::math

