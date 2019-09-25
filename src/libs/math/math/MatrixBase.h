#pragma once

#include <array>
#include <iostream>

namespace ad {
namespace math {

#define TMP class T_derived, int N_rows, int N_cols, class T_number
#define TMA T_derived, N_rows, N_cols, T_number


namespace detail {

class CastTag
{
    template <TMP>
    friend class MatrixBase;
};

} // namespace detail


template <TMP>
class MatrixBase
{
    typedef std::array<T_number, N_rows*N_cols> store_type;

public:
    typedef typename store_type::const_iterator const_iterator;

    static constexpr std::size_t Rows{N_rows};
    static constexpr std::size_t Cols{N_cols};

private:
    class Row
    {
        friend class MatrixBase;

        Row(T_number *aRow) :
                mRow(aRow)
        {}

        Row(const Row&) = default;

    public:
        T_number &operator[](std::size_t aColumn)
        { return mRow[aColumn]; }

    private:
        T_number *mRow;
    };
    
    class const_Row
    {
        friend class MatrixBase;

        const_Row(const T_number *aRow) :
                mRow(aRow)
        {}

        const_Row(const const_Row&) = default;

    public:
        T_number operator[](std::size_t aColumn)
        { return mRow[aColumn]; }

    private:
        const T_number *mRow;
    };

public:
    /// \note: std::array does not have a std::initializer_list constructor, but aggregate initialization.
    /// \note: enable_if to only allow this ctor when the right number of arguments is provided
    ///        (notably prevents this constructor from being selected as the default ctor)
    template <class... T_element,
              std::enable_if_t<sizeof...(T_element) == N_rows*N_cols, int> = 0>
    MatrixBase(T_element... vaElements);
    
    /// \brief Explicit cast to another derived type of same dimensions and scalar type
    template <class T_otherDerived,
              class = std::enable_if_t<std::is_base_of<MatrixBase<T_otherDerived,
                                                                  N_rows,
                                                                  N_cols,
                                                                  T_number>,
                                                       T_otherDerived>::value,
                                       T_otherDerived>>
    explicit operator T_otherDerived () const;

    /// \brief Sets all elements to zero
    T_derived & setZero();

    /// \brief Returns a Matrix with all elements set to 0.
    static T_derived Zero();


    Row operator[](std::size_t aRow);
    const_Row operator[](std::size_t aRow) const;

    // Iterate one line at a time, going through each column in the line before descending to the next line
    const_iterator cbegin() const;
    const_iterator cend() const;
    // Also implemented to enable range for loop
    const_iterator begin() const;
    const_iterator end() const;

    T_number & at(std::size_t aIndex);
    T_number & at(std::size_t aRow, std::size_t aColumn);
    T_number at(std::size_t aIndex) const;
    T_number at(std::size_t aRow, std::size_t aColumn) const;

    const T_number * data() const;


    T_derived & operator+=(const MatrixBase &aRhs);
    T_derived & operator-=(const MatrixBase &aRhs);

    T_derived & operator*=(T_number aScalar);
    T_derived & operator/=(T_number aScalar);

    T_derived operator-() const;

    /// \brief The compound componentwise multiplication
    T_derived & hadamardAssign(const MatrixBase &aRhs);
    /// \brief The componentwise multiplication
    /// \note Made a member function to have the syntax with the 'operator name' in between operands
    T_derived hadamard(T_derived aRhs) const;

    
    bool operator==(const MatrixBase &aRhs) const;
    bool operator!=(const MatrixBase &aRhs) const;

protected:
    T_derived * derivedThis();
    const T_derived * derivedThis() const;
    
protected:
    /// \note The default default-ctor would return unitialized memory.
    /// This is usefull in implementation details, but we make it more explicit with a ctor taking a tag
    MatrixBase() = delete;

    struct UninitializedTag{};

    MatrixBase(const MatrixBase &aRhs) = default;
    MatrixBase & operator=(const MatrixBase &aRhs) = default;

public:
    /// \brief Like a default constructor, but inaccessible to the client code thanks to the protected tag.
    MatrixBase(UninitializedTag);

    MatrixBase(detail::CastTag, store_type aData);

private:
    store_type mStore;
};

/*
 * Free function arithmetic operators
 */
template <TMP>
T_derived operator+(T_derived aLhs, const MatrixBase<TMA> &aRhs);

template <TMP>
T_derived operator-(T_derived aLhs, const MatrixBase<TMA> &aRhs);

template <TMP>
T_derived operator*(T_number aScalar, const MatrixBase<TMA> &aRhs);

template <TMP>
T_derived operator*(const MatrixBase<TMA> &aLhs, T_number aScalar);

template <TMP>
T_derived operator/(const MatrixBase<TMA> &aLhs, T_number aScalar);


/*
 * Output operator
 */
template<TMP>
std::ostream & operator<<(std::ostream & os, const MatrixBase<TMA> &aMatrix);


#include "MatrixBase-impl.h"


#undef TMA
#undef TMP


}} // namespace ad::math
