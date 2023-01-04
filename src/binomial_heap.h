#pragma once

#include <vector>
#include <cassert>
#include "priority_queue.h"

class BinomialHeap : public PriorityQueue {
private:
    class BinomialHeapNode {
    public:
        using node_type = BinomialHeapNode;
        using node_ptr = node_type *;

        BinomialHeapNode() {}

        value_type val;
        node_ptr next;
        node_ptr child;
    };

    using node_type = BinomialHeapNode::node_type;
    using node_ptr = BinomialHeapNode::node_ptr;

    size_type size_;
    node_ptr root_;
    value_type max_;

    static node_ptr merge(node_ptr r1, node_ptr r2) noexcept {
        assert(false);
        return r1;
    }

public:
    explicit BinomialHeap(const std::vector<value_type> &vals) {
        assert(false);
    }

    [[nodiscard]] bool empty() const noexcept override {
        return size() == 0;
    }

    [[nodiscard]] virtual size_type size() const noexcept override {
        return size_;
    }

    [[nodiscard]] virtual value_type max() const noexcept override {
        assert(!empty());
        return max_;
    }

    virtual void push(value_type val) noexcept override {
        ++size_;
        if (val > max_)
            max_ = val;

        // push here.
        assert(false);
    }

    virtual void pop() noexcept override {
        assert(!empty());
        --size_;

        // do the pop
        assert(false);

        // get the tree with the max as the root
        // remove the tree from the data structure
        // build new binomial heap from child subtrees
        // merge the heaps

        node_ptr prev = nullptr;
        auto cur = root_;
        while (cur->val != max_) {
            prev = cur;
            cur = cur->next;
        }

        assert(cur != nullptr);

        // if we are removing the root, maitain the root
        if (prev == nullptr) {
            root_ = root_->next;
        }
            // otherwise, unlink the max
        else {
            prev->next = cur->next;
        }

        // need to reverse the subtree order to make a heap
        node_ptr new_heap = nullptr;
        auto subtree = cur->child;
        while (subtree) {
            auto next_subtree = subtree->next;
            subtree->next = new_heap;
            new_heap = subtree;
            subtree = next_subtree;
        }

        // merge the heaps
        root_ = merge(root_, new_heap);

        // recompute max
        auto cur = root_;
        max_ = root_->val;
        while (cur != nullptr) {
            if (cur->val > max_)
                max_ = cur->val;
            cur = cur->next;
        }
    }
};