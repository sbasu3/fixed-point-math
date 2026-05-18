#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>

#include "fp_generic_util.hxx"

namespace
{
    constexpr bool near(double a, double b, double tol)
    {
        return std::fabs(a - b) <= tol;
    }
}

int main()
{
    using q = FixedPoint<1, 15, std::int32_t>;

    const q zero = q::from_int(0);
    const q one = q::from_int(1);
    const q quarter = q::from_double(0.25);
    const q neg_one = q::from_int(-1);
    const q twenty_five = q::from_int(125);

    const q r0 = fp_sqrt(zero);
    assert(!r0.is_nan());
    assert(r0.raw() == 0);

    const q r1 = fp_sqrt(one);
    assert(!r1.is_nan());
    assert(near(r1.to_double(), 1.0, 0.001));

    const q r2 = fp_sqrt(quarter);
    assert(!r2.is_nan());
    assert(near(r2.to_double(), 0.5, 0.001));

    const q r3 = fp_sqrt(neg_one);
    assert(r3.is_nan());

    const q r4 = fp_sqrt(q::nan());
    assert(r4.is_nan());

    assert(fp_leading_one_power(one) == 0);
    assert(fp_leading_one_power(quarter) == -2);
    assert(fp_leading_one_power(q::from_double(0.75)) == -1);
    assert(fp_leading_one_power(q::from_double(1.5)) == 0);
    assert(fp_leading_one_power(zero) == std::numeric_limits<int>::min());
    assert(fp_leading_one_power(q::nan()) == std::numeric_limits<int>::min());

    if (!std::isgreater(q::integer_bits, 6))
    {
        std::cout << "Skipping large sqrt test due to potential overflow in intermediate steps" << std::endl;
    }
    else
    {
        const q r5 = fp_sqrt(twenty_five);
        assert(!r5.is_nan());
        assert(near(r5.to_double(), 11.1803, 0.001));
        r5.print();
    }
    std::cout << std::endl;
    std::cout << "fp_generic_util sqrt tests passed" << std::endl;
    return 0;
}
