/*
 * Author: Neverland_LY
 * Date: 2018-111-16
 * ProjectName: string
 * Version: v-1.0
 *
 * Description: https://blog.csdn.net/zy2317878/article/details/79056289
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class CLASSNAME {
public:
    CLASSNAME() {}
    ~CLASSNAME() {}
private:

};

int test_string1() {
    {
        std::string s0 ("Initial string");  //根据已有字符串构造新的string实例
        // constructors used in the same order as described above:
        std::string s1;             //构造一个默认为空的string
        std::string s2 (s0);         //通过复制一个string构造一个新的string
        std::string s3 (s0, 8, 3);    //通过复制一个string的一部分来构造一个新的string。8为起始位置，3为偏移量。
        std::string s4 ("A character sequence");  //与s0构造方式相同。
        std::string s5 ("Another character sequence", 12);  //已知字符串，通过截取指定长度来创建一个string
        std::string s6a (10, 'x');  //指定string长度，与一个元素，则默认重复该元素创建string
        std::string s6b (10, 42);      // 42 is the ASCII code for '*'  //通过ASCII码来代替s6a中的指定元素。
        std::string s7 (s0.begin(), s0.begin() + 7); //通过迭代器来指定复制s0的一部分，来创建s7

        std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3;
        std::cout << "\ns4: " << s4 << "\ns5: " << s5 << "\ns6a: " << s6a;
        std::cout << "\ns6b: " << s6b << "\ns7: " << s7 << '\n';
    }

    {
        std::string str1, str2, str3;
        str1 = "Test string: ";   // c-string       //通过=运算符来给已创建的string“赋值”
        str2 = 'x';               // single character
        str3 = str1 + str2;       // string
        //注意这里重载了"+",string类的"+"可以理解为胶水，将两个string类型连接起来了
        std::cout << str3  << '\n';
    }

    {
        std::string str ("Test string");
        for ( std::string::iterator it = str.begin(); it != str.end(); ++it)
            std::cout << *it;
        std::cout << '\n';
    }

    {
        std::string str ("Test string");
        std::cout << "The size of str is " << str.size() << " bytes.\n";
    }

    {
        std::string str ("Test string");
        std::cout << "The size of str is " << str.length() << " bytes.\n";
    }

    {
        std::string str ("Test string");
        std::cout << "size: " << str.size() << "\n";
        std::cout << "length: " << str.length() << "\n";
        std::cout << "capacity: " << str.capacity() << "\n";
        std::cout << "max_size: " << str.max_size() << "\n";
    }

    {
        std::string str ("I like to code in C");
        std::cout << str << '\n';

        unsigned sz = str.size();

        str.resize (sz + 2, '+');
        std::cout << str << '\n';

        str.resize (14);
        std::cout << str << '\n';

        str.clear();
        std::cout << str << '\n';
    }

    {
        std::string str ("Test string");
        for (int i = 0; i < str.length(); ++i) {
            std::cout << str[i];
        }
    }

    {
        std::string str ("Test string");
        for (unsigned i = 0; i < str.length(); ++i) {
            std::cout << str.at(i);
        }
    }

    {
        std::string str ("hello world.");
        str.back() = '!';
        std::cout << str << '\n';
    }

    {
        std::string str ("test string");
        str.front() = 'T';
        std::cout << str << '\n';
    }

    {
        std::string name ("John");
        std::string family ("Smith");
        name += " K. ";         // c-string
        name += family;         // string
        name += '\n';           // character

        std::cout << name;
    }

    {
        std::string str;
        std::string str2 = "Writing ";
        std::string str3 = "print 10 and then 5 more";

        // used in the same order as described above:
        str.append(str2);                       // "Writing "
        str.append(str3, 6, 3);                 // "10 "
        str.append("dots are cool", 5);         // "dots "
        str.append("here: ");                   // "here: "
        str.append(10u, '.');                   // ".........."
        str.append(str3.begin() + 8, str3.end()); // " and then 5 more"
        // str.append<int>(5, 0x2E);               // "....."

        std::cout << str << '\n';
    }

    {
        // string::push_ back
    }

    {
        std::string str;
        std::string base = "The quick brown fox jumps over a lazy dog.";

        // used in the same order as described above:

        str.assign(base);
        std::cout << str << '\n';

        str.assign(base, 10, 9);
        std::cout << str << '\n';         // "brown fox"  //base的第11到第19个字符的内容

        str.assign("pangrams are cool", 7);
        std::cout << str << '\n';         // "pangram"  //一个参数默认从头开始往后数7个字符，没有s

        str.assign("c-string");
        std::cout << str << '\n';         // "c-string"

        str.assign(10, '*');
        std::cout << str << '\n';         // "**********"

        //str.assign<int>(10, 0x2D);
        std::cout << str << '\n';         // "----------"

        str.assign(base.begin() + 16, base.end() - 12);
        std::cout << str << '\n';
    }

    {
        std::string str = "to be question";
        std::string str2 = "the ";
        std::string str3 = "or not to be";
        std::string::iterator it;

        // used in the same order as described above:
        //后面注释中()括号的作用只是帮助显示插入的内容与位置信息。实际string中并没有这对括号
        str.insert(6, str2);                // to be (the )question
        str.insert(6, str3, 3, 4);          // to be (not )the question
        str.insert(10, "that is cool", 8);  // to be not (that is )the question
        str.insert(10, "to be ");           // to be not (to be )that is the question
        str.insert(15, 1, ':');             // to be not to be(:) that is the question
        it = str.insert(str.begin() + 5, ','); // to be(,) not to be: that is the question
        str.insert (str.end(), 3, '.');     // to be, not to be: that is the question(...)
        str.insert (it + 2, str3.begin(), str3.begin() + 3); // (or )

        std::cout << str << '\n';
    }

    {
        std::string str ("This is an example sentence.");
        std::cout << str << '\n';
        //后面注释有两部分，上一行是当前字符串内容，下一行是箭头，表示的意思就是箭头指向内容是处理的内容
        // "This is an example sentence."
        str.erase (10, 8);                       //            ^^^^^^^^
        std::cout << str << '\n';                //消除第11到第19之间的字符。即" example"，注意，有一个空格符
        // "This is an sentence."
        str.erase (str.begin() + 9);             //           ^
        std::cout << str << '\n';                //消除第10个字符，即begin()后9个字符：'n'
        // "This is a sentence."
        str.erase (str.begin() + 5, str.end() - 9); //       ^^^^^
        std::cout << str << '\n';                //消除begin()后5个字符，end()前9个字符。
        // "This sentence."
    }

    {
        std::string base = "this is a test string.";
        std::string str2 = "n example";
        std::string str3 = "sample phrase";
        std::string str4 = "useful.";

        // replace signatures used in the same order as described above:

        // Using positions:                 0123456789*123456789*12345
        std::string str = base;         // "this is a test string."
        //           ^^^^^
        str.replace(9, 5, str2);        // "this is an example string." (1)
        //           ^^^^^^^^^ ^^^^^^
        str.replace(19, 6, str3, 7, 6); // "this is an example phrase." (2)
        //                     ^^^^^^
        str.replace(8, 10, "just a");   // "this is just a phrase."     (3)
        str.replace(8, 6, "a shorty", 7); // "this is a short phrase."    (4)
        str.replace(22, 1, 3, '!');     // "this is a short phrase!!!"  (5)

        // Using iterators:                                               0123456789*123456789*
        str.replace(str.begin(), str.end() - 3, str3);                // "sample phrase!!!"      (1)
        str.replace(str.begin(), str.begin() + 6, "replace");         // "replace phrase!!!"     (3)
        str.replace(str.begin() + 8, str.begin() + 14, "is coolness", 7); // "replace is cool!!!"    (4)
        str.replace(str.begin() + 12, str.end() - 4, 4, 'o');         // "replace is cooool!!!"  (5)
        str.replace(str.begin() + 11, str.end(), str4.begin(), str4.end()); // "replace is useful."    (6)
        std::cout << str << '\n';
    }

    {
        std::string buyer ("money");
        std::string seller ("goods");

        std::cout << "Before the swap, buyer has " << buyer;
        std::cout << " and seller has " << seller << '\n';

        seller.swap (buyer);

        std::cout << " After the swap, buyer has " << buyer;
        std::cout << " and seller has " << seller << '\n';
    }

    {
        std::string str ("hello world!");
        str.pop_back();
        std::cout << str << '\n';
    }

    {
        char buffer[20];
        std::string str ("Test string...");
        std::size_t length = str.copy(buffer, 6, 5);
        buffer[length] = '\0';
        std::cout << "buffer contains: " << buffer << '\n';
        return 0;
    }

    {
        std::string str ("There are two needles in this haystack with needles.");
        std::string str2 ("needle");

        // different member versions of find in the same order as above:
        std::size_t found = str.find(str2);
        if (found != std::string::npos)
            std::cout << "first 'needle' found at: " << found << '\n';

        found = str.find("needles are small", found + 1, 6);
        if (found != std::string::npos)
            std::cout << "second 'needle' found at: " << found << '\n';

        found = str.find("haystack");
        if (found != std::string::npos)
            std::cout << "'haystack' also found at: " << found << '\n';

        found = str.find('.');
        if (found != std::string::npos)
            std::cout << "Period found at: " << found << '\n';

        // let's replace the first needle:
        str.replace(str.find(str2), str2.length(), "preposition");
        std::cout << str << '\n';
    }

    {
        std::string str = "We think in generalities, but we live in details.";
        // (quoting Alfred N. Whitehead)
        std::string str2 = str.substr (3, 5);    // "think"
        std::size_t pos = str.find("live");      // position of "live" in str 返回pos类型size_t
        std::string str3 = str.substr (pos);     // get from "live" to the end
        std::cout << str2 << ' ' << str3 << '\n';
    }

    {
        std::string str1 ("green apple");
        std::string str2 ("red apple");

        if (str1.compare(str2) != 0)         //!=0成立
            std::cout << str1 << " is not " << str2 << '\n';

        if (str1.compare(6, 5, "apple") == 0)     //==0成立
            std::cout << "still, " << str1 << " is an apple\n";

        if (str2.compare(str2.size() - 5, 5, "apple") == 0) //==0成立
            std::cout << "and " << str2 << " is also an apple\n";

        if (str1.compare(6, 5, str2, 4, 5) == 0) //==0成立
            std::cout << "therefore, both are apples\n";
    }


    return 0;
}

void SplitFilename (const std::string &str) {
    std::cout << "Splitting: " << str << '\n';
    std::size_t found = str.find_last_of("/\\");   //在str中搜索与"/\\"中任一个字符匹配的最后一个字符。
    std::cout << " path: " << str.substr(0, found) << '\n';  //pos就是匹配到的位置。0~pos
    std::cout << " file: " << str.substr(found + 1) << '\n'; //pos~string结束
}

int test_string2() {

    {
        std::string str ("Please, replace the vowels in this sentence by asterisks.");
        std::size_t found = str.find_first_of("aeiou");
        //下面的循环实现了找到str中，”aeiou“中所有字符：'a''e''i''o''u'，并将其都替换为'* '
        while (found != std::string::npos) {
            str[found] = '*';
            found = str.find_first_of("aeiou", found + 1);
        }

        std::cout << str << '\n';
    }

    {
        std::string str ("look for non-alphabetic characters...");
        std::size_t found = str.find_first_not_of("abcdefghijklmnopqrstuvwxyz ");

        //下面的代码就是实现找到str中非小写字母的字符，即'-'，并返回'-'的位置。
        if (found != std::string::npos) {
            std::cout << "The first non-alphabetic character is " << str[found];
            std::cout << " at position " << found << '\n';
        }
    }

    {
        std::string str1 ("/usr/bin/man");
        std::string str2 ("c:\\windows\\winhelp.exe");

        SplitFilename (str1);
        SplitFilename (str2);
    }

    {
        std::string name;

        std::cout << "Please, enter your name: ";
        std::cin >> name;
        std::cout << "Hello, " << name << "!\n";
    }

    {
        std::string name;

        std::cout << "Please, enter your full name: ";
        std::getline (std::cin, name);
        std::cout << "Hello, " << name << "!\n";
    }
}


int main(int argc, char *argv[]) {

    // test_string1();
    // test_string2();
    //

    // string path1 = "C:\Program Files (x86)\alipay\aliedit\5.1.0.3754";  // \p提示警告
    string path2 = "C:\\Program Files (x86)\\alipay\\aliedit\\5.1.0.3754";
    string path3 = R"(C:\Program Files (x86)\alipay\aliedit\5.1.0.3754)";
    string path4 = R"(C:\Program "Files" (x86)\\alipay\aliedit\5.1.0.3754)";

    // cout << path1 << endl;
    cout << path2 << endl;
    cout << path3 << endl;
    cout << path4 << endl;

    cout << "Hello world!\n";

    return 0;
}