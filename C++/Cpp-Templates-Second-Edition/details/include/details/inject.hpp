#ifndef INJECT_HPP
#define INJECT_HPP

#include <iostream>

namespace details {

int C;

class C {

    public:
    C() {
        //Just to avoid unused vatiable error
        i[0] = 1;
        i[1] = 2;
    }
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