#pragma once

#include <type_traits>

namespace ad {
namespace math {


template <class T_derivedLeft, class T_derivedRight, class T_enabler>
struct addition_trait : public std::false_type
{};

template <class T_derivedLeft, class T_derivedRight>
struct addition_trait<T_derivedLeft, T_derivedRight,
                      std::enable_if_t<std::is_same<T_derivedLeft, T_derivedRight>::value>> 
                     : public std::true_type
{
    // Implementer's note:
    //   The trait could also return the addition result type, allowing more flexibility
    //   Yet this leads to several potential complications:
    //   * operator+= is not available when the result type is not the left type
    //   * because of the above, the operator+(left, right) becomes more complicated to implement
    //     because we cannot compound assign the first argument taken by value (copy)
    //   * What if A+B -> C, yet C+B does not result in C?
    //   Because of those complications, and since we did not encounter a case where the result
    //   type is not the left type, we make it a hard rule to return the left type in additive_t.
    //
    // typedef T_derivedLeft result_type; // Would be default, if we specified a result_type
};

// Would be if we specified a result_type
//template <class T_derivedLeft, class T_derivedRight>
//using additive_t = typename addition_trait<T_derivedLeft, T_derivedRight, void>::result_type;

template <class T_derivedLeft, class T_derivedRight>
using additive_t = std::enable_if_t<addition_trait<T_derivedLeft, T_derivedRight, void>::value,
                                    T_derivedLeft>;

}} // namespace ad::math
