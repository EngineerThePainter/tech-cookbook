#ifndef INJECT_HPP
#define INJECT_HPP

#include <iostream>

namespace details {

int C;

class C {

    public:
    static int f() {
        return sizeof(C);
    }
    private:
    int i[2];
};

int f() {
    return sizeof(C);
}

} // details

#endif