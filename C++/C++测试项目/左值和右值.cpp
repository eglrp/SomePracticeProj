#include <iostream>
#include <string>

using namespace std;

class A {
public:
    int foo(const int &i) {
        std::cout << "This is const foo()!\n";
    }
    int foo(int &i) {
        std::cout << "This is non-const foo()!\n";
    }

    std::string  name;
};

void bar(const int &i) {
    cout << "successful!\n" << endl;
}

int main(int argc, char const *argv[]) {

    int i = 5;
    bar(5);




    return 0;
}