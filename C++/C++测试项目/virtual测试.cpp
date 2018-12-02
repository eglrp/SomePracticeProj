#include <iostream>
#include <string>

using namespace std;

class Dog {
public:
    Dog() {
        cout << "I'm just a dog!\n";
        bark();
    }

    void bark() {
        cout << "Wang wang!\n";
        cout <<  dogName << endl;
    }

    string dogName;
};

int main(int argc, char const *argv[]) {
    Dog d;
    return 0;
}