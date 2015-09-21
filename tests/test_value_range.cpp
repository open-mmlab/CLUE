#include <cppstdx/value_range.hpp>
#include <gtest/gtest.h>
#include <vector>

template<typename T>
void test_unit_range(const cppstdx::value_range<T>& rgn, const T& a, const T& b) {
    using size_type = typename cppstdx::value_range<T>::size_type;
    using difference_type = typename cppstdx::value_range<T>::difference_type;

    ASSERT_EQ(a,   rgn.first());
    ASSERT_EQ(b,   rgn.last());
    ASSERT_EQ(a,   rgn.front());
    ASSERT_EQ(b-1, rgn.back());

    ASSERT_EQ(size_type(b - a), rgn.size());
    ASSERT_EQ((a == b), rgn.empty());

    auto ifirst = rgn.begin();
    auto ilast  = rgn.end();

    if (!rgn.empty()) {
        ASSERT_EQ(a, *ifirst);
        ASSERT_EQ(b, *ilast);
    }
    ASSERT_EQ((a == b), (ifirst == ilast));
    ASSERT_EQ((a != b), (ifirst != ilast));
    ASSERT_EQ((a <  b), (ifirst <  ilast));
    ASSERT_EQ((a <= b), (ifirst <= ilast));
    ASSERT_EQ((a >  b), (ifirst >  ilast));
    ASSERT_EQ((a >= b), (ifirst >= ilast));

    difference_type n = (difference_type)(rgn.size());
    ASSERT_EQ(ilast, ifirst + n);
    ASSERT_EQ(ifirst, ilast - n);
    ASSERT_EQ(n, ilast - ifirst);
    ASSERT_EQ(n, std::distance(ifirst, ilast));

    if (!rgn.empty()) {
        auto i1 = ifirst;
        ASSERT_EQ(a,   *(i1++));
        ASSERT_EQ(a+1, *i1);
        ASSERT_EQ(a+1, *(i1--));
        ASSERT_EQ(a,   *i1);

        auto i2 = ifirst;
        ASSERT_EQ(a+1, *(++i2));
        ASSERT_EQ(a+1, *i2);
        ASSERT_EQ(a,   *(--i2));
        ASSERT_EQ(a,   *i2);

        i1 += 1;
        ASSERT_EQ(a+1, *i1);
        i1 -= 1;
        ASSERT_EQ(a, *i1);

        ASSERT_EQ(a+1, *(ifirst+1));
        ASSERT_EQ(b-1, *(ilast-1));
    }

    std::vector<T> v_gt;
    for (T x = a; x != b; ++x) v_gt.push_back(x);
    ASSERT_TRUE(v_gt.size() == rgn.size());

    std::vector<T> v1;
    for (auto x: rgn) v1.push_back(x);
    ASSERT_EQ(v_gt, v1);

    std::vector<T> v2(ifirst, ilast);
    ASSERT_EQ(v_gt, v2);
}


TEST(ValueRanges, IntRanges) {

    using irange = cppstdx::value_range<int>;
    ASSERT_TRUE((std::is_same<irange::size_type, unsigned int>::value));
    ASSERT_TRUE((std::is_same<irange::difference_type, int>::value));

    test_unit_range(irange(0, 0), 0, 0);
    test_unit_range(irange(5, 5), 5, 5);
    test_unit_range(irange(3, 8), 3, 8);
}

TEST(ValueRanges, SizeRanges) {
    using std::size_t;
    using srange = cppstdx::value_range<std::size_t>;
    ASSERT_TRUE((std::is_same<srange::size_type, std::size_t>::value));
    ASSERT_TRUE((std::is_same<srange::difference_type, std::ptrdiff_t>::value));

    test_unit_range(srange(0, 0), size_t(0), size_t(0));
    test_unit_range(srange(5, 5), size_t(5), size_t(5));
    test_unit_range(srange(3, 8), size_t(3), size_t(8));
}

