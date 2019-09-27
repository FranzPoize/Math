#pragma once

#include "Vector.h"

namespace ad {
namespace math {


template <class T_number>
struct Rectangle
{
    T_number x() const
    { return mPosition.x(); }
    T_number y() const
    { return mPosition.y(); }

    T_number width() const
    { return mDimension.width(); }
    T_number height() const
    { return mDimension.height(); }

    T_number area() const
    { return mDimension.area(); }

    Position<2, T_number> originCorner()
    { return mPosition; }

    Position<2, T_number> diagonalCorner()
    { return mPosition + static_cast<Vec<2, T_number>>(mDimension); }

    bool operator==(const Rectangle &aRhs) const
    { return mPosition == aRhs.mPosition && mDimension == aRhs.mDimension; }
    bool operator!=(const Rectangle &aRhs) const
    { return !(*this == aRhs); }

    Position<2, T_number>  mPosition;
    Size<2, T_number> mDimension;
};


}} // namespace ad::math
