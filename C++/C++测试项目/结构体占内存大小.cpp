#include <iostream>
#include <stdio.h>

struct A {
    char sex;
    int year;
};

struct B {
    int year;
    char sex;
};

struct C{
    char a;
    int b;
    char c;
    double d;
};
// 1 + 3(占) + 4 + 1 + 3(占) + 8 = 16

struct D {
    char a;
    int b;
    char c;
    double d;
};
// 1 + 3(占) + 4 + 1 + 7(占) + 8 = 24

struct E {
    double a;
    char b;
    char c;
    int d;
    char e;
    double f;
    int g;
};
// 8 + 1 + 1 + 6(占) + 4 + 1 +3(占) + 8 + 4 + 4(占) = 40



int main(int argc, char const *argv[]) {
    {
        // 测试A
        A a = {'s', 1993};
        printf("%p\n", &a);          //000000000061fe14
        printf("%p\n", &a.sex);      //000000000061fe14
        printf("%p\n", &a.year);     //000000000061fe18
        printf("%p\n", &a + 1);      //000000000061fe1c
    }

    int i = 15;
    while(i--)
        putchar(10);

    {
        // 测试 B
        B b  = {1993, 's'};
        printf("%p\n", &b);         //000000000061fe0c
        printf("%p\n", &b.year);    //000000000061fe0c
        printf("%p\n", &b.sex);     //000000000061fe10
        printf("%p\n", &b + 1);     //000000000061fe14
    }

    {
        printf("%d\n", sizeof(E));
    }
    return 0;
}

// int char 会处理成 8
// int char char 会处理成 8
// int char char char 会处理成 8

// double char 会处理成 16
// char int double 会处理成 16

