#pragma once


#include <cstdlib>


class BaseHeap {
public:
    using size_type = std::size_t;
    using value_type = int;

    [[nodiscard]] virtual bool empty() const noexcept = 0;
    [[nodiscard]] virtual size_type size() const noexcept = 0;
    [[nodiscard]] virtual value_type max() const noexcept = 0;
    virtual void push(value_type val) noexcept = 0;
    virtual void pop() noexcept = 0;
};