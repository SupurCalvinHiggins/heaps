#pragma once


#include <algorithm>
#include <cassert>
#include "base_heap.h"


class LeftistHeap : public BaseHeap {
private:

    class LeftistHeapNode {
    public:
        using node_type = LeftistHeapNode;
        using node_ptr = node_type*;

        LeftistHeapNode(value_type val, size_type rank, node_ptr left, node_ptr right) : val(val), rank(rank), left(left), right(right) {}

        value_type val;
        size_type rank;
        node_ptr left;
        node_ptr right;
    };

    using node_type = LeftistHeapNode::node_type;
    using node_ptr = LeftistHeapNode::node_ptr;

    size_type size_;
    node_ptr head_;

    static node_ptr merge(node_ptr h1, node_ptr h2) noexcept {
        if (h1 == nullptr)
            return h2;

        if (h2 == nullptr)
            return h1;

        if (h1->val < h2->val)
            std::swap(h1, h2);

        h1->right = merge(h1->right, h2);

        if (h1->left == nullptr) {
            std::swap(h1->left, h1->right);
            h1->rank = 1;
            return h1;
        }

        if (h1->left->rank < h1->right->rank)
            std::swap(h1->left, h1->right);

        h1->rank = h1->left->rank + 1;
        return h1;
    }

public:

    explicit LeftistHeap(const std::vector<value_type>& values) : head_(nullptr), size_(0) {}

    [[nodiscard]] bool empty() const noexcept override {
        return size() == 0;
    }

    [[nodiscard]] size_type size() const noexcept override {
        return size_;
    }

    [[nodiscard]] value_type max() const noexcept override {
        assert(!empty());
        return head_->val;
    }

    void push(value_type val) noexcept override {
        auto node = new node_type(val, 1, nullptr, nullptr);
        head_ = merge(head_, node);
    }

    void pop() noexcept override {
        assert(!empty());
        auto left = head_->left;
        auto right = head_->right;
        delete head_;
        head_ = merge(left, right);
    }
};
