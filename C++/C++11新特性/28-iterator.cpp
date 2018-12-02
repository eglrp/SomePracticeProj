#include <iostream>
#include <string>
#include <map>

using namespace std;

// 创建自己的迭代器
class IntVector;

class Iter {
public:
    Iter(const IntVector *p_vec, int pos)
        : _pos(pos), _p_vec(p_vec) {}

    bool operator!=(const Iter &other) const {
        return _pos != other._pos;
    }

    int operator*() const;

    const Iter &operator++() {
        ++_pos;
        return *this;
    }

private:
    int _pos;
    const IntVector *_p_vec;
};


class IntVector {
public:
    IntVector() {}

    int get(int col) const {
        return _data[col];
    }

    Iter begin() const {
        return Iter(this, 0);
    }

    Iter end() const {
        return Iter(this, 100);
    }

    void set(int index, int val) {
        _data[index] = val;
    }

private:
    int _data[100];
};

int Iter::operator*() const {
    return _p_vec->get(_pos);
}

int main(int argc, char const *argv[]) {
    map<string, string> address_book;
    address_book["1"] = "11";
    address_book["2"] = "22";
    for(auto address_entry : address_book) {
        // cout << address_entry.first << "---" << address_entry.second << endl;
    }

    IntVector iv;
    for(int i = 0; i < 100; ++i ) {
        iv.set(i, i);
    }

    for(int i : iv) {
        cout << i << endl;
    }

    cout << "hello world!\b";

    return 0;
}