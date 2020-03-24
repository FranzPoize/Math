#include <math/Vector.h>

int main()
{
    using namespace ad::math;
    Vec<2, int> a{1, 2};
    a + Vec<2, int>{3, 4};
}
