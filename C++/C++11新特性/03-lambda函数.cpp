#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 这样使用你必须先在其他地方创建函数
class AddressBook {
public:
    template<typename Func>
    vector<string> findMatchingAddress(Func func) {
        vector<string> results;
        for(auto itr = _addresses.begin(), end = _addresses.end(); itr != end; ++itr) {
            if(func(*itr))
                results.push_back(*itr);
        }
        return results;
    }
private:
    vector<string> _addresses;
};

AddressBook global_address_book;

vector<string> findAddressFromArgs() {
    return global_address_book.findMatchingAddress(
    [](const string & addr) ->bool {
        return addr.find(".org") != string::npos;
    });
}


class Foo {
public:
    Foo() : _x(3) {}
    void func() {
        [this]() {
            cout << "_x: " << _x << endl;
        }();
    }
private:
    int _x;
};


int test_lambda1() {
    {
        // int i = 3;
        // auto sum = [](int a) {
        //     return (a + i); // i can not be captured
        // };
        // cout << sum(10) << ' ' << i << endl;
    }

    {
        int i = 3;
        auto sum = [ = ](int a) {
            return (a + i);
        };
        cout << sum(10) << ' ' << i << endl;
    }

    {
        // int i = 3;
        // auto sum = [ = ](int a) {
        //     return (a + i++);  // i is read only
        // };
        // cout << sum(10) << ' ' << i << endl;
    }

    {
        int i = 3;
        auto sum = [ & ](int a) {
            return (a + i++);
        };
        cout << sum(10) << ' ' << i << endl;
    }

    {
        int i = 3;
        auto sum = [ & ](int a) {
            i++;
            cout << i << ' ';
            return (a + i++);
        };
        cout << sum(10) << ' ' << i << endl; // i is 3
    }



    {
        int i = 3;
        auto sum = [ = ](int a) mutable {
            i++; // i is no longer read-only, but i can not be modified from essence
            cout << i << ' ';
            return (a + i++);
        };
        cout << sum(10) << ' ' << i << endl; // i still is 3
    }

    {
        int i = 3;
        auto sum = [&](int a) {
            return (i += a);
        };
        // cout << sum(10) << " " << i << endl; // i still is 3, but why???
        cout << i << " " << sum(10) << endl; // then this is correct, this is because the sequence of exectute
    }

    return 0;
}


int main(int argc, char const *argv[]) {

    auto fun = []() {
        cout << "Hello world!\n";
    };

    fun();

    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    for_each(vec.begin(), vec.end(), [](int val) {
        cout << val << endl;
    });

    auto bar = [] {};

    /*

    []  不捕获任何变量
    [&] 以引用方式捕获所有变量
    [=] 用值的方式捕获所有变量（可能被编译器优化为const &)
    [=, &foo] 以引用捕获foo, 但其余变量都靠值捕获
    [bar] 以值方式捕获bar; 不捕获其它变量
    [this] 捕获所在类的this指针

     */



    Foo f;
    f.func();


    cout << "-----\n";

    test_lambda1();


    return 0;
}