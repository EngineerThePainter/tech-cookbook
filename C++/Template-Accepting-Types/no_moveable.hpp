#pragma once

class NoMoveable
{
public:
    NoMoveable() = default;
    NoMoveable(const NoMoveable &) = default;
    NoMoveable &operator=(const NoMoveable &) = default;

    NoMoveable(NoMoveable &&) = delete;
    NoMoveable &&operator=(NoMoveable &&) = delete;
};