#pragma once

class NoAssignable
{
public:
    NoAssignable() = default;
    NoAssignable(const NoAssignable &) = default;
    NoAssignable &operator=(const NoAssignable &) = delete;
    NoAssignable(NoAssignable &&) = default;
    NoAssignable &operator=(NoAssignable &&) = delete;
};