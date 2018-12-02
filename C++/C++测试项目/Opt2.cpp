#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

// 短参数测试案例
void testGetOpt(int argc, char *argv[]) {
    int opt;  // getopt() 的返回值
    const char *optstring = "abc:d"; // 设置短参数类型及是否需要参数

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        printf("opt = %c\n", opt);  // 命令参数，亦即 -a -b -c -d
        printf("optarg = %s\n", optarg); // 参数内容
        printf("optind = %d\n", optind); // 下一个被处理的下标值
        printf("argv[optind - 1] = %s\n\n",  argv[optind - 1]); // 参数内容
    }
}

// 长参数测试案例
void testGetOptLong(int argc, char *argv[]) {
    int opt; // getopt_long() 的返回值
    int digit_optind = 0; // 设置短参数类型及是否需要参数

    // 如果option_index非空，它指向的变量将记录当前找到参数符合long_opts里的
    // 第几个元素的描述，即是long_opts的下标值
    int option_index = 666/*0*/;
    // 设置短参数类型及是否需要参数
    const char *optstring = "ab:nr:";

    // 设置长参数类型及其简写，比如 --reqarg <==>-r
    /*
    struct option {
             const char * name;  // 参数的名称
             int has_arg; // 是否带参数值，有三种：no_argument， required_argument，optional_argument
             int * flag; // 为空时，函数直接将 val 的数值从getopt_long的返回值返回出去，
                     // 当非空时，val的值会被赋到 flag 指向的整型数中，而函数返回值为0
             int val; // 用于指定函数找到该选项时的返回值，或者当flag非空时指定flag指向的数据的值
        };
    其中：
        no_argument(即0)，表明这个长参数不带参数（即不带数值，如：--name）
            required_argument(即1)，表明这个长参数必须带参数（即必须带数值，如：--name Bob）
            optional_argument(即2)，表明这个长参数后面带的参数是可选的，（即--name和--name Bob均可）
     */
    static struct option long_options[] = {
        {"reqarg", required_argument, NULL, 'A'},
        {"noarg",  no_argument,       NULL, 'B'},
        {"optarg", optional_argument, NULL, 'C'},
        {0, 0, 0, 0}  // 添加 {0, 0, 0, 0} 是为了防止输入空值
    };

    while ( (opt = getopt_long(argc,
                               argv,
                               optstring,
                               long_options,
                               &option_index)) != -1) {
        printf("opt = %c\n", opt); // 命令参数，亦即 -a -b -n -r
        printf("optarg = %s\n", optarg); // 参数内容
        printf("optind = %d\n", optind); // 下一个被处理的下标值
        printf("argv[optind - 1] = %s\n",  argv[optind - 1]); // 参数内容
        printf("option_index = %d\n", option_index);  // 当前打印参数的下标值
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    testGetOpt(argc, argv);
    // testGetOptLong(argc, argv);
    return 0;
}