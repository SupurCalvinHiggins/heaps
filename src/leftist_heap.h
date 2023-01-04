#pragma once

#include <queue>
#include <algorithm>
#include <cassert>
#include "priority_queue.h"

class LeftistHeap : public PriorityQueue {
private:
    class LeftistHeapNode {
    public:
        using node_type = LeftistHeapNode;
        using node_ptr = node_type *;

        LeftistHeapNode(value_type val) : val(val), rank(1), left(nullptr), right(nullptr) {}

        value_type val;
        size_type rank;
        node_ptr left;
        node_ptr right;
    };

    using node_type = LeftistHeapNode::node_type;
    using node_ptr = LeftistHeapNode::node_ptr;

    size_type size_;
    node_ptr root_;

    static node_ptr merge(node_ptr r1, node_ptr r2) noexcept {
        if (r1 == nullptr)
            return r2;

        if (r2 == nullptr)
            return r1;

        if (r1->val < r2->val)
            std::swap(r1, r2);

        r1->right = merge(r1->right, r2);

        if (r1->left == nullptr) {
            std::swap(r1->left, r1->right);
            r1->rank = 1;
            return r1;
        }

        if (r1->left->rank < r1->right->rank)
            std::swap(r1->left, r1->right);

        r1->rank = r1->left->rank + 1;
        return r1;
    }

public:
    explicit LeftistHeap(const std::vector<value_type> &vals) {
        size_ = vals.size();

        if (vals.empty()) {
            root_ = nullptr;
            return;
        }

        std::queue<node_ptr> q;
        for (const auto val: vals)
            q.push(new node_type(val));

        while (q.size() != 1) {
            auto n1 = q.back();
            q.pop();
            auto n2 = q.back();
            q.pop();
            q.push(merge(n1, n2));
        }

        root_ = q.back();
    }

    [[nodiscard]] bool empty() const noexcept override {
        return size() == 0;
    }

    [[nodiscard]] size_type size() const noexcept override {
        return size_;
    }

    [[nodiscard]] value_type max() const noexcept override {
        assert(!empty());
        return root_->val;
    }

    void push(value_type val) noexcept override {
        ++size_;
        auto node = new node_type(val);
        root_ = merge(root_, node);
    }

    void pop() noexcept override {
        assert(!empty());
        --size_;
        auto left = root_->left;
        auto right = root_->right;
        delete root_;
        root_ = merge(left, right);
    }
};
