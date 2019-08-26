#pragma once


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
Range<T_integer> range(T_integer aLast)
{
    return {aLast};
}


}} // namespace ad::math

