#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include "classes.h"
#include <cassert>

Tritset_proxy::Tritset_proxy(size_t number, std::vector<unsigned int> &Trits) : trits(Trits) {
        max_trits = number;
        Tritnumber = number % (sizeof(unsigned int) * 4);
        if (max_trits + 1 <= trits.size() * (sizeof(unsigned int) * 4))
        {
            unsigned int  &Tritcontainer = (Trits[max_trits / (sizeof(unsigned int) * 4)]);
            value = ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b11 ? True : \
                ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b00 ? False : Unknown;
        }
    }

void Tritset_proxy::add (size_t amount) {
    //std::cout <<"p";
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

void Tritset_proxy::operator = (Trit new_value) {
    if (max_trits + 1 <= trits.size() * (sizeof(unsigned int) * 4)) {
        unsigned int  &Tritcontainer = (trits[max_trits / (sizeof(unsigned int) * 4)]);
        if (new_value == True) {
            Tritcontainer |= (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
            //std::cout << " TC: " << Tritcontainer << " ";
        }
        if (new_value == False) {
            //std::cout << Tritcontainer << std::endl;
            Tritcontainer -= Tritcontainer & (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
            //std::cout << Tritcontainer << std::endl;
            //Tritcontainer |= (0b00 << Tritnumber * 2);
        }
        if (new_value == Unknown) {
            Tritcontainer -= Tritcontainer & (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
            Tritcontainer += (0b10 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
        //std::cout << " Tc: " << (Tritcontainer >> 32 - Tritnumber * 2 - 2) << " ";
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
            Tritcontainer |= (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
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
Trit Tritset_proxy::operator |(Tritset_proxy &operand) {
    if (value == True || operand.value == True)
        return True;
    else if (value == Unknown || operand.value == Unknown)
        return Unknown;
    else
        return False;
}
Trit Tritset_proxy::operator !() {
    if (value == True)
        return False;
    else if (value == Unknown)
        return Unknown;
    else
        return True;
}

Tritset::Tritset(size_t size) {
    size_t count = size * 2 / 8 / sizeof(unsigned int);
    if (size % (sizeof(unsigned int) * 4) > 0)
        ++count;
    forTrits.resize(count);
}

Tritset::Tritset (const std::string& str, char True_symb, char False_symp){
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

size_t Tritset::length() {
    size_t count = forTrits.size() * sizeof(unsigned int) * 4 - 1;
    unsigned int number = count % (sizeof(unsigned int) * 4);
    unsigned int  Tritcontainer = (forTrits[count / (sizeof(unsigned int) * 4)]);
    unsigned int comparable_var = ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b11 ? True : \
                ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b00 ? False : Unknown;
    while (comparable_var == Unknown && count >= 0) {
        --count;
        number = count % (sizeof(unsigned int) * 4);
        Tritcontainer = (forTrits[count / (sizeof(unsigned int) * 4)]);
        comparable_var = ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b11 ? True : \
                ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b00 ? False : Unknown;
    }
    return count + 1;
}

size_t Tritset::cardinality(Trit value) {
    size_t count = 0;
    for (size_t i = 0; i < this->length(); ++i)
    {
        unsigned int number = i % (sizeof(unsigned int) * 4);
        unsigned int  Tritcontainer = (forTrits[i / (sizeof(unsigned int) * 4)]);
        //std::cout << number << " ";
        unsigned int comparable_var = ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b11 ? \
        True : ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b00 ? False : Unknown;
        if (comparable_var == value)
            count++;
        //std::cout << comparable_var << std::endl;
    }
    return count;
}

void Tritset::operator = (Tritset *operand) {
    forTrits = operand->forTrits;
    delete[](operand);
}

Tritset * Tritset::operator& (Tritset &operand) {
    size_t max = operand.capacity() * sizeof(unsigned int) * 4 > forTrits.size() * sizeof(unsigned int) * 4 ? \
                operand.capacity() * sizeof(unsigned int) * 4 : forTrits.size() * sizeof(unsigned int) * 4;

    Tritset *a = new Tritset[1] {max};
    for (size_t i = 0; i < max; ++i)
    {
        Tritset_proxy first = operand[i];
        Tritset_proxy second = Tritset_proxy(i, forTrits);
        //std::cout << first << " " << second << " f&s:" << (first & second);
        (*a)[i] = (first & second);
        //(*a)[i] = Unknown;
        //std::cout << " a[i]:" << (*a)[i] << std::endl;
    }
    return a;
}

Tritset* Tritset::operator | (Tritset &operand) {
    size_t max = operand.capacity() * sizeof(unsigned int) * 4 > forTrits.size() * sizeof(unsigned int) * 4 ? \
                operand.capacity() * sizeof(unsigned int) * 4 : forTrits.size() * sizeof(unsigned int) * 4;

    Tritset *a = new Tritset[1] {max};
    for (size_t i = 0; i < max; ++i)
    {
        Tritset_proxy first = operand[i];
        Tritset_proxy second = Tritset_proxy(i, forTrits);
        (*a)[i] = (first | second);
    }
    return a;
}
Tritset* Tritset::operator!() {
    Tritset *a = new Tritset[1] {forTrits.size() * sizeof(unsigned int) * 4};
    for (size_t i = 0; i < forTrits.size() * sizeof(unsigned int) * 4; ++i)
    {
        Tritset_proxy first = Tritset_proxy(i, forTrits);
        (*a)[i] = (!first);
    }
    return a;
}

int main() {
    Tritset set(16);
    Tritset set1("TFFFTTFU");
    Tritset set2("TFTUUFTF");
    assert(set[1000000] == Unknown);
    set = set1 & set2;
    for (unsigned int i = 0; i < set.capacity() * sizeof(unsigned int) * 8 / 2; ++i)
        std::cout << i % 10 << " ";
    std::cout << std::endl;
    for (unsigned int i = 0; i < set1.capacity() * sizeof(unsigned int) * 8 / 2; ++i)
        std:: cout  << set1[i]  << " ";
    std::cout << std::endl;
    for (unsigned int i = 0; i < set2.capacity() * sizeof(unsigned int) * 8 / 2; ++i)
        std:: cout  << set2[i]  << " ";
    std::cout << std::endl;
    for (unsigned int i = 0; i < set.capacity() * sizeof(unsigned int) * 8 / 2; ++i)
        std:: cout  << set[i]  << " ";
    std::cout << std::endl;
    set = set1 | set2;
    for (unsigned int i = 0; i < set.capacity() * sizeof(unsigned int) * 8 / 2; ++i)
        std:: cout  << set[i]  << " ";
    std::cout << std::endl;
    set = !set2;
    for (unsigned int i = 0; i < set.capacity() * sizeof(unsigned int) * 8 / 2; ++i)
        std:: cout  << set[i]  << " ";
    std::cout << std::endl << set.capacity() << " " << sizeof(unsigned int) * 8 / 2 << " " << set.cardinality(Unknown);
    return 0;
}
