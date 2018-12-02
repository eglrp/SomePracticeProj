/*
auto 的使用
 */

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class MyObjBuilder {
public:
    int makeObject() const {
        cout << "MyObjBuilder::makeObject()\n";
        return 0;
    }
};


// template<typename BuildType, typename Builder>
// void makeAndProcessProject(const Builder &builder) {
//     BuildType var = builder.makeObject();
// }

template<typename Builder>
void makeAndProcessProject(const Builder &builder) {
    auto val  = builder.makeObject();
}

int main(int argc, char const *argv[]) {

    // auto 的使用
    int x = 3;
    auto y = x;

    map<string, string> address_book;
    address_book["FIRST"] = "123456";
    map<string, string>::iterator iter = address_book.begin();
    auto iter2 = address_book.begin();

    MyObjBuilder builder;
    //makeAndProcessProject<int/*, MyObjBuilder*/>(builder);
    makeAndProcessProject/*<MyObjBuilder>*/(builder);

    // 区间迭代
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    for(auto i : vec) {
        cout << i << endl;
    }

    // 右括号的优化
    vector<vector<int> > vec2; // C++03
    vector<vector<int>> vec3; // C++11

    // 多线程
    //
    //

    // C++11 下的使用
    auto square_int = [](int x) {
        return x * x;
    };
    auto square_double = [](double y) {
        return y * y;
    };
    cout << square_int(3) << endl;
    cout << square_double(4.) << endl;

    // C++ 14 下可以这么写
    auto square = [](auto x) {
        return x * x;
    };
    cout << square(5) << endl;
    cout << square(6.0) << endl;

    // C++ 14 支持返回值类型的推导
    /*
    auto foo(){return 1;}
     */


    return 0;
}