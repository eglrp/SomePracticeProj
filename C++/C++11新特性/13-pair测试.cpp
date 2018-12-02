/*
 * Author: Neverland_LY
 * Date: 2018-11-16
 * ProjectName: pair
 * Version: v-1.0
 *
 * Description: https://www.cnblogs.com/lvchaoshun/p/7769003.html
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class CLASSNAME {
public:
    CLASSNAME() {}
    ~CLASSNAME() {}
private:

};

int main(int argc, char *argv[]) {

    // Todo...
    // 定义
    {
        pair<int, double> p1;  //使用默认构造函数
        pair<int, double> p2(1, 2.4);  //用给定值初始化
        pair<int, double> p3(p2);  //拷贝构造函数
    }

    // 访问两个元素
    {
        pair<int, double> p1;  //使用默认构造函数
        p1.first = 1;
        p1.second = 2.5;
        cout << p1.first << ' ' << p1.second << endl;
    }

    // operator=
    {
        pair<int, double> p1;
        p1 = make_pair(1, 1.2);
        pair<int, double> p2 = p1;
    }

    cout << "Hello world!\n";

    return 0;
}