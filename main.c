#include <iostream>
#include <string>
#include <bitset>
#include <vector>
/*class Trit{

};*/
enum Trit{False = 1, Unknown = 2, True = 3};
class Tritset_proxy {
private: unsigned int *Tritcontainer = nullptr;
public:
    Tritset_proxy(size_t number, std::vector<unsigned int> Trits) {
    if (number / (sizeof(unsigned int) * 4) <= Trits.size())
    {
        Tritcontainer = &(Trits[number / (sizeof(unsigned int) * 4)]);
        max_trits = number;
        Tritnumber = number % (sizeof(unsigned int) * 4);
        value = ((*Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b11 ? True : \
            ((*Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b00 ? False : Unknown;
    }
}
void operator = (int new_value) {
    if (Tritcontainer != nullptr) {
        if (new_value == True) {
            *Tritcontainer = *Tritcontainer | (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
        if (new_value == False) {
            //std::cout << Tritcontainer << std::endl;
            *Tritcontainer -= *Tritcontainer & (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
            //std::cout << Tritcontainer << std::endl;
            //Tritcontainer |= (0b00 << Tritnumber * 2);
        }
        if (new_value == Unknown) {
            *Tritcontainer -= *Tritcontainer && (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
            *Tritcontainer |= (0b10 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
    }
    else
    {
        if (new_value == True) {
            *Tritcontainer = *Tritcontainer | (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
        if (new_value == False) {
            //std::cout << Tritcontainer << std::endl;
            *Tritcontainer -= *Tritcontainer & (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
            //std::cout << Tritcontainer << std::endl;
            //Tritcontainer |= (0b00 << Tritnumber * 2);
        }
        if (new_value == Unknown) {
            *Tritcontainer -= *Tritcontainer && (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
            *Tritcontainer |= (0b10 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
    }
}
friend std::ostream & operator << (std::ostream & out, const Tritset_proxy & out_value) {
    //out ;
    return (out << out_value.value);
}
private:
    size_t max_trits;
    unsigned int Tritnumber;
    int value;
};

class Tritset {
private:
    std::vector<unsigned int> forTrits;

public: Tritset(size_t size){
    forTrits.resize(size * 2 / 8 / sizeof(unsigned int) + 1);
}

public:
    Tritset (size_t size, const std::string& str, char True = 'T', char Unknown = 'U', char False = 'F'){
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

    size_t capacity(){
        return forTrits.size();
    }

    void add (size_t amount) {
        for (size_t i = 0; i < amount; ++i){
            int new_uint = 2;
            unsigned int ins_vec = 0b10;
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
    }

    Tritset_proxy operator[](const size_t number) {
        return Tritset_proxy(number, forTrits);
    }
};
//using namespace std;

int main() {
    Tritset set(3, "TFTUF");
    //std::cout << std::endl;
    //std::cout << set[0] << set[1] << std::endl;
    set[3] = False;
    for (unsigned int i = 0; i < set.capacity() * sizeof(unsigned int) * 8 / 2; ++i)
        std:: cout << set[i]  << " ";
    //std::cout << set.capacity() << sizeof(unsigned int);
    return 0;
}
