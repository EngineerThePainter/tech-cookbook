#pragma once

class ClassHavingAllTraits
{
public:
    ClassHavingAllTraits() = default;
    ClassHavingAllTraits(const ClassHavingAllTraits &) = default;
    ClassHavingAllTraits &operator=(const ClassHavingAllTraits &) = default;

    ClassHavingAllTraits(ClassHavingAllTraits &&) = default;
    ClassHavingAllTraits &operator=(ClassHavingAllTraits &&) = default;
};