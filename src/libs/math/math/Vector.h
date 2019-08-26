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

    /// \brief Dot product
    T_number dot(const Vector &aRhs) const;
};

template <class T_derived, int N_dimension, class T_number>
T_derived operator*(const Vector<T_derived, N_dimension, T_number> aLhs,
                    const Matrix<N_dimension, N_dimension, T_number> &aRhs);


/***
 * Specializations
 ***/

#define BASE Vector<T_derived, 4, T_number>
template <class T_derived, class T_number>
class Vec4Base : public BASE
{
    typedef BASE base_type;
    using base_type::base_type;

public:
    T_derived & crossAssign(const Vec4Base &aRhs);
    T_derived cross(const Vec4Base &aRhs);

    T_number &x()
    { return this->at(0); }
    T_number &y()
    { return this->at(1); }
    T_number &z()
    { return this->at(2); }
    T_number &w()
    { return this->at(3); }

    T_number x() const
    { return this->at(0); }
    T_number y() const
    { return this->at(1); }
    T_number z() const
    { return this->at(2); }
    T_number w() const
    { return this->at(3); }
};
#undef BASE


#define BASE Vec4Base<Vec4<T_number>, T_number>
template <class T_number=real_number>
class Vec4 : public BASE
{
    typedef BASE base_type;
    using base_type::base_type;
};
#undef BASE

#define BASE Vector<T_derived, 3, T_number>
template <class T_derived, class T_number>
class Vec3Base : public BASE
{
    typedef BASE base_type;
    using base_type::base_type;

public:
    T_derived & crossAssign(const Vec3Base &aRhs);
    T_derived cross(const Vec3Base &aRhs);

    T_number &x()
    { return this->at(0); }
    T_number &y()
    { return this->at(1); }
    T_number &z()
    { return this->at(2); }

    T_number x() const
    { return this->at(0); }
    T_number y() const
    { return this->at(1); }
    T_number z() const
    { return this->at(2); }
};
#undef BASE


#define BASE Vec3Base<Vec3<T_number>, T_number>
template <class T_number=real_number>
class Vec3 : public BASE
{
    typedef BASE base_type;
    using base_type::base_type;
};
#undef BASE


#define BASE Vector<T_derived, 2, T_number>
template <class T_derived, class T_number>
class Vec2Base : public BASE
{
    typedef BASE base_type;
    using base_type::base_type;

public:
    T_number &x()
    { return this->at(0); }
    T_number &y()
    { return this->at(1); }

    T_number x() const
    { return this->at(0); }
    T_number y() const
    { return this->at(1); }
};
#undef BASE


#define BASE Vec2Base<Vec2<T_number>, T_number>
template <class T_number=real_number>
class Vec2 : public BASE
{
    typedef BASE base_type;
    using base_type::base_type;
};
#undef BASE


#define BASE Vector<Dimension2<T_number>, 2, T_number>
template <class T_number=real_number>
class Dimension2 : public BASE
{
    typedef BASE base_type;
    using base_type::base_type;

    /// \TODO disable most of the public functions

public:
    T_number &width()
    { return this->at(0); }
    T_number &height()
    { return this->at(1); }

    T_number width() const
    { return this->at(0); }
    T_number height() const
    { return this->at(1); }

    T_number area() const
    { return width()*height(); }
};
#undef BASE


#include "Vector-impl.h"


}} // namespace ad::math

