/*
统计一个数字在排序数组中出现的次数。
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int GetNumberOfK(vector<int> data, int k) {
        return biSearch(data, k + 0.5) - biSearch(data, k - 0.5) ;
    }
private:
    int biSearch(const vector<int> &data, double num) {
        int s = 0, e = data.size() - 1;
        while(s <= e) {
            cout << "(s, e) = [ " << s << "," << e << " ]" << endl;
            int mid = (e - s) / 2 + s;
            if(data[mid] < num)
                s = mid + 1;
            else if(data[mid] > num)
                e = mid - 1;
        }
        cout << "(s, e) = [ " << s << "," << e << " ]" << endl;
        return s;
    }
};

int main(int argc, char const *argv[]) {
    //Todo...
    int arr[] = {1, 2, 2, 3, 4, 7, 11, 20, 25};
    vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));
    Solution sln;
    cout << sln.GetNumberOfK(v, 2);

    return 0;
}