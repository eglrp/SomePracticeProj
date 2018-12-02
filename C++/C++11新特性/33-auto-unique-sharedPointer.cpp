/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: auto_ptr
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <memory>

using namespace std;

class Copyable {
public:
    Copyable(int i): _i(new int(i)) {
        cout << "Copyable(int i)" << endl;
    }
    Copyable(const Copyable &another): _i(new int(*another._i)) {
        cout << " Copyable(const Copyable & another)" << endl;
    }
    ~Copyable() {
        cout << "~Copyable()" << endl;
    }
    int *_i;
};

int main(int argc, char *argv[]) {

    {
        // warning: 'template<class> class std::auto_ptr' is deprecated [-Wdeprecated-declarations]
        auto_ptr<Copyable> apc(new Copyable(10));
        cout << *apc->_i << endl;

        // warning: 'template<class> class std::auto_ptr' is deprecated [-Wdeprecated-declarations]
        auto_ptr<Copyable> apcapc(apc);
        // cout<<*apc->_i<<endl; // error
        cout << *apcapc->_i << endl;
    }

    {
        // 实现了资源的唯一,既不可以拷贝也不可以赋值
        // unique_ptr 可以用于数组
        unique_ptr<Copyable> unc(new Copyable(10));
        cout << *unc->_i << endl;
        // unique_ptr<Copyable> uncunc(unc);
        // error: use of deleted function 'std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&)

        // cout << *uncunc->_i << endl;
        unique_ptr<Copyable> unc2;
        // unc2 = unc;
        // error: use of deleted function 'std::unique_ptr<_Tp, _Dp>& std::unique_ptr<_Tp, _Dp>::operator=(const std::unique_ptr<_Tp, _Dp>&)
    }

    {
        cout << "-------------\n";
        // deprecated
        auto_ptr<int> ap(new int);
        cout << *ap << endl;
        *ap = 100;
        cout << *ap << endl;

        unique_ptr<int> up(new int);
        cout << *up << endl;
        *up = 100;
        cout << *up << endl;

        unique_ptr<Copyable> upc(new Copyable(10));
        upc.reset(new Copyable(100));
        cout << (upc.get()) << endl;
        Copyable *p = upc.release();
        if(!upc) {
            cout << "upc has no pointer" << endl;
        }
        delete p;
    }

    {
        shared_ptr<int> sp;
        if(!sp) {
            cout << "sp has none" << endl;
        }

        shared_ptr<int> sp2(new int(5));
        sp = sp2; // 可以赋值
        cout << *sp << " " << *sp2 << endl;
        cout << sp.use_count() << endl; // 2
        cout << sp2.use_count() << endl; // 2

        sp.reset();
        cout << sp.use_count() << endl; // 0
        cout << sp2.use_count() << endl; // 1

        sp.reset(new int(10));
        cout << sp.use_count() << endl; // 1
        cout << sp2.use_count() << endl; // 1
        cout << *sp << endl; // 10
        cout << *sp2 << endl; // 5
    }

    {
        // weak_ptr 基本上没有什么用处，此处略
    }



    cout << "Hello world!\n";

    return 0;
}