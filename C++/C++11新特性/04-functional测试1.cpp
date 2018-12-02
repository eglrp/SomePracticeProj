#include <functional>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

class AddressBook {
public:
    vector<string> findMatchingAddresses(function<bool (const string &)> func) {
        vector<string> results;
        for(auto itr = _addresses.begin(), end = _addresses.end(); itr != end; ++itr) {
            if(func(*itr)) {
                results.push_back(*itr);
            }
        }
        return results;
    }

private:
    vector<string> _addresses;
};


int add(int i, int j) {
    return i + j;
}
int _minus(int i, int j) {
    return i - j;
}

typedef int(*MINUS)(int, int);

auto multiply = [](int i, int j) {
    return i * j;
};

class Divide {
public:
    int operator()(int i, int j) {
        return i / j;
    }
};

int main(int argc, char const *argv[]) {

    function<int ()> foo = []() {
        return 1;
    };

    if(foo)
        cout << "Contain function\n";

    typedef int (*func)();
    func f = []() ->int {return 2;};
    f();


    {
        std::function<int(int, int)> oper;
        oper = add;
        cout << oper(1, 2) << endl;
        MINUS m = _minus;
        oper = m;
        cout << oper(10, 1) << endl;
        oper = multiply;
        cout << oper(1, 2) << endl;
        oper = Divide();
        cout << oper(10, 2) << endl;

        map<string, std::function<int(int, int)>> math;
        math.insert({"+", add});
        math.insert({"-", _minus});
        math.insert({"*", multiply});
        math.insert({"/", Divide()});
        math.insert({"%", [](int i, int j) {
            return i % j;
        }});

        cout << math["+"](10, 5) << endl;
        cout << math["-"](10, 5) << endl;
        cout << math["*"](10, 5) << endl;
        cout << math["/"](10, 5) << endl;
        cout << math["%"](10, 5) << endl;
    }

    return 0;
}