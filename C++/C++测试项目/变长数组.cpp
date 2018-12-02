#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

    int i = 1;
    ++i   = ++ i = ++i;
    cout << i << endl;
    return 0;
}