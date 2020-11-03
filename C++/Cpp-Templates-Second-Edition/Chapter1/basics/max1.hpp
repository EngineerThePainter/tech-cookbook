namespace basics {

template<typename T>
T max(T a, T b) {
    return b < a ? a : b;
}

template<typename T1, typename T2>
T1 maxWithT1ReturnType(T1 a, T2 b) {
    return b < a ? a : b;
}

template<typename T1, typename T2, typename RT>
RT maxWithRTReturnType(T1 a, T2 b) {
    return b < a ? a : b;
}

template<typename RT, typename T1, typename T2>
RT maxWithRTReturnTypeAsFirstArgument(T1 a, T2 b) {
    return b < a ? a : b;
}

template<typename T1, typename T2>
auto maxWithAuto(T1 a, T2 b) {
    return b < a ? a : b;
}

}