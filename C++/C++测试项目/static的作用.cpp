#include <iostream>
#include <stdio.h>

class Student1 {
public:
    static int num;
    void printNum() {
        printf("我的学号是：%d\n", num);
    }

    Student1() {
        num ++;
    }
};
int Student1::num = 0;

class Student2 {
public:
    int num;
    void printNum() {
        printf("我的学号是：%d\n", num);
    }

    Student2() {
        num ++;
    }
};

int main(int argc, char const *argv[]) {

    Student1 s11, s12, s13;
    s11.printNum(); s12.printNum(); s13.printNum();

    Student1 s14; s14.printNum();
    Student1 s15; s15.printNum();
    Student1 s16; s16.printNum();

    printf("1--------------------\n");

    Student2 s21, s22, s23;
    s21.printNum(); s22.printNum(); s23.printNum();

    return 0;
}