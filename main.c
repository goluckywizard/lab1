#include <iostream>
#include <string>
#include <bitset>
#include <vector>
/*class Trit{

};*/
enum Trit{False, Unknown, True};
class Tritset {
private:
    std::vector<unsigned int> forTrits;
public: Tritset(size_t size){
    forTrits.resize(size * 2 / 8 / sizeof(unsigned int) + 1);
}
public: Tritset (size_t size, const std::string& str, char True = 'T', char Unknown = 'U', char False = 'F'){
    //forTrits.resize(size * 2 / 8 / sizeof(unsigned int) + 1);
    int new_uint = 0;
    unsigned int ins_vec = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (new_uint == sizeof(unsigned int))
        {
            forTrits.push_back(ins_vec);
            new_uint = 0;
            ins_vec = 0;
        }
        if (str[i] == True)
        {
            ins_vec |= 0b11;
        }
        if (str[i] == Unknown)
        {
            ins_vec |= 0b10;
        }
        if (str[i] == False)
        {
            ins_vec |= 0b00;
        }
        ins_vec <<= 2;
        new_uint += 2;
    }
    while (new_uint != 0)
    {
        ins_vec |= 0b10;
        ins_vec <<= 2;
        new_uint += 2;
        if (new_uint == sizeof(unsigned int))
        {
            forTrits.push_back(ins_vec);
            new_uint = 0;
            ins_vec = 0;
        }
    }
}
    size_t capacity()
    {
        return forTrits.size();
    }
    int&operator[](const size_t number){

        }
    Tritset&operator[](const size_t number){
            return
        };
};

//using namespace std;

int main() {
    Tritset set(500);
    set[0] = False;
    std::cout << set.capacity();
    return 0;
}
