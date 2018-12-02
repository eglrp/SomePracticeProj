#if 0
#include <stdio.h>
#include <string.h>

typedef struct student {
    char name[100];
    // char * name = NULL;
    char sex;
    int age;
    float score;
} STU;

int main(int argc, char const *argv[]) {
    STU s;
    printf("please input name:");
    scanf("%s\n", s.name);
    //getchar();

    printf("please input sex:");
    scanf("%c", &s.sex);

    printf("please input age:");
    scanf("%d", &s.age);

    printf("please input score:");
    scanf("%f", &s.score);

    printf("name   =%s\n", s.name);
    printf("sex    =%c\n", s.sex);
    printf("age    =%d\n", s.age);
    printf("score  =%.2f\n", s.score);

    return 0;
}

#endif


#include <stdio.h>
#include <Windows.h>

// #define LY 1

int main() {
#ifdef LY
    {
        printf("define!\n");
        char str[80];
        char str1[80];
        char str2[80];

        scanf("%s", str); /*此处输入:I love you! */
        printf("%s", str);
        Sleep(3000);/*这里等待5秒,告诉你程序运行到什么地方*/
        scanf("%s", str1); /*这两句无需你再输入,是对键盘盘缓冲区再扫描   */
        scanf("%s", str2); /*这两句无需你再输入,是对键盘盘缓冲区再扫描    */
        printf("/n%s", str1);
        printf("/n%s", str2);
    }
#endif

    { // 失败
        char string[50];
        printf("11111\n");
        /*scanf("%s",string);不能接收空格符*/
        scanf("%[^/n]\n", string);
        getchar();
        printf("22222\n");
        printf("%s/n", string);
    }

    return 0;
}

