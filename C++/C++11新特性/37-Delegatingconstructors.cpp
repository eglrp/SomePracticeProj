/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: Delegating constructors
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

// 此种情况下，必须提供无参构造器，否则编译通不过。
class Obj {
public:
    Obj(): Obj(0) {}
    Obj(int a): _a(a) {}
private:
    int _a;
};

int main(int argc, char *argv[]) {
    Obj o;
    return 0;
}