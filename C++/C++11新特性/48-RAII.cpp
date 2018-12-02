/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: RAII
 * Version: v-1.0
 *
 * Description: no
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <fstream>

using namespace std;

#if 0
void function() {
    FILE *f = fopen("test.txt", 'w');
    if (...) {
        fclose(f);
        return;
    } else if(...) {
        fclose(f);
        return;
    }

    fclose(f);
    ...
}

#endif

// https://www.cnblogs.com/jiangbin/p/6986511.html
#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)

class ScopeGuard {
public:
    explicit ScopeGuard(std::function<void()> f) :
        handle_exit_scope_(f) {
        cout << "ScopeGuard()\n";
    };

    ~ScopeGuard() {
        cout << " ~ScopeGuard()\n";
        handle_exit_scope_();
    }
private:
    std::function<void()> handle_exit_scope_;
};

class A {

};

int main(int argc, char *argv[]) {

    {
        {
            cout << "start\n";
            A *a = new A();
            ON_SCOPE_EXIT([&] {delete a; });
            cout << "A *a = new A();\n";
            //......
        }

        {
            cout << "start\n";
            std::ofstream f("test.txt");
            ON_SCOPE_EXIT([&] {f.close(); });
            cout << R"(std::ofstream f("test.txt"))" << "\n";
            //......
        }
    }


    cout << "Hello world!\n";

    return 0;
}