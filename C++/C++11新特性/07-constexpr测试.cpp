#include <iostream>
#include <string>

using namespace std;

constexpr int multiply(int x, int y) {
    return x * y;
}

constexpr int getDefaultArraySize(int multiplier) {
    return 10 * multiplier;
}

class Circle {
public:
    constexpr Circle(int x, int y, int radius)
        : _x(x), _y(y), _radius(radius) {}

    constexpr double getArea() {
        return (_radius * _radius * 3.1415926);
    }

private:
    int _x;
    int _y;
    int _radius;
};

/*constexpr*/Circle c(0, 0, 10);
/*constexpr*/double area = c.getArea();

// 函数中只能有一个return语句
constexpr int factorial(int n) {
    return n > 0 ? n * factorial(n - 1) : 1;
}

int main(int argc, char const *argv[]) {
    const int val = multiply(1, 2);

    // 不能直接用函数的返回值声明数组的大小，但是加了 cconstexpr 就可以了
    int array[getDefaultArraySize(10)];

    // 既可以在编译时，也可以在运行时候调用
    int a;
    cin >> a;
    cout << a << " 的阶乘是: " << factorial(a) << endl;

    return 0;
}

/*

一个constexpr有一些必须遵循的严格要求：

1. 函数中只能有一个return语句（有极少特例）
2. 只能调用其它constexpr函数
3. 只能使用全局constexpr变量

一个constexpr函数，只允许包含一行可执行代码。
但允许包含typedefs、 using declaration && directives、静态断言等。

 */