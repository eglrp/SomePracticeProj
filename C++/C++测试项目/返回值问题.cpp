#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

char *foo() {
    char *p = (char *)malloc(sizeof(char) * 5 );
    p[0] = 'y'; p[1] = 'u'; p[2] = 'a'; p[3] = 'n'; p[4] = '\0';
    printf("%s\n", p);
    return p;
}

void bar() {
    char *p = (char *)malloc(sizeof(char *) * 5);
    free(p);
}

void fun(char *p) {
    printf("%s\n", p);
}

int main() {
    char *ptr = foo();
    free(ptr);

    bar();

    fun(foo());
    // fun(bar());  就是错的，因为他没有返回值，所以要不要返回值要看你的需求

    return 0;
}

/*
// 写法一
for(; *q != '\0'; p++, q++)
    *p = *q;  //这个写在循环体里

*p = '\0'; // 最后给 *p 加上终止符

// 写法二
for(; *q != '\0'; *p = *q, p++, q++);
*p = '\0'; // 最后给 *p 加上终止符

// 注意事项，你这样写不对
// 因为 *p = *q 是赋值语句，永远正确，永远返回1或者true
// 1 永远不等于 '\0' ，所以你这样写无意义
// 区别于 *p == *q ，这是个判断语句
for(; (*p = *q) != '\0'; p++, q++);



int a = 3;
int b = 4;
for(;a = b; a++)
    printf("%d\n", a);

int a = 3;
int b = 4;
for(;a == b; a++)
    printf("%d\n", 1a);



char p[5] = "1234"; // 等价于 char p[5] = "1234\0"
char q[5] = "12345";

printf("%s\n", p);
printf("%s\n", q);*/