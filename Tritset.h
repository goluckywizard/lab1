#ifndef LAB1_TRITSET_H
#define LAB1_TRITSET_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
//#include <iterator>
enum Trit{False = 1, Unknown = 2, True = 3};
class Tritset;
class Tritset_proxy {
private:
    friend class Tritset;
    size_t max_trits;
    unsigned int Tritnumber;
    int value = Unknown;
    Tritset &base_set;
    friend void size_change(size_t new_size, Tritset &base);
public:
    Tritset_proxy(size_t number, Tritset & base);
    void operator = (Trit new_value);
    void operator = (Tritset_proxy new_trit) {
        max_trits = new_trit.max_trits;
        Tritnumber = new_trit.Tritnumber;
        value = new_trit.value;
        //base_set = new_trit.base_set;
    }
    friend std::ostream & operator << (std::ostream & out, const Tritset_proxy & out_value);
    bool operator == (Tritset_proxy &comp);
    bool operator == (Trit comp);
    bool operator != (Tritset_proxy &comp);
    void operator++ ();
    Tritset_proxy operator*();
    Trit operator &(Tritset_proxy &operand);
    Trit operator |(Tritset_proxy &operand);
    Trit operator !();
};

class Tritset {
    friend class Tritset_proxy;
private:
    std::vector<unsigned int> forTrits;
    size_t set_size;
    size_t start_size;
    void add (size_t amount);
    friend void size_change(size_t new_size, Tritset &base);
public:
    Tritset(size_t size);
    Tritset(Tritset &old_set);
    Tritset(Tritset &&old_set);
    Tritset (const std::string& str, char True = 'T', char False = 'F');
    size_t capacity();
    Tritset_proxy operator[](size_t number);
    size_t length();
    size_t cardinality(Trit value);
    std::unordered_map<Trit, int, std::hash<int>> cardinality();
    void operator = (Tritset &&operand) noexcept;
    Tritset operator & (Tritset operand);
    Tritset operator | (Tritset operand);
    Tritset operator!();
    void trim (size_t lastIndex);
    void shrink();
    Tritset_proxy begin();
    Tritset_proxy end();
};

int testes();
#endif //LAB1_TRITSET_H
