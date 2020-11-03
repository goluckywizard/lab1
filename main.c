#include <iostream>
#include <string>
#include <bitset>
#include <vector>
/*class Trit{

};*/
enum Trit{False = 1, Unknown = 2, True = 3};
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
        if (str[i] == True)
        {
            ins_vec |= 0b11;
        } else
        if (str[i] == False)
        {
            ins_vec |= 0b00;
        } else
        {
            ins_vec |= 0b10;
        }
        //std::cout << ins_vec << " ";
        if (new_uint == sizeof(unsigned int) * 8)
        {
            //std::cout << "kuk" << new_uint;
            forTrits.push_back(ins_vec);
            new_uint = 0;
            ins_vec = 0;
            continue;
        }
        ins_vec <<= 2;
        new_uint += 2;
    }
    while (new_uint != 0)
    {
        ins_vec |= 0b10;
        if (new_uint == sizeof(unsigned int) * 8 - 2)
        {
            forTrits.push_back(ins_vec);
            break;
        }
        ins_vec <<= 2;
        new_uint += 2;

    }
}
    size_t capacity()
    {
        return forTrits.size();
    }
    int operator[](const size_t number){
        unsigned int comp = forTrits[forTrits.size() - number * 2 / 8 / sizeof(unsigned int) - 1];
        //std::cout << comp << " ";
        comp >>= (sizeof(unsigned int) * 8 - ((number * 2) % (sizeof(unsigned int) * 8))) - 2;
        //std::cout << comp << " ";
        comp &= 0b11;
        //std::cout << comp << " ";
        if (comp == 3)
            return True;
        if (comp == 0)
            return False;
        return Unknown;
    }
    /*Tritset&operator[](const size_t number){
            return
        };*/
};

//using namespace std;

int main() {
    Tritset set(3, "TFT");
    //std::cout << std::endl;
    for (int i = 0; i < 16; ++i)
        std:: cout << set[i]  << " ";
    //std::cout << set.capacity() << sizeof(unsigned int);
    return 0;
}
