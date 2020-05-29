namespace trans2d {

template <class T_number, class T_angleUnitTag>
Matrix<2, 2, T_number> rotate(const Angle<T_number, T_angleUnitTag> aAngle)
{
    return {
         cos(aAngle), sin(aAngle),
        -sin(aAngle), cos(aAngle),
    };
}

} // namespace trans2d

