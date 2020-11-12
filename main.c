#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include "classes.h"
#include <cassert>
/*class Tritset_proxy {
private:
    size_t max_trits;
    unsigned int Tritnumber;
    int value = Unknown;
    std::vector<unsigned int> &trits;
public:/*/
Tritset_proxy::Tritset_proxy(size_t number, std::vector<unsigned int> &Trits) : trits(Trits) {
        max_trits = number;
        Tritnumber = number % (sizeof(unsigned int) * 4);
        if (max_trits + 1 <= trits.size() * (sizeof(unsigned int) * 4))
        {
            unsigned int  &Tritcontainer = (Trits[number / (sizeof(unsigned int) * 4)]);
            value = ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b11 ? True : \
                ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b00 ? False : Unknown;
        }
    }

void Tritset_proxy::add (size_t amount) {
    for (size_t i = 0; i < amount; ++i){
        int new_uint = 2;
        unsigned int ins_vec = 0b10;
        while (new_uint != 0)
        {
            ins_vec |= 0b10;
            if (new_uint == sizeof(unsigned int) * 8)
            {
                trits.push_back(ins_vec);
                break;
            }
            ins_vec <<= 2;
            new_uint += 2;
        }
    }
}

void Tritset_proxy::operator = (int new_value) {
    if (max_trits + 1 <= trits.size() * (sizeof(unsigned int) * 4)) {
        unsigned int  &Tritcontainer = (trits[max_trits / (sizeof(unsigned int) * 4)]);
        if (new_value == True) {
            Tritcontainer = Tritcontainer | (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
        if (new_value == False) {
            //std::cout << Tritcontainer << std::endl;
            Tritcontainer -= Tritcontainer & (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
            //std::cout << Tritcontainer << std::endl;
            //Tritcontainer |= (0b00 << Tritnumber * 2);
        }
        if (new_value == Unknown) {
            Tritcontainer -= Tritcontainer && (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
            Tritcontainer |= (0b10 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
        trits[max_trits / (sizeof(unsigned int) * 4)] = Tritcontainer;
    }
    else{
        if (new_value == True) {
            add((max_trits + 1 - trits.size() * sizeof(unsigned int) * 4) /  (sizeof(unsigned int) * 4));
            if ((max_trits + 1 - trits.size() * sizeof(unsigned int) * 4) % (sizeof(unsigned int) * 4) > 0)
            {
                add(1);
            }
            unsigned int  &Tritcontainer = (trits[max_trits / (sizeof(unsigned int) * 4)]);
            Tritcontainer = Tritcontainer | (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
        if (new_value == False) {
            //std::cout << Tritcontainer << std::endl;
            add((max_trits + 1 - trits.size() * sizeof(unsigned int) * 4) /  (sizeof(unsigned int) * 4));
            if ((max_trits + 1 - trits.size() * sizeof(unsigned int) * 4) % (sizeof(unsigned int) * 4) > 0)
            {
                add(1);
            }
            unsigned int  &Tritcontainer = (trits[max_trits / (sizeof(unsigned int) * 4)]);
            Tritcontainer -= Tritcontainer & (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
            //std::cout << Tritcontainer << std::endl;
            //Tritcontainer |= (0b00 << Tritnumber * 2);
        }
    }
}
 std::ostream &operator << (std::ostream & out, const Tritset_proxy & out_value) {
    //out ;
    return (out << out_value.value);
}
bool Tritset_proxy::operator == (Tritset_proxy &comp) {
    return value == comp.value;
}
bool Tritset_proxy::operator == (Trit comp) {
        return value == comp;
}
Trit Tritset_proxy::operator & (Tritset_proxy &operand) {
    if (value == False || operand.value == False)
        return False;
    else if (value == Unknown || operand.value == Unknown)
        return Unknown;
    else
        return True;
}

Tritset::Tritset(size_t size){
    forTrits.resize(size * 2 / 8 / sizeof(unsigned int) + 1);
}

Tritset::Tritset (size_t size, const std::string& str, char True_symb, char False_symp){
    //forTrits.resize(size * 2 / 8 / sizeof(unsigned int) + 1);
    int new_uint = 0;
    unsigned int ins_vec = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == True_symb)
        {
            ins_vec |= 0b11;
        } else
        if (str[i] == False_symp)
        {
            ins_vec |= 0b00;
        } else
        {
            ins_vec |= 0b10;
        }
        //std::cout << ins_vec << " ";
        if (new_uint == sizeof(unsigned int) * 8)
        {
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

size_t Tritset::capacity(){
    return forTrits.size();
}


Tritset_proxy Tritset::operator[](const size_t number) {
    return Tritset_proxy(number, forTrits);
}

Tritset& Tritset::operator& (Tritset &operand)
{
    size_t max = operand.capacity() * sizeof(unsigned int) * 4 > forTrits.size() * sizeof(unsigned int) * 4 ? \
                operand.capacity() * sizeof(unsigned int) * 4 : forTrits.size() * sizeof(unsigned int) * 4;
    Tritset k(max);
    Tritset &a = k;
    for (size_t i = 0; i < max; ++i)
    {
        Tritset_proxy first = operand[i];
        Tritset_proxy second = Tritset_proxy(i, forTrits);
        a[i] = (first & second);
    }
    return k;
}

int main() {
    Tritset set(3, "TFTUF");
    //std::cout << std::endl;
    //std::cout << set[0] << set[1] << std::endl;
    //set[45] = Unknown;
    assert(set[1000000] == Unknown);
    for (unsigned int i = 0; i < set.capacity() * sizeof(unsigned int) * 8 / 2; ++i)
        std::cout << i % 10 << " ";
    std::cout << std::endl;
    for (unsigned int i = 0; i < set.capacity() * sizeof(unsigned int) * 8 / 2; ++i)
        std:: cout  << set[i]  << " ";
    std::cout << std::endl << set.capacity() << " " << sizeof(unsigned int) * 8 / 2;
    return 0;
}
