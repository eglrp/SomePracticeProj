#include <stdio.h>

int main() {
    char firstname[30] = "li";
    char lastname[30] = "yuan";
    char *p = firstname; // p 在这里指向了'l'

    // 这里定义了一个局部变量 p ，这里的 p 和上面的 p 是两个不同的变量
    // 所以这里对 p 的操作不会影响到上面的 p
    //                                'l' 'i' '\0'
    // 当你执行完该语句后 p 还是指向   ^
    //                                 |
    // 所以相当于从头开始复制复制 q 的内容
    for(char *p = firstname; *p != '\0'; p++);


    // 这里的 p = firstname，相当于重复了上面的定义
    for(p = firstname; *p != '\0'; p++);
    // 所以该语句还可以写成如下
    for( ; *p != '\0'; p++);
    //                                'l' 'i' '\0'
    // 当你执行完该语句后 p 已经指向           ^
    //                                         |
    // 所以相当于在 li后面继续复制 q 的内容


    // 这里定义了一个局部变量 q
    for(char *q = lastname; *p = *q; p++, q++);

    printf("%s\n", firstname);

    return 0;
}