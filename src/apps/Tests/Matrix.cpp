#include "catch.hpp"

#include <math/Matrix.h>
#include <math/Range.h>
#include <math/Vector.h>

#include <iostream>
#include <iomanip>


using namespace ad::math;


SCENARIO("Matrices have a different factories")
{
    WHEN("Using the Identity factory")
    {
        Matrix<4, 4> identity = Matrix<4, 4>::Identity();

        THEN("The Identity matrix diagonal elements are 1, others are 0")
        {
            bool isDiagonal = true;

            for(std::size_t row : range(identity.Rows))
            {
                for(std::size_t col : range(identity.Cols))
                {
                    if ( ((col==row) && (identity[row][col] != 1.))
                        || ((col!=row) && (identity[row][col] != 0.)) )
                    {
                        isDiagonal = false;
                    }
                }
            }

            REQUIRE(isDiagonal);
        }

        THEN("It can be zeroed")
        {
            identity.setZero();
            REQUIRE(std::all_of(identity.begin(), identity.end(), [](double aValue){ return aValue == 0; }));
        }
    }

    WHEN("Using the Zero factory")
    {
        auto zero = Matrix<3,5>::Zero();
        THEN("All elements are 0")
        {
            REQUIRE(std::all_of(zero.begin(), zero.end(), [](double aValue){ return aValue == 0; }));
        }
    }
}

SCENARIO("Basic operations are available on Matrix instances")
{
    THEN("A zero factory is available")
    {
        Vec3<> zero = Vec3<>::Zero();
        REQUIRE(zero.x() == 0.);
        REQUIRE(zero.y() == 0.);
        REQUIRE(zero.z() == 0.);
    }

    GIVEN("Two 3 elements vectors")
    {
        Vec3<> a = {3., 4., 5.};
        Vec3<> b = {10., 20., 30.};

        THEN("They can be added and substracted")
        {
            Vec3<> add = a+b;
            REQUIRE(add.x() == a.x() + b.x());
            REQUIRE(add.y() == a.y() + b.y());
            REQUIRE(add.z() == a.z() + b.z());

            Vec3<> sub = b-a;
            REQUIRE(sub.x() == b.x() - a.x());
            REQUIRE(sub.y() == b.y() - a.y());
            REQUIRE(sub.z() == b.z() - a.z());
        }
    } 

    GIVEN("A 3x3 Matrix")
    {
        Matrix<3, 3> matrix = {
            1., 2.,  3.,
            5., 55., 5.,
            0., 11., 1.15,
        };

        GIVEN("A scalar factor")
        {
            double factor = 2.67;

            THEN("The matrix can be multiplied by the factor")
            {
                Matrix<3, 3> scaled = matrix * factor;

                REQUIRE(std::equal(matrix.cbegin(), matrix.cend(), scaled.cbegin(),
                                   [factor](double base, double scaled){ return scaled == factor*base; })
                       );

                REQUIRE (matrix != scaled);
                Matrix<3, 3> matrixCopy(matrix);
                REQUIRE( (matrixCopy *= factor) == scaled );
            }

            THEN("The matrix can be divided by the factor")
            {
                Matrix<3, 3> divided = matrix / factor;

                REQUIRE(std::equal(matrix.cbegin(), matrix.cend(), divided.cbegin(),
                                   [factor](double base, double divided){ return divided == base/factor; })
                       );

                Matrix<3, 3> matrixCopy(matrix);
                REQUIRE( (matrixCopy /= factor) == divided);
            }
        }

        THEN("It can be negated with unary minus")
        {
            Matrix<3, 3> negation = -matrix;

            REQUIRE(std::equal(matrix.cbegin(), matrix.cend(), negation.cbegin(),
                               [](double base, double negated){ return negated == -base; })
                   );
        }

        GIVEN("A second 3x3 matrix")
        {
            Matrix<3, 3> second = {
                6., -11., 13.,
                4., -1.,  3.,
                3., 4.,   -2.,
            };

            THEN("They can be multiplied together.")
            {
                Matrix<3, 3> expectedResult = {
                    23.,   -1.,   13.,
                    265.,  -90.,  220.,
                    47.45, -6.4, 30.7,
                };

                REQUIRE((matrix * second) == expectedResult);
            }

            THEN("They can be componentwise multiplied together (Hadamard product).")
            {
                Matrix<3, 3> expectedResult = {
                    6., -22., 39.,
                    20., -55., 15.,
                    0., 44., -2.3,
                };

                REQUIRE((matrix.hadamard(second)) == expectedResult);

                second.hadamardAssign(matrix);
                REQUIRE(second == expectedResult);
            }
        }
    }
}

SCENARIO("Naive multiplication")
{
    GIVEN("A 2x2 Matrix")
    {
        Matrix<2, 2> left = {
            1., 2.,
            2., 1.
        };

        GIVEN("An 2x2 Identity matrix")
        {
            Matrix<2, 2> right = Matrix<2, 2>::Identity();

            THEN("Mutlipliying them results in the first matrix")
            {
                REQUIRE( (left*right) == left );
            }
        }
    }
}

SCENARIO("Vector multiplication")
{
    GIVEN("A vector 3")
    {
        Vec3<> vector{ 5., 6., 15.};

        GIVEN("A 3x3 matrix")
        {
            Matrix<3, 3> matrix {
                4., 12., 33.,
                1., 0.5, 1.,
                84., 0.5, 4.,
            };

            Vec3<> expected { 1286., 70.5, 231. };

            THEN("The vector can me multiplied by the matrix")
            {
                REQUIRE((vector*matrix) == expected);
            }

            THEN("The vector can me multiplied by the matrix")
            {
                vector *= matrix;
                REQUIRE(vector == expected);
            }
        }
    }
}


SCENARIO("Vector operations")
{
    GIVEN("Two vector of dimension 3")
    {
        Vec3<> a{ 3., 2., -4.};
        Vec3<> b{ 5., -1., 2.};

        THEN("dot product can be computed")
        {
            REQUIRE(a.dot(b) == 5);
            REQUIRE(a.dot(b) == b.dot(a));
        }

        THEN("Hadamard product can be computed")
        {
            Vec3<> expected{15., -2., -8.};
            REQUIRE(a.hadamard(b) == expected);

            b.hadamardAssign(a);
            REQUIRE(b == expected);
        }

        THEN("Cross product can be computed")
        {
            Vec3<> expected{0., -26., -13.};
            REQUIRE(a.cross(b) == expected);

            a.crossAssign(b);
            REQUIRE(a == expected);
        }
    }
}
