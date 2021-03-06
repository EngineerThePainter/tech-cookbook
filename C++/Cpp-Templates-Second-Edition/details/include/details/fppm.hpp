#ifndef FPPM_HPP
#define FPPM_HPP

namespace details {

template<int N>
class X {
  public:
    using I = int;
    void f(int) {

    }
};

template<int N>
void fppm(void (X<N>::*p)(typename X<N>::I)) {

}

} // namespace details

#endif // FPPM_HPP