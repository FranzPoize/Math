#include "catch.hpp"

#include <math/Rectangle.h>

using namespace ad::math;


SCENARIO("Rectangle usage")
{
    GIVEN("A rectangle instance")
    {
        Rectangle<double> rect{ {0., 5.}, {20., 30.} };

        THEN("Its position and dimensions are readable")
        {
            REQUIRE(rect.x() == 0.);
            REQUIRE(rect.y() == 5.);

            REQUIRE(rect.width() == 20.);
            REQUIRE(rect.height() == 30.);
        }
    }
}

