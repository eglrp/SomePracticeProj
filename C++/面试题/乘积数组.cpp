/*
给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],
其中B中的元素B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]。
不能使用除法。
 */

#include <iostream>
#include <vector>

using namespace std;

//B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]
//从左到右算 B[i]=A[0]*A[1]*...*A[i-1]
//从右到左算B[i]*=A[i+1]*...*A[n-1]
//正好互补，经典
vector<int> multiply1(const vector<int> &A) {

    int n = A.size();
    vector<int> b(n);
    int ret = 1;
    for(int i = 0; i < n; ret *= A[i++]) {
        b[i] = ret;
    }
    ret = 1;
    for(int i = n - 1; i >= 0; ret *= A[i--]) {
        b[i] *= ret;
    }
    return b;
}

int main(int argc, char const *argv[]) {
    /* code */

    return 0;
}