/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: shared_ptr
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

/*********** Shared_ptr ***********/

// 1. When a pointer outlives pointee: dangling pointer
// 2. When a pointee outlives all its pointers: resource leak
//
// Smart Pointers: Make sure the lifetime of a pointer and pointee match.

class Dog {
    string m_name;
public:
    void bark() {
        cout << "Dog " << m_name << " rules!" << endl;
    }
    Dog(string name) {
        cout << "Dog is created: " << name << endl;
        m_name = name;
    }
    Dog() {
        cout << "Nameless dog created." << endl;
        m_name = "nameless";
    }
    ~Dog() {
        cout << "dog is destroyed: " << m_name << endl;
    }
    //void enter(DogHouse* h) { h->setDog(shared_from_this()); }  // Dont's call shared_from_this() in constructor
};

void foo() {
    shared_ptr<Dog> p(new Dog("GUnner")); // count == 1
    // 1.Gunner is created
    // 2. P is created
    // 注意，这可能是个危险的操作，因为可能存在这种情况，gunner 创建成功，但是 P 没有成功，
    // 那么的话，没人负责销毁gunner，造成内存泄露

    {
        shared_ptr<Dog> p2(new Dog("Tank")); // count == 2
        p2->bark(); cout << p.use_count(); // count == 2
    }
    //count == 1
    p->bark();
} // count == 0

int main(int argc, char *argv[]) {

    {
        // Dog * dog = new Dog("Tom");
        // shared_ptr<Dog> p1(dog); // count == 1
        // shared_ptr<Dog> p2(dog); // count == 1
    } // Memory leak(p2 is deleted first)

    {
        Dog *d = new Dog("Tank");
        shared_ptr<Dog> p = make_shared<Dog>("Tank"); // faster and safer(exception safe)
        (*p).bark();
        //static_pointer_cast
        //dynamic_pointer_cast
        //const_pointer_cast
    }

    {
        shared_ptr<Dog> p1 = shared_ptr<Dog>(new Dog("Gunner"));
        shared_ptr<Dog> p2 = shared_ptr<Dog>(new Dog("Tank"));

        // 以下三种方法都会使得 gunner deleted
        //p1 = p2; // Gunner is deleted
        //p1 = nullptr; // Gunner is deleted
        //p1.reset(); // Gunner is deleted

    }

    {
        cout << "-------\n";
        shared_ptr<Dog> p1 = make_shared<Dog>("Gunner"); // default deleter is operator delete.
        shared_ptr<Dog> p2( new Dog("Victor"),
        [](Dog * p) {
            cout << "deleting a dog.\n";
            delete p;
        }); // custome deleter

        // shared_ptr<Dog> p3(new Dog[3]); // when out of scope, dog[1] and dog[2] have memory leaks
        shared_ptr<Dog> p4(new Dog[3], [](Dog * dog) {
            delete[] dog; // all three dogs will be deleted when out of scope
        });
    }

    {
        shared_ptr<Dog> p1(new Dog("Gunner"));
        Dog *d = p1.get();  // returns the raw pointer

        // delete p1; // error
        // shared_ptr<Dog> p2(d); // error
        //
        //
        // dogHouse.seveDog(); // dangling pointer
    }

    {
        // shared_ptr<Dog> pD(new Dog("Gunner"));
        // shared_ptr<Dog> pD = make_shared<Dog>(new Dog("Gunner")); // faster and safer
        // pD->bark();
        // (*pD).bark();
    }

    cout << "Hello world!\n";

    return 0;
}