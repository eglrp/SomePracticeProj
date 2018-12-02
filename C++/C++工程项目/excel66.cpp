#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {
    ofstream ofs("123.csv");
    for(int i = 0; i < 21; i++)
        for(int j = 0; j < 50; j++)
            ofs << to_string(i + 1) << endl;
    ofs.close();
    return 0;
}