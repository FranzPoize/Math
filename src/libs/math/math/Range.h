#pragma once

#include "Vector.h"

#include <array>
#include <iostream>
#include <numeric>


namespace ad {
namespace math {


template<class T_integer>
class Range
{
public:
    Range(T_integer aLast):
        mCurrent(0),
        mLast(aLast)
    {}


    // Iterable functions
    const Range & begin() const
    { return *this; }

    const Range & end() const
    { return *this; }


    // Iterator functions
    bool operator!=(const Range &) const
    { return mCurrent != mLast; }

    void operator++()
    { ++mCurrent; }

    T_integer operator*() const
    { return mCurrent; }

private:
    T_integer mCurrent;
    T_integer mLast;
};


template <class T_integer>
std::enable_if_t<std::is_integral<T_integer>::value, Range<T_integer>> range(T_integer aLast)
{
    return {aLast};
}


template<class T_integer, std::size_t N_dimension>
class MultiRange
{
public:
    template <class... T_element>
    MultiRange(T_element &&... vaElements):
        mCurrent(0),
        mLimits(std::forward<T_element>(vaElements)...),
        mLast(accumulate(mLimits.begin(), mLimits.end(), 1, std::multiplies<T_integer>()))
    {}

    // Iterable functions
    const MultiRange & begin() const
    { return *this; }

    const MultiRange & end() const
    { return *this; }


    // Iterator functions
    bool operator!=(const MultiRange &) const
    { return mCurrent != mLast; }

    void operator++()
    { ++mCurrent; }

    std::array<T_integer, N_dimension> operator*() const
    {
        std::array<T_integer, N_dimension> result;
        T_integer forward = mCurrent;
        for (std::size_t index = 0; index != N_dimension; ++index)
        {
            result[index] = forward % mLimits[index];
            forward /= mLimits[index];
        }
        return result;
    }

private:
    T_integer mCurrent;
    const Size<N_dimension, T_integer> mLimits;
    const T_integer mLast;
};


/// \TODO test on c++14 compliant compiler
//template <class T_integer, std::size_t N_dimension>
//auto multirange(const std::initializer_list<T_integer> aLimits) -> MultiRange<T_integer, aLimits.size()>
//{
//    return {aLimits};
//}

template <class... T_integral>
MultiRange<std::common_type_t<T_integral...>, sizeof...(T_integral)> make_multirange(T_integral &&... vaLimits)
{
    return {std::forward<T_integral>(vaLimits)...};
}

template <class T_integer, std::size_t N_dimension>
std::ostream & operator<<(std::ostream & aOs, const MultiRange<T_integer, N_dimension> & aRange)
{
    auto indices = *aRange;
    for (std::size_t index = 0; index != N_dimension; ++index)
    {
        aOs << '[' << indices[index] << ']';
    }
    return aOs;
}


}} // namespace ad::math

