#pragma once

#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
#include "priority_queue.h"

class SkewHeap : public PriorityQueue {
private:

    class SkewHeapNode {
    public:
        using node_type = SkewHeapNode;
        using node_ptr = node_type*;

        SkewHeapNode(value_type val) : val(val), left(nullptr), right(nullptr) {}

        value_type val;
        node_ptr left;
        node_ptr right;
    };

    using node_type = SkewHeapNode::node_type;
    using node_ptr = SkewHeapNode::node_ptr;

    size_type size_;
    node_ptr root_;

    static node_ptr merge(node_ptr r1, node_ptr r2) {
        if (r1 == nullptr) return r2;
        if (r2 == nullptr) return r1;

        if (r1->val < r2->val) std::swap(r1, r2);

        r1->right = merge(r1->right, r2);
        std::swap(r1->left, r1->right);
        return r1;
    }

public:
    explicit SkewHeap(const std::vector<value_type>& vals) {
        size_ = vals.size();

        if (vals.empty()) {
            root_ = nullptr;
            return;
        }

        std::queue<node_ptr> q;
        for (const auto val : vals)
            q.push(new node_type(val));

        while (q.size() > 1) {
            auto r1 = q.front();
            q.pop();
            auto r2 = q.front();
            q.pop();
            q.push(merge(r1, r2));
        }

        root_ = q.front();
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