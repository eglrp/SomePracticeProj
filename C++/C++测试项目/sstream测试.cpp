#include <iostream>
#include <sstream>

using namespace std;

int main() {
    istringstream istr;
    istr.str("156.7   3.14  5.96");  // 只能以空格作为分隔符
    //istr.str("156.7,3.14,5.96");
    cout << istr.str() << endl;
    float a;
    istr >> a;
    cout << a << endl;
    float b;
    istr >> b ;
    cout << b << endl;
    float c;
    istr >> c;
    cout << c << endl;

    ostringstream ostr;
    ostr.put('d');
    ostr.put('e');
    cout << ostr.str() << endl;
    ostr << "fgccc";
    cout << ostr.str() << endl;

    return 0;
}