#ifndef LAB1_CLASSES_H
#define LAB1_CLASSES_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "gtest/gtest.h"
enum Trit{False = 1, Unknown = 2, True = 3};
class Tritset;
class Tritset_proxy {
private:
    size_t max_trits;
    unsigned int Tritnumber;
    int value = Unknown;
    Tritset *base_set;
    std::vector<unsigned int> &trits;
    friend void size_change(size_t new_size, Tritset *base);
public:
    Tritset_proxy(size_t number, std::vector<unsigned int> &Trits, Tritset * base);
    void operator = (Trit new_value);
    friend std::ostream & operator << (std::ostream & out, const Tritset_proxy & out_value);
    bool operator == (Tritset_proxy &comp);
    bool operator == (Trit comp);
    Trit operator &(Tritset_proxy &operand);
    Trit operator |(Tritset_proxy &operand);
    Trit operator !();
};

class Tritset {
private:
    std::vector<unsigned int> forTrits;
    size_t set_size;
    size_t start_size;
    void add (size_t amount);
    friend void size_change(size_t new_size, Tritset *base);
public:
    Tritset(size_t size);
    Tritset (size_t size, const std::string& str, char True = 'T', char False = 'F');
    size_t capacity();
    Tritset_proxy operator[](size_t number);
    size_t length ();
    size_t cardinality(Trit value);
    std::unordered_map<Trit, int, std::hash<int>> cardinality();
    void operator = (Tritset *operand);
    Tritset * operator & (Tritset &operand);
    Tritset * operator | (Tritset &operand);
    Tritset * operator!();
    void trim (size_t lastIndex);
    void shrink();
};
int testes();
#endif //LAB1_CLASSES_H
