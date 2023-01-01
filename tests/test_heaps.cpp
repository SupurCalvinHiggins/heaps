#include <vector>
#include "gtest/gtest.h"
#include "leftist_heap.h"


template <typename T>
class HeapTest : public testing::Test {
public:
    using heap_type = T;
};


using HeapTypes = ::testing::Types<LeftistHeap>;
TYPED_TEST_SUITE(HeapTest, HeapTypes);


TYPED_TEST(HeapTest, EmptyOnConstruction) {
    using heap_type = typename TestFixture::heap_type;
    using value_type = typename heap_type::value_type;

    std::vector<value_type> values;
    heap_type heap(values);

    ASSERT_TRUE(heap.empty());
}