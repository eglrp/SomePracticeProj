/*
 * Author: Neverland_LY
 * Date: 2018-11-17
 * ProjectName: weak_ptr
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

class Dog {
    //shared_ptr<Dog> m_pFriend;  // cyclic reference
    weak_ptr<Dog> m_pFriend; // equal to Dog * ptr;
public:
    string m_name;
    void bark() {
        cout << "Dog " << m_name << " rules!" << endl;
    }
    Dog(string name) {
        cout << "Dog is created: " << name << endl;
        m_name = name;
    }
    ~Dog() {
        cout << "dog is destroyed: " << m_name << endl;
    }
    void makeFriend(shared_ptr<Dog> f) {
        m_pFriend = f;
    }
    void showFriend() { //cout << "My friend is: " << m_pFriend.lock()->m_name << endl;
        if (!m_pFriend.expired())
            // cout << "My friend is: " << m_pFriend->m_name << endl;
            cout << "My friend is: " << m_pFriend.lock()->m_name << endl;
        cout << " He is owned by " << m_pFriend.use_count() << " pointers." << endl;
    }
};

int main(int argc, char *argv[]) {

    {
        shared_ptr<Dog> pD(new Dog("Gunner"));
        shared_ptr<Dog> pD2(new Dog("Smokey"));
        pD->makeFriend(pD2);
        pD2->makeFriend(pD);

        pD->showFriend();
    }


    cout << "Hello world!\n";

    return 0;
}