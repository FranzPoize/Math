#pragma once


#include <cmath>


namespace ad {
namespace math {


template <class T_number>
bool sameSign(T_number aLeft, T_number aRight)
{
    // see: https://stackoverflow.com/a/3038621/1027706
    return std::signbit(aLeft) == std::signbit(aRight);
}


}} // namespace ad::math
