//
// Created by sasha on 13.11.2020.
//

#ifndef LAB1_CLASSES_H
#define LAB1_CLASSES_H
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
enum Trit{False = 1, Unknown = 2, True = 3};
class Tritset_proxy {
private:
    size_t max_trits;
    unsigned int Tritnumber;
    int value = Unknown;
    //unsigned int Tritcontainer;
    std::vector<unsigned int> &trits;
public:
    Tritset_proxy(size_t number, std::vector<unsigned int> &Trits);

    void add (size_t amount);

    void operator = (int new_value);
    friend std::ostream & operator << (std::ostream & out, const Tritset_proxy & out_value);
    bool operator == (Tritset_proxy &comp);
    bool operator == (Trit comp);
    Trit operator &(Tritset_proxy &operand);
};

class Tritset {
private:
    std::vector<unsigned int> forTrits;
public:
    Tritset(size_t size);
public:
    Tritset (size_t size, const std::string& str, char True = 'T', char False = 'F');
    size_t capacity();
    Tritset_proxy operator[](const size_t number);
    Tritset & operator & (Tritset &operand);
};
#endif //LAB1_CLASSES_H
