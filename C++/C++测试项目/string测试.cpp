#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) {
    using std::cout;
    string s1("Hello"); cout << s1 << endl;
    string s2("Hello", 2); cout << s2 << endl;
    string s3(s1, 2); cout << s3 << endl;
    string s4(s1, 2, 2); cout << s4 << endl;
    string s5(5, 'a'); cout << s5 << endl;
    //string s6({'a', 'b', 'c'}); cout << s6 << endl;
    //
    cout << s1.size() << endl;
    cout << s1.length() << endl;
    cout << s1.capacity() << endl;

    s1.reserve(100);
    cout << s1.size() << endl;
    cout << s1.capacity() << endl;

    //s1.shrink_to_fit();
    cout << s1.size() << endl;
    cout << s1.capacity() << endl;

    s1.resize(9); cout << s1 << endl;
    s1.resize(12, 'L'); cout << s1 << endl;
    s1.resize(3); cout << s1 << endl;

    return 0;
}