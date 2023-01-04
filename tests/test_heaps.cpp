#include <vector>
#include "gtest/gtest.h"
#include "leftist_heap.h"
#include "maxiphobic_heap.h"

template<typename T>
class HeapTest : public testing::Test {
public:
    using heap_type = T;
};

using HeapTypes = ::testing::Types<LeftistHeap, MaxiphobicHeap>;
TYPED_TEST_SUITE(HeapTest, HeapTypes);

TYPED_TEST(HeapTest, EmptyWithEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values;
    heap_type heap(values);

    EXPECT_TRUE(heap.empty());
}

TYPED_TEST(HeapTest, SizeWithEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values;
    heap_type heap(values);

    EXPECT_EQ(heap.size(), 0);
}

TYPED_TEST(HeapTest, MaxWithEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values;
    heap_type heap(values);

    EXPECT_DEATH({ heap.max(); }, "");
}

TYPED_TEST(HeapTest, PopWithEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values;
    heap_type heap(values);

    EXPECT_DEATH({ heap.pop(); }, "");
}

TYPED_TEST(HeapTest, PushWithEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values;
    heap_type heap(values);

    heap.push(7);

    EXPECT_FALSE(heap.empty());
    EXPECT_EQ(heap.size(), 1);
    EXPECT_EQ(heap.max(), 7);
}

TYPED_TEST(HeapTest, FillWithEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values;
    heap_type heap(values);

    std::vector<value_type> push_values{7, 3, 8, 9, 1, 2, 4, 6, 5, 0};
    std::vector<value_type> max_after_push{7, 7, 8, 9, 9, 9, 9, 9, 9, 9};
    for (int i = 0; i < push_values.size(); ++i) {
        const auto value = push_values[i];
        heap.push(value);

        const auto max = max_after_push[i];
        const auto size = i + 1;
        EXPECT_FALSE(heap.empty());
        EXPECT_EQ(heap.size(), size);
        EXPECT_EQ(heap.max(), max);
    }
}

TYPED_TEST(HeapTest, FillDrainWithEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values;
    heap_type heap(values);

    std::vector<value_type> push_values{3, 7, 1, 2, 8, 4, 9, 0, 5, 6};
    for (const auto value: push_values)
        heap.push(value);

    for (int i = 0; i < push_values.size(); ++i) {
        const auto max = 9 - i;
        const auto size = 10 - i;
        EXPECT_FALSE(heap.empty());
        EXPECT_EQ(heap.size(), size);
        EXPECT_EQ(heap.max(), max);

        heap.pop();
    }

    EXPECT_TRUE(heap.empty());
    EXPECT_EQ(heap.size(), 0);
}

TYPED_TEST(HeapTest, FillDrainFillWithEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values;
    heap_type heap(values);

    std::vector<value_type> push_values{1, 6, 7, 3, 2, 8, 4, 0, 5, 9};
    for (const auto value: push_values)
        heap.push(value);

    for (const auto _: push_values)
        heap.pop();

    std::vector<value_type> max_after_push{1, 6, 7, 7, 7, 8, 8, 8, 8, 9};
    for (int i = 0; i < push_values.size(); ++i) {
        const auto value = push_values[i];
        heap.push(value);

        const auto max = max_after_push[i];
        const auto size = i + 1;
        EXPECT_FALSE(heap.empty());
        EXPECT_EQ(heap.size(), size);
        EXPECT_EQ(heap.max(), max);
    }
}

TYPED_TEST(HeapTest, EmptyWithNonEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values{0};
    heap_type heap(values);

    EXPECT_FALSE(heap.empty());
}

TYPED_TEST(HeapTest, SizeWithNonEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values{0};
    heap_type heap(values);

    EXPECT_EQ(heap.size(), 1);
}

TYPED_TEST(HeapTest, MaxWithNonEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values{2, 3, 0, 1, 5, 4};
    heap_type heap(values);

    EXPECT_EQ(heap.max(), 5);
}

TYPED_TEST(HeapTest, PopWithNonEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values{2, 3, 0, 1, 5, 4};
    heap_type heap(values);

    heap.pop();
    EXPECT_FALSE(heap.empty());
    EXPECT_EQ(heap.size(), 5);
    EXPECT_EQ(heap.max(), 4);
}

TYPED_TEST(HeapTest, PushWithNonEmptyInit) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values{2, 3, 0, 1, 5, 4};
    heap_type heap(values);

    heap.push(7);
    EXPECT_FALSE(heap.empty());
    EXPECT_EQ(heap.size(), 7);
    EXPECT_EQ(heap.max(), 7);

    heap.push(6);
    EXPECT_FALSE(heap.empty());
    EXPECT_EQ(heap.size(), 8);
    EXPECT_EQ(heap.max(), 7);
}

TYPED_TEST(HeapTest, DrainWithNonEmptyInit) {}

TYPED_TEST(HeapTest, FillWithNonEmptyInit) {}

TYPED_TEST(HeapTest, FillDrainWithNonEmptyInit) {}

TYPED_TEST(HeapTest, DrainFillWithNonEmptyInit) {}

TYPED_TEST(HeapTest, FillDrainFillWithNonEmptyInit) {}