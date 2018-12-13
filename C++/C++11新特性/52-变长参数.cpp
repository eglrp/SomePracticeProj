#include <iostream>

namespace TEST1 {

    template <typename T>
    T add(T a, T b, T c) {
        return a + b + c;
    }

    template<typename T, typename ... Args>
    T sum(T t, Args ... values ) {
        return add(t, values...);
    }

    template<typename T, typename ... Args>
    T sumOfAverage(T t, Args ... values ) {
        return add(t * t, (values * values)...);
    }

} // TEST1

namespace TEST2 {

    template <typename ... T>
    void dummy_wrapper(T... t) {
    };

    template <class T>
    T unpacker(const T t) {
        std::cout << '[' << t << ']';
        return t;
    }


    template <typename... Args>
    void write_line(const Args &... data) {
        dummy_wrapper(unpacker(data)...);
        std::cout << '\n';
    }

} // TEST2

namespace TEST3 {

    template <typename ... Tlist>
    void dummy_wrapper(Tlist... tlst) {
        std::cout << "dummy_wrapper(Tlist... tlst)" << std::endl;
    };

    template <class T>
    T unpacker(const T t) {
        std::cout << '[' << t << ']';
        return t;
    }

    template <typename T, typename ... Tlist>
    void dummy_wrapper(T t, Tlist... tlst) {
        unpacker(t);
        dummy_wrapper(tlst...); // 包扩展优先于单参数
    };

    template <typename... Args>
    void write_line(const Args &... data) {
        dummy_wrapper(data...);
        std::cout << '\n';
    }

} // TEST3


int main() {

    {
        std::cout << TEST1::add(1, 2, 3) << std::endl;
        // std::cout << TEST1::add(1, 2, 3, 4) << std::endl;
        std::cout << TEST1::sum(1, 2, 3) << std::endl;
        // std::cout << TEST1::sum(1, 2, 3, 4) << std::endl; // too many argc
        // std::cout << TEST1::sum(1, 2, 3.0f) << std::endl; // not same type
        std::cout << TEST1::sumOfAverage(1, 2, 3) << std::endl;
    }

    {
        TEST2::write_line(1, "--", "2", "--", 3.0f);
    }

    {
        TEST3::write_line(1, "--", "2", "--", 3.0f);
    }

    return 0;

}

/** https://blog.csdn.net/fullsail/article/details/42255063 */