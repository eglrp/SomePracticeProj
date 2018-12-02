#include <vector>
#include <string>
#include <iostream>

/*


template< class... Args >
void emplace_back( Args&&... args );

添加新元素到容器尾。元素通过 std::allocator_traits::construct 构造，它典型地用布置 new 于容器所提供的位置原位构造元素。
参数 args... 以 std::forward<Args>(args)... 转发到构造函数。

 */

struct President {
    std::string name;
    std::string country;
    int year;

    President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year) {
        std::cout << "I am being constructed.\n";
    }
    President(President &&other)
        : name(std::move(other.name)), country(std::move(other.country)), year(other.year) {
        std::cout << "I am being moved.\n";
    }
    President &operator=(const President &other) = default;
};

int main() {
    std::vector<President> elections;
    std::cout << "emplace_back:\n";
    elections.emplace_back("Nelson Mandela", "South Africa", 1994);

    std::vector<President> reElections;
    std::cout << "\npush_back:\n";
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

    std::cout << "\nContents:\n";
    for (President const &president : elections) {
        std::cout << president.name << " was elected president of "
                  << president.country << " in " << president.year << ".\n";
    }
    for (President const &president : reElections) {
        std::cout << president.name << " was re-elected president of "
                  << president.country << " in " << president.year << ".\n";
    }
}