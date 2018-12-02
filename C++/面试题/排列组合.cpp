#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main() {

    // 从n个元素中，任取r个元素的所有组合：
    //  G++[o] BCC5[o] VC7[x]

    const int n = 7;
    const int r = 4; // 0 <= r <= n
    vector<int> p, set;
    p.insert(p.end(), r, 1);
    p.insert(p.end(), n - r, 0);

    for(auto i : p)
        cout << i << " ";
    cout << endl;

    for ( int i = 0; i != p.size(); ++i )
        set.push_back(i + 1);

    int count = 0;
    do {
        for ( int i = 0; i != p.size(); ++i )
            if(p[i])
                cout << set[i] << " ";
        count++;
        cout << "\n";
    } while (prev_permutation( p.begin(), p.end() ));
    cout << "There are " << count << " combinations in total.";

    return 0;
}

/*
permutation  排列
 */