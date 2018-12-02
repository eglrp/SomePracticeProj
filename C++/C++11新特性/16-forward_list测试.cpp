/*
 * Author: Neverland_LY
 * Date: 2018-11-16
 * ProjectName: forward_list
 * Version: v-1.0
 *
 * Description: https://blog.csdn.net/elloop/article/details/50405783
 *              http://www.cplusplus.com/reference/
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <forward_list>

using namespace std;

int main(int argc, char *argv[]) {

    // 基本用法
    {
        forward_list<int> fl = {1, 2, 3, 4, 5};
        for (const auto &elem : fl) {
            cout << elem << " ";
        }
        cout << endl;
    }


    cout << "Hello world!\n";

    return 0;
}