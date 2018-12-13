#include <iostream>

typedef enum {
    Monday = 0x01,
    Tuesday = 0x02,
    Wednesday = 0x04,
    Thursday = 0x08
} DAY;

void foo(int flag) {
    if(flag & DAY::Monday)
        std::cout << "DAY::Monday" << std::endl;
    if(flag & DAY::Tuesday)
        std::cout << "DAY::Tuesday" << std::endl;
    if(flag & DAY::Wednesday)
        std::cout << "DAY::Wednesday" << std::endl;
    if(flag & DAY::Thursday)
        std::cout << "DAY::Thursday" << std::endl;
}

int main() {
    foo(DAY::Monday);
    foo(DAY::Tuesday | DAY::Wednesday);
    foo(DAY::Monday | DAY::Thursday);
}