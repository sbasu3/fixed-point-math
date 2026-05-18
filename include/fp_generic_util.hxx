#ifndef FP_GENERIC_UTIL_HXX
#define FP_GENERIC_UTIL_HXX

#include <limits>
#include "fp_generic.hxx"

template <int M, int N, typename Storage>
constexpr FixedPoint<M, N, Storage> fp_sqrt(FixedPoint<M, N, Storage> x)
{
    using fp_t = FixedPoint<M, N, Storage>;

    if (x.is_nan() || x.raw() < 0)
    {
        return fp_t::nan();
    }
    if (x.raw() == 0)
    {
        return fp_t::from_raw(0);
    }

    /* Initial guess: x / 2 */
    const fp_t half = fp_t::from_double(0.5);
    fp_t guess = x * half;
    if (guess.raw() == 0)
    {
        guess = fp_t::from_int(1);
    }

    /* Newton-Raphson: x_new = 0.5 * (x_old + S / x_old) */
    for (int i = 0; i < 5; i++)
    {
        fp_t div = x / guess;
        guess = (guess + div) * half;
    }

    return guess;
}

template <int M, int N, typename Storage>
constexpr int fp_leading_one_power(FixedPoint<M, N, Storage> x)
{
    using fp_t = FixedPoint<M, N, Storage>;
    using unsigned_storage_t = typename std::make_unsigned<Storage>::type;

    if (x.is_nan() || x.raw() == 0)
    {
        return std::numeric_limits<int>::min();
    }

    unsigned_storage_t magnitude;
    if (x.raw() < 0)
    {
        const typename fp_t::wide_type raw_wide = static_cast<typename fp_t::wide_type>(x.raw());
        magnitude = static_cast<unsigned_storage_t>(-raw_wide);
    }
    else
    {
        magnitude = static_cast<unsigned_storage_t>(x.raw());
    }

    int highest_bit = -1;
    while (magnitude != 0)
    {
        magnitude >>= 1;
        highest_bit++;
    }

    return highest_bit - N;
}

template <int M, int N, typename Storage>
constexpr FixedPoint<M, N, Storage> fp_inverse(FixedPoint<M, N, Storage> x)
{
    using fp_t = FixedPoint<M, N, Storage>;

    if (x.is_nan() || x.raw() == 0)
    {
        return fp_t::nan();
    }

    /* Initial guess for Newton-Raphson: start with a simple division */
    fp_t guess = fp_t::from_double(1.0) / x;

    /* Newton-Raphson: x_new = x_old * (2 - a * x_old) where a is input */
    for (int i = 0; i < 5; i++)
    {
        fp_t product = x * guess;
        fp_t delta = fp_t::from_double(2.0) - product;
        guess = guess * delta;
    }

    return guess;
}
#endif /* FP_GENERIC_UTIL_HXX */