/*
请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。
路径可以从矩阵中的任意一个格子开始，
每一步可以在矩阵中向左，向右，向上，向下移动一个格子。
如果一条路径经过了矩阵中的某一个格子，则之后不能再次进入这个格子。
例如下面的 3 X 4 矩阵中：
| a b c e |
| s f c s |
| a d e e |
该矩阵包含一条字符串"bcced"的路径，但是矩阵中不包含"abcb"路径，
因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，
路径不能再次进入该格子。
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    bool isPath(char *matrix, vector<char> flags, char *str, int x, int y, int rows, int cols) {
        if(x < 0 || x >= rows || y < 0 || y >= cols) //越界的点
            return false;

        if( matrix[x * cols + y] == *str  &&  flags[x * cols + y] == 0 ) {
            flags[x * cols + y] = 1;

            if(*(str + 1) == 0) // 字符串结尾了（最后一个满足的）
                return true;

            bool condition = isPath(matrix, flags, (str + 1), x, y - 1, rows, cols) ||
                             isPath(matrix, flags, (str + 1), x - 1, y, rows, cols) ||
                             isPath(matrix, flags, (str + 1), x, y + 1, rows, cols) ||
                             isPath(matrix, flags, (str + 1), x + 1, y, rows, cols);
            if(condition == false)
                flags[x * cols + y] = 0;
            return condition;
        } else
            return false;
    }
public:
    bool hasPath(char *matrix, int rows, int cols, char *str) {
        vector<char> flags(rows * cols, 0);
        bool condition = false;
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++) {
                condition = (condition || isPath(matrix, flags, str, i, j, rows, cols) );
            }
        return condition;
    }

};

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}