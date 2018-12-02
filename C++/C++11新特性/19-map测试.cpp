/*
 * Author: Neverland_LY
 * Date: 2018-11-16
 * ProjectName: map
 * Version: v-Version
 *
 * Description: https://www.cnblogs.com/fnlingnzb-learner/p/5833051.html
 *              https://blog.csdn.net/libing_zeng/article/details/74011894
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <vector>
#include <map>

using namespace std;

typedef struct tagStudentinfo {
    int niD;
    string strName;
    bool operator < (tagStudentinfo const &_A) const {
        //这个函数指定排序策略，按niD排序，如果niD相等的话，按strName排序
        if(niD < _A.niD)
            return true;
        if(niD == _A.niD)
            return strName.compare(_A.strName) < 0;
        return false;
    }
} Studentinfo, *PStudentinfo; //学生信息


class sort {
public:
    bool operator() (Studentinfo const &_A, Studentinfo const &_B) const {
        if(_A.niD < _B.niD)
            return true;
        if(_A.niD == _B.niD)
            return _A.strName.compare(_B.strName) < 0;
        return false;
    }
};



int main(int argc, char *argv[]) {

    // 用insert函数插入pair数据
    {
        map<int, string> mapStudent;
        mapStudent.insert(pair<int, string>(1, "student_one"));
        mapStudent.insert(pair<int, string>(2, "student_two"));
        mapStudent.insert(pair<int, string>(3, "student_three"));
        map<int, string>::iterator iter;
        for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
            cout << iter->first << ' ' << iter->second << endl;
    }

    // 用insert函数插入value_type数据，下面举例说明
    {
        map<int, string> mapStudent;
        mapStudent.insert(map<int, string>::value_type (1, "student_one"));
        mapStudent.insert(map<int, string>::value_type (2, "student_two"));
        mapStudent.insert(map<int, string>::value_type (3, "student_three"));
        map<int, string>::iterator iter;
        for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
            cout << iter->first << ' ' << iter->second << endl;
    }

    // 用数组方式插入数据
    {
        map<int, string> mapStudent;
        mapStudent[1] = "student_one";
        mapStudent[2] = "student_two";
        mapStudent[3] = "student_three";
        map<int, string>::iterator iter;
        for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
            cout << iter->first << ' ' << iter->second << endl;
    }

    // 数据是否插入成功
    {
        map<int, string> mapStudent;
        pair<map<int, string>::iterator, bool> Insert_Pair;
        Insert_Pair = mapStudent.insert(pair<int, string>(1, "student_one"));

        if(Insert_Pair.second == true)
            cout << "Insert Successfully" << endl;
        else
            cout << "Insert Failure" << endl;

        Insert_Pair = mapStudent.insert(pair<int, string>(1, "student_two"));
        if(Insert_Pair.second == true)
            cout << "Insert Successfully" << endl;
        else
            cout << "Insert Failure" << endl;

        map<int, string>::iterator iter;
        for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
            cout << iter->first << ' ' << iter->second << endl;
    }

    // 用数组插入在数据覆盖上的效果
    {
        map<int, string> mapStudent;
        mapStudent[1] = "student_one";
        mapStudent[2] = "student_two";
        mapStudent[1] = "student_three";
        mapStudent[2] = "student_four";
        map<int, string>::iterator iter;
        cout << "-----------\n";
        for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
            cout << iter->first << ' ' << iter->second << endl;
    }

    // 反向遍历
    {
        map<int, string> mapStudent;
        mapStudent.insert(pair<int, string>(1, "student_one"));
        mapStudent.insert(pair<int, string>(2, "student_two"));
        mapStudent.insert(pair<int, string>(3, "student_three"));
        map<int, string>::reverse_iterator iter;
        for(iter = mapStudent.rbegin(); iter != mapStudent.rend(); iter++)
            cout << iter->first << "  " << iter->second << endl;
    }

    // 简单遍历
    {
        map<int, string> mapStudent;
        mapStudent.insert(pair<int, string>(1, "student_one"));
        mapStudent.insert(pair<int, string>(2, "student_two"));
        mapStudent.insert(pair<int, string>(3, "student_three"));
        int nSize = mapStudent.size();
        //此处应注意，应该是 for(int nindex = 1; nindex <= nSize; nindex++)
        //而不是 for(int nindex = 0; nindex < nSize; nindex++)
        for(int nindex = 1; nindex <= nSize; nindex++)
            cout << mapStudent[nindex] << endl;
    }

    // count 函数
    {
        map<int, string> mapStudent;
        mapStudent.insert(pair<int, string>(1, "student_one"));
        mapStudent.insert(pair<int, string>(2, "student_two"));
        mapStudent.insert(pair<int, string>(3, "student_three"));
        if(mapStudent.count(4) == 1)
            cout << "Find the element!\n";
        else
            cout << "Not find the element!\n";
    }

    // find 函数
    {
        map<int, string> mapStudent;
        mapStudent.insert(pair<int, string>(1, "student_one"));
        mapStudent.insert(pair<int, string>(2, "student_two"));
        mapStudent.insert(pair<int, string>(3, "student_three"));
        map<int, string>::iterator iter;
        iter = mapStudent.find(1);
        if(iter != mapStudent.end())
            cout << "Find, the value is " << iter->second << endl;
        else
            cout << "Do not Find" << endl;
    }

    // lower_bound函数用法，这个函数用来返回要查找关键字的下界(是一个迭代器)
    // upper_bound函数用法，这个函数用来返回要查找关键字的上界(是一个迭代器)
    // 例如：map中已经插入了1，2，3，4的话，如果lower_bound(2)的话，返回的2，
    // 而upper-bound（2）的话，返回的就是3
    {
        cout << "----------\n";
        map<int, string> mapStudent;
        mapStudent[1] = "student_one";
        mapStudent[3] = "student_three";
        mapStudent[5] = "student_five";
        map<int, string>::iterator iter;
        iter = mapStudent.lower_bound(1); //返回的是下界1的迭代器
        cout << iter->second << endl;
        iter = mapStudent.upper_bound(1); //返回的是上界3的迭代器
        cout << iter->second << endl << endl;

        iter = mapStudent.lower_bound(2); //返回的是下界3的迭代器
        cout << iter->second << endl;
        iter = mapStudent.upper_bound(2); //返回的是上界3的迭代器
        cout << iter->second << endl << endl;

        iter = mapStudent.lower_bound(3); //返回的是下界3的迭代器
        cout << iter->second << endl;
        iter = mapStudent.upper_bound(3); //返回的是上界5的迭代器
        cout << iter->second << endl << endl;

        iter = mapStudent.lower_bound(4); //返回的是下界3的迭代器
        cout << iter->second << endl;
        iter = mapStudent.upper_bound(4); //返回的是上界5的迭代器
        cout << iter->second << endl << endl;

        pair<map<int, string>::iterator, map<int, string>::iterator> mappair;
        mappair = mapStudent.equal_range(2);
        if(mappair.first == mappair.second)
            cout << "Do not Find" << endl;
        else
            cout << "Find" << endl;

        mappair = mapStudent.equal_range(3);
        if(mappair.first == mappair.second)
            cout << "Do not Find" << endl;
        else
            cout << "Find" << endl;
    }

    // 删除元素
    {
        map<int, string> mapStudent;
        mapStudent.insert(pair<int, string>(1, "student_one"));
        mapStudent.insert(pair<int, string>(2, "student_two"));
        mapStudent.insert(pair<int, string>(3, "student_three"));
        //如果你要演示输出效果，请选择以下的一种，你看到的效果会比较好
        //如果要删除1,用迭代器删除
        map<int, string>::iterator iter;
        iter = mapStudent.find(1);
        mapStudent.erase(iter);
        //如果要删除1，用关键字删除
        int n = mapStudent.erase(1);//如果删除了会返回1，否则返回0
        //用迭代器，成片的删除
        //一下代码把整个map清空
        mapStudent.erase( mapStudent.begin(), mapStudent.end() );
        //成片删除要注意的是，也是STL的特性，删除区间是一个前闭后开的集合
        //自个加上遍历代码，打印输出吧
    }

    // map中的元素是自动按Key升序排序，所以不能对map用sort函数
    {
        int nSize; //用学生信息映射分数
        map<Studentinfo, int>mapStudent;
        map<Studentinfo, int>::iterator iter;
        Studentinfo studentinfo;
        studentinfo.niD = 1;
        studentinfo.strName = "student_one";
        mapStudent.insert(pair<Studentinfo, int>(studentinfo, 90));
        studentinfo.niD = 2;
        studentinfo.strName = "student_two";
        mapStudent.insert(pair<Studentinfo, int>(studentinfo, 80));
        for (iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
            cout << iter->first.niD << ' ' << iter->first.strName << ' ' << iter->second << endl;
    }

    // 仿函数排序
    {
        //用学生信息映射分数
        map<Studentinfo, int, sort>mapStudent; // 重点在这里
        map<Studentinfo, int>::iterator iter;
        Studentinfo studentinfo;
        studentinfo.niD = 1;
        studentinfo.strName = "student_one";
        mapStudent.insert(pair<Studentinfo, int>(studentinfo, 90));
        studentinfo.niD = 2;
        studentinfo.strName = "student_two";
        mapStudent.insert(pair<Studentinfo, int>(studentinfo, 80));
        for (iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
            cout << iter->first.niD << ' ' << iter->first.strName << ' ' << iter->second << endl;
    }

    cout << "Hello world!\n";

    return 0;
}
