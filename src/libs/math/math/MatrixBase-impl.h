template<TMP>
template <class... T_element,
          std::enable_if_t<sizeof...(T_element) == N_rows*N_cols, int>>
MatrixBase<TMA>::MatrixBase(T_element... vaElements) :
        mStore{ {vaElements...} }
{}


template<TMP>
MatrixBase<TMA>::MatrixBase(UninitializedTag)
{}


template<TMP>
MatrixBase<TMA>::MatrixBase(detail::CastTag, store_type aData) :
    mStore(aData)
{}


template<TMP>
template <class T_otherDerived,
          class /* default template argument used to enable_if */>
MatrixBase<TMA>::operator T_otherDerived () const
{
    T_otherDerived result(detail::CastTag{}, mStore);
    return result;
}


template<TMP>
template <class T_otherDerived,
          class /* default template argument used to enable_if */>
MatrixBase<TMA>::MatrixBase(const T_otherDerived & aOther)
{
    std::copy(aOther.begin(), aOther.end(), mStore.begin());
}


template<TMP>
T_derived & MatrixBase<TMA>::setZero()
{
    mStore.fill(0);
    return *derivedThis();
}


template<TMP>
T_derived MatrixBase<TMA>::Zero()
{
    T_derived result(UninitializedTag{});
    return result.setZero();
}


template <TMP>
typename MatrixBase<TMA>::Row MatrixBase<TMA>::operator[](std::size_t aRow)
{
    return Row{&mStore[aRow*N_cols]};
}

template <TMP>
typename MatrixBase<TMA>::const_Row MatrixBase<TMA>::operator[](std::size_t aRow) const
{
    return const_Row{&mStore[aRow*N_cols]};
}


template <TMP>
typename MatrixBase<TMA>::const_iterator MatrixBase<TMA>::cbegin() const
{
    return mStore.cbegin();
}

template <TMP>
typename MatrixBase<TMA>::const_iterator MatrixBase<TMA>::cend() const
{
    return mStore.cend();
}

template <TMP>
typename MatrixBase<TMA>::const_iterator MatrixBase<TMA>::begin() const
{
    return cbegin();
}

template <TMP>
typename MatrixBase<TMA>::const_iterator MatrixBase<TMA>::end() const
{
    return cend();
}


template <TMP>
T_derived * MatrixBase<TMA>::derivedThis()
{
    return static_cast<T_derived*>(this);
}

template <TMP>
const T_derived * MatrixBase<TMA>::derivedThis() const
{
    return static_cast<const T_derived*>(this);
}


template <TMP>
T_number & MatrixBase<TMA>::at(std::size_t aIndex)
{
    return mStore[aIndex];
}


template <TMP>
T_number & MatrixBase<TMA>::at(std::size_t aRow, std::size_t aColumn)
{
    return mStore[aRow*N_cols + aColumn];
}


template <TMP>
T_number MatrixBase<TMA>::at(std::size_t aIndex) const
{
    return mStore[aIndex];
}


template <TMP>
T_number MatrixBase<TMA>::at(std::size_t aRow, std::size_t aColumn) const
{
    return mStore[aRow*N_cols + aColumn];
}


template <TMP>
const T_number * MatrixBase<TMA>::data() const
{
    return mStore.data();
}


template <TMP>
T_derived & MatrixBase<TMA>::operator+=(const MatrixBase &aRhs)
{
    for(std::size_t elementId = 0; elementId != N_rows*N_cols; ++elementId)
    {
        mStore[elementId] += aRhs.mStore[elementId];
    }

    return *derivedThis();
}


template <TMP>
T_derived operator+(T_derived aLhs, const MatrixBase<TMA> &aRhs)
{
    aLhs += aRhs;
    return aLhs;
}


template <TMP>
T_derived & MatrixBase<TMA>::operator-=(const MatrixBase &aRhs)
{
    for(std::size_t elementId = 0; elementId != N_rows*N_cols; ++elementId)
    {
        mStore[elementId] -= aRhs.mStore[elementId];
    }

    return *derivedThis();
}


template <TMP>
T_derived operator-(T_derived aLhs, const MatrixBase<TMA> &aRhs)
{
    aLhs -= aRhs;
    return aLhs;
}


template <TMP>
T_derived & MatrixBase<TMA>::operator *=(T_number aScalar)
{
    for(std::size_t elementId = 0; elementId != N_rows*N_cols; ++elementId)
    {
        mStore[elementId] *= aScalar;
    }
    return *derivedThis();
}


template <TMP>
T_derived operator*(T_number aScalar, const MatrixBase<TMA> &aRhs)
{
    T_derived copy(static_cast<const T_derived &>(aRhs));
    copy *= aScalar;
    return copy;
}


template <TMP>
T_derived operator*(const MatrixBase<TMA> &aLhs, T_number aScalar)
{
    return aScalar * aLhs;
}


template <TMP>
T_derived & MatrixBase<TMA>::operator /=(T_number aScalar)
{
    for(std::size_t elementId = 0; elementId != N_rows*N_cols; ++elementId)
    {
        mStore[elementId] /= aScalar;
    }
    return *derivedThis();
}


template <TMP>
T_derived operator/(const MatrixBase<TMA> &aLhs, T_number aScalar)
{
    T_derived copy(static_cast<const T_derived &>(aLhs));
    copy /= aScalar;
    return copy;
}


template <TMP>
T_derived MatrixBase<TMA>::operator-() const
{
    T_derived copy(static_cast<const T_derived &>(*this));
    copy *= -1;
    return copy;
}


template <TMP>
T_derived & MatrixBase<TMA>::hadamardAssign(const MatrixBase &aRhs)
{
    for(std::size_t elementId = 0; elementId != N_rows*N_cols; ++elementId)
    {
        mStore[elementId] *= aRhs.mStore[elementId];
    }
    return *this->derivedThis();
}


template <TMP>
T_derived MatrixBase<TMA>::hadamard(T_derived aRhs) const
{
    return aRhs.hadamardAssign(*this);
}


template <TMP>
bool MatrixBase<TMA>::operator==(const MatrixBase &aRhs) const
{
    return mStore == aRhs.mStore;
}

template<TMP>
bool MatrixBase<TMA>::operator!=(const MatrixBase &aRhs) const
{
    return !(*this == aRhs);
}


template<TMP>
std::ostream & operator<<(std::ostream & os, const MatrixBase<TMA> &aMatrix)
{
    auto printRow = [&](std::size_t row)
    {
        os << "| ";
        for(std::size_t col = 0; col != N_cols; ++col)
        {
            os << aMatrix[row][col] << ' ';
        }
        os << '|';
    };

    printRow(0);
    for(std::size_t row = 1; row != N_rows; ++row)
    {
        os << '\n';
        printRow(row);
    }

    return os;
}
