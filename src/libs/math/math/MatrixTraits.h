#pragma once

#include <type_traits>

namespace ad {
namespace math {


template <class T_derivedLeft, class T_derivedRight>
struct addition_trait : public std::false_type
{};

// This would be ambiguous with the "per derived-type" partial specialization in Vector.h
// see: https://stackoverflow.com/q/58960177/1027706
//template <class T_derivedLeft, class T_derivedRight>
//struct addition_trait<T_derivedLeft, T_derivedRight,
//                      std::enable_if_t<std::is_same<T_derivedLeft, T_derivedRight>::value>>

template <class T_derived>
struct addition_trait<T_derived, T_derived> : public std::true_type
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
using additive_t = std::enable_if_t<addition_trait<T_derivedLeft, T_derivedRight>::value,
                                    T_derivedLeft>;


//
// Types segmentation (detecting if a type derives from MatrixBase, etc.)
//

/// \brief Defines a static constexpr boolean `value`, true if T is considered a matrix type
/// false otherwise
///
/// \note Implemented in MatrixBase.h
template <class T>
class from_matrix;

template <class T>
inline constexpr bool from_matrix_v = from_matrix<T>::value;

template<class T>
inline constexpr bool is_arithmetic_v = std::is_arithmetic<T>::value;




}} // namespace ad::math
