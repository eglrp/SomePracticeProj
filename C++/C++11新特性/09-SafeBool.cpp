/*
 * Author: Neverland_LY
 * Date: 2018-11-15
 * ProjectName: SafeBool
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

// 为 class 提供真假的能力，即 if(class_name)
class CData1 {
public:
    bool isValid() const {
        return true;
    }
};

// 重载 operator ()
class CData2 {
public:
    operator bool() const {
        return true;
    }
};

// safe bool 的实现
class Testable {
public:
    bool ok_;
    typedef void (Testable::*bool_type)() const;


    void this_type_can_not_support_comparisons() const {}
public:
    explicit Testable(bool b = true) : ok_(b) {}

    operator bool_type() const {
        return ok_ == true ? &Testable::this_type_can_not_support_comparisons : 0;
    }
};

class TestableOther {
    bool ok_;
    typedef void (TestableOther::*bool_type)() const;
    void this_type_can_not_support_comparisons() const {}
public:
    explicit TestableOther(bool b = true) : ok_(b) {}

    operator bool_type() const {
        return ok_ == true ? &TestableOther::this_type_can_not_support_comparisons : 0;
    }
};

// bool 操作符的副作用
template<typename T>
class CPtr {
    T *ptr;
public:
    operator bool() const {
        return ptr != nullptr;
    }
};

int main(int argc, char *argv[]) {

    // Todo...
    CData1 data1;
    if(data1.isValid()) {
        cout << "data1 is valid!\n";
    }

    CData2 data2;
    if(data2) {
        cout << "data2 is valid!\n";
    }

    CPtr<int> p1;
    CPtr<float> p2;
    if( p1 == p2) {
        cout << "ERROR! We are not same!\n";
    }

    Testable test;
    TestableOther testother;
    if(test) {
        cout << "Correct!\n";
    }

    // 这样就不会出现上面写的副作用了
    // if(test == testother){
    //     // err
    // }


    cout << "Hello world!\n";

    return 0;
}