#include <iostream>

using namespace std;

class Person {
public:
    enum PersonType {ADULT, CHIlD, SENIOR};
    void setPersonType(PersonType type);
    PersonType getPersonType();

private:
    PersonType person_type_;
};

void Person::setPersonType(PersonType type){
    person_type_ = type;
}

// error: 'PersonType' does not name a type
//PersonType Person::getPersonType(){
// Person::PersonType Person::getPersonType(){
//     return person_type_;
// }

auto Person::getPersonType() -> PersonType{
    return person_type_;
}

int main(int argc, char const *argv[]) {

    return 0;
}