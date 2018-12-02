/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: std::bind
 * Version: v-Version
 *
 * Description: Description
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

double my_divide (double x, double y) {
    return x / y;
}
struct MyPair {
    double a, b;
    double multiply() {
        return a * b;
    }
};

int main(int argc, char *argv[]) {

    using namespace std::placeholders;

    auto fn_five = std::bind (my_divide, 10, 2); // returns 10/2
    cout << fn_five() << '\n'; // 10 / 2 = 5

    auto fn_half = std::bind (my_divide, std::placeholders::_1, 2); // return x / 2;
    cout << fn_half(10) << '\n'; // 10 / 2 = 5

    auto fn_invert = std::bind (my_divide, _2, _1); // returns y/x
    cout << fn_invert(10, 2) << '\n'; // 2 / 10 = 0.2

    auto fn_rounding = std::bind<int> (my_divide, _1, _2); // returns int(x/y)
    cout << fn_rounding(10, 3) << '\n'; // 10 / 3 = 3

    MyPair ten_two = {10, 2};
    auto bound_member_fn = std::bind (&MyPair::multiply, _1); // returns x.multiply()
    std::cout << bound_member_fn(ten_two) << '\n'; // 20

    // 这个重要
    auto bound_member_data = std::bind (&MyPair::a, ten_two); // returns ten_two.a
    std::cout << bound_member_data() << '\n'; // 10


    cout << "Hello world!\n";

    return 0;
}