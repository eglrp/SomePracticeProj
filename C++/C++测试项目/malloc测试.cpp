#include <stdlib.h>
#include <stdio.h>

int yunyuan_age = 23;

// 编程中经常说的 get set 方法
int getAge() {
    return yunyuan_age;
}
void setAge(int age) {
    yunyuan_age = age;
}

int main() {
    printf("圆圆的年龄是：%s岁\n", getAge());
    setAge(23);
    printf("圆圆的年龄是：%s岁\n", getAge());/*青春永驻*/
    return 0;
}