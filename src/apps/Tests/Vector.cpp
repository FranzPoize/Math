#include "catch.hpp"
#include "detection.h"

#include <math/Vector.h>


using namespace ad::math;


SCENARIO("Vectors can be constructed and manipulated")
{
    WHEN("Using the Zero factory")
    {
        Vec<2> vec2 = Vec<2>::Zero();

        THEN("All elements are 0")
        {
            REQUIRE(std::all_of(vec2.begin(), vec2.end(), [](double aValue){ return aValue == 0; }));
        }

        THEN("Elements are assignable via accessors")
        {
            vec2.x() = 1;
            vec2.y() = 2;
            REQUIRE(vec2[0] == 1);
            REQUIRE(vec2[1] == 2);
        }

    }

    WHEN("Using explicit constructor")
    {
        Vec<3> vec3{1.0, 2.0, 3.0};

        THEN("Stored values can be accessed as a pointer to contiguous data")
        {
            const double * data = vec3.data();
            REQUIRE(data[0] == 1.0);
            REQUIRE(data[1] == 2.0);
            REQUIRE(data[2] == 3.0);
        }

        THEN("Vector can be reset to zero")
        {
            vec3.setZero();
            REQUIRE(std::all_of(vec3.begin(), vec3.end(), [](double aValue){ return aValue == 0; }));
        }
    }
}


SCENARIO("There are separate vector template classes")
{
    WHEN("Using different vector types of matching dimension")
    {
        THEN("They are not implicitly convertible")
        {
            REQUIRE_FALSE(std::is_convertible<Size<2>, Vec<2>>::value);
        }

        THEN("They can be explicitly converted")
        {
            Size<2> size{5., 10.};
            Vec<2> vec = static_cast<Vec<2>>(size);
            REQUIRE(vec.at(1) == 10.);
        }
    }
}

#define HAS(mem_fun) template <class T> using has_##mem_fun##_t = decltype(std::declval<T&>().mem_fun());

HAS(x)
HAS(y)
HAS(z)
HAS(w)

SCENARIO("Vec class operations")
{
    GIVEN("Two vector of dimension 3")
    {
        Vec<3> a{ 3., 2., -4.};
        Vec<3> b{ 5., -1., 2.};

        THEN("dot product can be computed")
        {
            REQUIRE(a.dot(b) == 5);
            REQUIRE(a.dot(b) == b.dot(a));
        }

        THEN("Hadamard product can be computed")
        {
            Vec<3> expected{15., -2., -8.};
            REQUIRE(a.hadamard(b) == expected);

            b.hadamardAssign(a);
            REQUIRE(b == expected);
        }

        THEN("Cross product can be computed")
        {
            Vec<3> expected{0., -26., -13.};
            REQUIRE(a.cross(b) == expected);

            a.crossAssign(b);
            REQUIRE(a == expected);
        }
    }

    THEN("Accessors are available depending on dimension")
    {
        REQUIRE(ad::is_detected_v<has_x_t, Vec<2>>);
        REQUIRE(ad::is_detected_v<has_y_t, Vec<2>>);
        REQUIRE_FALSE(ad::is_detected_v<has_z_t, Vec<2>>);
        REQUIRE_FALSE(ad::is_detected_v<has_w_t, Vec<2>>);

        REQUIRE(ad::is_detected_v<has_x_t, Vec<3>>);
        REQUIRE(ad::is_detected_v<has_y_t, Vec<3>>);
        REQUIRE(ad::is_detected_v<has_z_t, Vec<3>>);
        REQUIRE_FALSE(ad::is_detected_v<has_w_t, Vec<3>>);

        REQUIRE(ad::is_detected_v<has_x_t, Vec<4>>);
        REQUIRE(ad::is_detected_v<has_y_t, Vec<4>>);
        REQUIRE(ad::is_detected_v<has_z_t, Vec<4>>);
        REQUIRE(ad::is_detected_v<has_w_t, Vec<4>>);
    }
}


template<class T>
class has_area
{
    template <size_t> struct exists;

    template <class C> static std::true_type  test(exists<sizeof(decltype(std::declval<C>().area()))>*);
    template <class C> static std::false_type test(...);

public:
    //static bool const value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
    static bool const value = decltype(test<T>(nullptr))::value;
};

HAS(area)
HAS(volume)

SCENARIO("Size class operations")
{
    GIVEN("A size instance of dimension 2")
    {
        Size<2> size2{2., 5.};

        THEN("Values are accessible via subscript operator")
        {
            REQUIRE(size2[0]  == 2.);
            REQUIRE(size2[1]  == 5.);
        }

        THEN("Values are accessible via accessors")
        {
            REQUIRE(size2.width()  == 2.);
            REQUIRE(size2.height() == 5.);
        }

        THEN("Its area can be computed")
        {
            REQUIRE(size2.area() == 2.*5.);
        }

        THEN("Volume member function is disabled")
        {
            REQUIRE_FALSE(ad::is_detected_v<has_volume_t, Size<2>>);
        }
    }

    GIVEN("A size instance of dimension 3")
    {
        Size<3> box{2., 4., 3.};

        THEN("Elements are accessible via accessors")
        {
            REQUIRE(box.width()  == 2.);
            REQUIRE(box.height() == 4.);
            REQUIRE(box.depth()  == 3.);
        }

        THEN("Its volume can be computed")
        {
            REQUIRE(box.volume() == 2.*4.*3.);
        }

        THEN("Area member function is disabled")
        {
            // Custom check
            REQUIRE_FALSE(has_area<Size<3>>::value);

            // Equivalent, but using detection experimental feature
            REQUIRE_FALSE(ad::is_detected<has_area_t, Size<3>>::value);
        }
    }
}
