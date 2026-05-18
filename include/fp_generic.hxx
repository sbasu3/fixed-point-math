#ifndef __FP_HXX
#define __FP_HXX

#include <cstdint>
#include <limits>
#include <type_traits>

template <int M, int N, typename Storage = std::int32_t>
class FixedPoint
{
public:
    static_assert(M >= 0, "M must be non-negative");
    static_assert(N > 0, "N must be positive");
    static_assert(std::is_integral<Storage>::value, "Storage must be an integral type");

    using storage_type = Storage;
    using wide_type = std::int64_t;
    static constexpr int integer_bits = M;
    static constexpr int fractional_bits = N;
    static constexpr storage_type scale = static_cast<storage_type>(1) << N;
    static constexpr storage_type nan_raw = std::numeric_limits<storage_type>::min();

    constexpr FixedPoint() : raw_(0) {}

    static constexpr FixedPoint from_raw(storage_type raw)
    {
        return FixedPoint(raw);
    }

    static constexpr FixedPoint from_int(int value)
    {
        return FixedPoint(static_cast<storage_type>(value) * scale);
    }

    static constexpr FixedPoint nan()
    {
        return FixedPoint(nan_raw);
    }

    static constexpr FixedPoint from_double(double value)
    {
        return FixedPoint(static_cast<storage_type>(value * static_cast<double>(scale)));
    }

    constexpr storage_type raw() const
    {
        return raw_;
    }

    constexpr bool is_nan() const
    {
        return raw_ == nan_raw;
    }

    constexpr double to_double() const
    {
        if (is_nan())
        {
            return std::numeric_limits<double>::quiet_NaN();
        }

        return static_cast<double>(raw_) / static_cast<double>(scale);
    }

    constexpr FixedPoint operator+(FixedPoint rhs) const
    {
        if (is_nan() || rhs.is_nan())
        {
            return nan();
        }

        return FixedPoint(static_cast<storage_type>(raw_ + rhs.raw_));
    }

    constexpr FixedPoint operator-(FixedPoint rhs) const
    {
        if (is_nan() || rhs.is_nan())
        {
            return nan();
        }

        return FixedPoint(static_cast<storage_type>(raw_ - rhs.raw_));
    }

    constexpr FixedPoint operator*(FixedPoint rhs) const
    {
        if (is_nan() || rhs.is_nan())
        {
            return nan();
        }

        const wide_type product = static_cast<wide_type>(raw_) * static_cast<wide_type>(rhs.raw_);
        return FixedPoint(static_cast<storage_type>(product >> N));
    }

    constexpr FixedPoint operator/(FixedPoint rhs) const
    {
        if (is_nan() || rhs.is_nan() || rhs.raw_ == 0)
        {
            return nan();
        }

        const wide_type dividend = static_cast<wide_type>(raw_) << N;
        return FixedPoint(static_cast<storage_type>(dividend / static_cast<wide_type>(rhs.raw_)));
    }

    constexpr bool operator==(FixedPoint rhs) const
    {
        if (is_nan() || rhs.is_nan())
        {
            return false;
        }

        return raw_ == rhs.raw_;
    }

    constexpr bool operator!=(FixedPoint rhs) const
    {
        return !(*this == rhs);
    }

    constexpr bool operator<(FixedPoint rhs) const
    {
        if (is_nan() || rhs.is_nan())
        {
            return false;
        }

        return raw_ < rhs.raw_;
    }
    constexpr bool operator<=(FixedPoint rhs) const
    {
        if (is_nan() || rhs.is_nan())
        {
            return false;
        }

        return raw_ <= rhs.raw_;
    }
    constexpr bool operator>(FixedPoint rhs) const
    {
        if (is_nan() || rhs.is_nan())
        {
            return false;
        }

        return raw_ > rhs.raw_;
    }
    constexpr bool operator>=(FixedPoint rhs) const
    {
        if (is_nan() || rhs.is_nan())
        {
            return false;
        }

        return raw_ >= rhs.raw_;
    }
    constexpr FixedPoint operator-() const
    {
        if (is_nan())
        {
            return nan();
        }

        return FixedPoint(-raw_);
    }
    constexpr FixedPoint &operator+=(FixedPoint rhs)
    {
        if (is_nan() || rhs.is_nan())
        {
            raw_ = nan_raw;
            return *this;
        }

        raw_ += rhs.raw_;
        return *this;
    }
    constexpr FixedPoint &operator-=(FixedPoint rhs)
    {
        if (is_nan() || rhs.is_nan())
        {
            raw_ = nan_raw;
            return *this;
        }

        raw_ -= rhs.raw_;
        return *this;
    }
    constexpr FixedPoint &operator*=(FixedPoint rhs)
    {
        if (is_nan() || rhs.is_nan())
        {
            raw_ = nan_raw;
            return *this;
        }

        const wide_type product = static_cast<wide_type>(raw_) * static_cast<wide_type>(rhs.raw_);
        raw_ = static_cast<storage_type>(product >> N);
        return *this;
    }
    constexpr FixedPoint &operator/=(FixedPoint rhs)
    {
        if (is_nan() || rhs.is_nan() || rhs.raw_ == 0)
        {
            raw_ = nan_raw;
            return *this;
        }

        const wide_type dividend = static_cast<wide_type>(raw_) << N;
        raw_ = static_cast<storage_type>(dividend / static_cast<wide_type>(rhs.raw_));
        return *this;
    }
    constexpr FixedPoint &operatorfrac()
    {
        if (is_nan())
        {
            return *this;
        }

        raw_ = raw_ & (scale - 1);
        return *this;
    }
    constexpr void print() const
    {
        if (is_nan())
        {
            std::cout << "NaN";
        }
        else
        {
            std::cout << to_double();
        }
    }

private:
    explicit constexpr FixedPoint(storage_type raw) : raw_(raw) {}

    storage_type raw_;
};

using q1_14_t = FixedPoint<1, 14, std::int16_t>;
using q1_30_t = FixedPoint<1, 30, std::int32_t>;

#endif
