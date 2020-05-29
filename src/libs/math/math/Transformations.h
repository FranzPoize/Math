#pragma once

#include "commons.h"

#include "Angle.h"
#include "Matrix.h"


namespace ad {
namespace math {


// Note: C++ identifier cannot start with a number
namespace trans2d {

    template <class T_number, class T_angleUnitTag=void>
    Matrix<2, 2, T_number> rotate(const Angle<T_number, T_angleUnitTag> aAngle);

} // namespace trans2d


#include "Transformations-impl.h"


} // namespace math
} // namespace ad
