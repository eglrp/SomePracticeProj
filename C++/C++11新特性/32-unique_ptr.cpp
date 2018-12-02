/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: unique_ptr
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

// Unique Pointers: exclusive owenership

class Bone {

};

class Dog {
    //Bone* pB;
    //unique_ptr<Bone> pB;  // This prevents memory leak even constructor fails.
public:
    string m_name;
    void bark() {
        cout << "Dog " << m_name << " rules!" << endl;
    }
    Dog() {
        /*pB = new Bone();*/ //假如刚构造完就发生了异常，那么会造成泄露，所以用 unique_ptr
        cout << "Nameless dog created." << endl;
        m_name = "nameless";
    }
    Dog(string name) {
        cout << "Dog is created: " << name << endl;
        m_name = name;
    }
    ~Dog() {
        /*delete pB;*/
        cout << "dog is destroyed: " << m_name << endl;
    }
};

void f(unique_ptr<Dog> p) {
    p->bark();
}

unique_ptr<Dog> getDog() {
    unique_ptr<Dog> p(new Dog("Smokey"));
    return p; // p 不再拥有所有权，而是交给了接收者
}

int main(int argc, char *argv[]) {

    {
        Dog *pD = new Dog("Gunner");
        pD->bark();
        // 比较危险的操作，一旦中途么的或者跑出异常，没来得及delete导致内存泄露
        delete pD;
    }

    cout << "----------------\n";

    {
        unique_ptr<Dog> pD(new Dog("Gunner"));
        pD->bark();
    }

    cout << "----------------\n";

    {
        unique_ptr<Dog> pD(new Dog("Gunner"));
        Dog *d = pD.release();  // pD 不再拥有所有权，但是pD 还存在
        if(!pD)
            cout << "pD is empty!\n";
        delete d;
    }

    cout << "----------------\n";

    {
        unique_ptr<Dog> pD(new Dog("Gunner"));
        pD.reset(new Dog("Tank"));  // gunner deleted
        if(!pD)
            cout << "pD is empty!\n";
        else
            cout << "pD is not empty!\n";
    }

    cout << "----------------\n";

    {
        unique_ptr<Dog> pD(new Dog("Gunner"));
        pD.reset();  // equal to pD = nullptr  ，gunner deleted
        if(!pD)
            cout << "pD is empty!\n";
        else
            cout << "pD is not empty!\n";
    }

    cout << "----------------\n";

    {
        // 不同的unique_pte 不能在同一时间指向同一个物体
        unique_ptr<Dog> p1(new Dog("Gunner"));
        unique_ptr<Dog> p2(new Dog("Tank"));

        p2->bark();
        //但是换一个时间就可以
        p2 = std::move(p1);
        // 发生了三件事情
        // 1、Tank destroyed
        // 2、p1 变成 empty
        // p2 拥有 gunner
        p2->bark();

    }

    cout << "----------------\n";

    {
        unique_ptr<Dog> p1(new Dog("Gunner"));
        f(std::move(p1)); // p1 destroyed in f funcrion, not in the local
        // 此时 gunner 的所有权不再是 p1 的，而是转移给了f函数的参数p
        if(!p1)
            cout << "p1 is empty!\n";
    }

    cout << "----------------\n";

    {
        unique_ptr<Dog> p = getDog(); // 此时 p 拥有的所有权
        // 出了作用域后，destroyed
    }

    cout << "----------------\n";

    {
        // shared_ptr<Dog> p3(new Dog[3]); // when out of scope, dog[1] and dog[2] have memory leaks
        shared_ptr<Dog> p1(new Dog[3], [](Dog * dog) {
            delete[] dog; // all three dogs will be deleted when out of scope
        });

        // difference
        unique_ptr<Dog[]> p2(new Dog[3]);
    }


    cout << "Hello world!\n";

    return 0;
}