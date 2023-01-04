#pragma once

#include <algorithm>
#include <cassert>
#include "priority_queue.h"

class MaxiphobicHeap : public PriorityQueue {

private:
    class MaxiphobicHeapNode {
    public:
        using node_type = MaxiphobicHeapNode;
        using node_ptr = node_type *;

        MaxiphobicHeapNode(value_type val) : val(val), size(1), left(nullptr), right(nullptr) {}

        value_type val;
        size_type size;
        node_ptr left;
        node_ptr right;
    };

    using node_type = MaxiphobicHeapNode::node_type;
    using node_ptr = MaxiphobicHeapNode::node_ptr;

    size_type size_;
    node_ptr root_;

    static node_ptr merge(node_ptr r1, node_ptr r2) {
        if (r1 == nullptr) return r2;
        if (r2 == nullptr) return r1;

        assert(r1 != nullptr);
        assert(r2 != nullptr);

        if (r1->val < r2->val) std::swap(r1, r2);

        assert(r1->val >= r2->val);

        if (r1->left == nullptr) {
            r1->left = r2;
            r1->size += r2->size;
            return r1;
        }

        if (r1->right == nullptr) {
            r1->right = r2;
            r1->size += r2->size;
            return r1;
        }

        assert(r1->right != nullptr);
        assert(r1->left != nullptr);

        if (r1->left->size < r1->right->size)
            std::swap(r1->left, r1->right);

        assert(r1->left->size >= r1->right->size);

        if (r1->left->size < r2->size) {
            r1->left = merge(r1->left, r1->right);
            r1->right = r2;
        } else {
            r1->right = merge(r1->right, r2);
        }

        r1->size = r1->left->size + r1->right->size + 1;
        return r1;
    }

public:
    explicit MaxiphobicHeap(const std::vector<value_type>& vals) {
        size_ = vals.size();

        if (vals.empty()) {
            root_ = nullptr;
            return;
        }

        std::queue<node_ptr> q;
        for (const auto val : vals) {
            q.push(new node_type(val));
        }

        while (q.size() != 1) {
            auto r1 = q.back();
            q.pop();
            auto r2 = q.back();
            q.pop();
            q.push(merge(r1, r2));
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