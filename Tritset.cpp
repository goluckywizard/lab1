#include "Tritset.h"
Tritset_proxy::Tritset_proxy(size_t number, Tritset &base) : base_set(base) {
    max_trits = number;
    //base_set = base.set_size;
    Tritnumber = number % (sizeof(unsigned int) * 4);
    if (max_trits + 1 <= base_set.forTrits.size() * (sizeof(unsigned int) * 4))
    {
        unsigned int Tritcontainer = (base_set.forTrits[max_trits / (sizeof(unsigned int) * 4)]);
        value = ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b11 ? True : \
            ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b00 ? False : Unknown;
    }
}

void Tritset_proxy::operator = (Trit new_value) {
    if (max_trits + 1 <= base_set.forTrits.size() * (sizeof(unsigned int) * 4)) {
        unsigned int &Tritcontainer = (base_set.forTrits[max_trits / (sizeof(unsigned int) * 4)]);
        if (new_value == True) {
            Tritcontainer |= (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
        if (new_value == False) {
            Tritcontainer -= Tritcontainer & (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
        if (new_value == Unknown) {
            Tritcontainer -= Tritcontainer & (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
            Tritcontainer += (0b10 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
        //base_set.forTrits[max_trits / (sizeof(unsigned int) * 4)] = Tritcontainer;

    }
    else {
        unsigned int Tritcontainer;
        if (new_value == True) {
            size_change(max_trits + 1, base_set);
            Tritcontainer = (base_set.forTrits[max_trits / (sizeof(unsigned int) * 4)]);
            Tritcontainer |= (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
        if (new_value == False) {
            size_change(max_trits + 1, base_set);
            Tritcontainer = (base_set.forTrits[max_trits / (sizeof(unsigned int) * 4)]);
            Tritcontainer -= Tritcontainer & (0b11 << (sizeof(unsigned int) * 8 - Tritnumber * 2 - 2));
        }
        if (new_value != Unknown)
            base_set.forTrits[max_trits / (sizeof(unsigned int) * 4)] = Tritcontainer;
    }
}
std::ostream &operator << (std::ostream & out, const Tritset_proxy & out_value) {
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
    start_size = size;
    set_size = size;
    size_t count = size * 2 / 8 / sizeof(unsigned int);
    if (size % (sizeof(unsigned int) * 4) > 0)
        count++;
    for (size_t i = 0; i < count; ++i){
        int new_uint = 2;
        unsigned int ins_vec = 0b10;
        while (new_uint != 0)
        {
            ins_vec |= 0b10;
            if (new_uint == sizeof(unsigned int) * 8)
            {
                forTrits.push_back(ins_vec);
                break;
            }
            ins_vec *= 4;
            new_uint += 2;
        }
    }
}

Tritset::Tritset (size_t size, const std::string& str, char True_symb, char False_symb){
    set_size = size;
    start_size = size;
    int new_uint = 0;
    unsigned int ins_vec = 0;
    size_t already_inserted = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == True_symb)
        {
            ins_vec |= 0b11;
        } else
        if (str[i] == False_symb)
        {
            ins_vec |= 0b00;
        } else
        {
            ins_vec |= 0b10;
        }
        if (new_uint == sizeof(unsigned int) * 8)
        {
            forTrits.push_back(ins_vec);
            new_uint = 0;
            ins_vec = 0;
            ++already_inserted;
            continue;
        }
        ins_vec *= 4;
        new_uint += 2;
    }
    while (new_uint != 0)
    {
        ins_vec += 0b10;
        if (new_uint == sizeof(unsigned int) * 8 - 2)
        {
            ++already_inserted;
            forTrits.push_back(ins_vec);
            break;
        }
        ins_vec *= 4;
        new_uint += 2;
    }
    size_t count = (size - 1) * 2 / 8 / sizeof(unsigned int) + 1 - already_inserted;
    for (size_t i = 0; i < count; ++i) {
        new_uint = 2;
        ins_vec = 0b10;
        while (new_uint != 0)
        {
            ins_vec |= 0b10;
            if (new_uint == sizeof(unsigned int) * 8)
            {
                forTrits.push_back(ins_vec);
                break;
            }
            ins_vec *= 4;
            new_uint += 2;
        }
    }
}
Tritset::Tritset(Tritset *old_set) {
    set_size = old_set->set_size;
    start_size = old_set->start_size;
    forTrits = old_set->forTrits;
}
Tritset::Tritset(Tritset &old_set){
    set_size = old_set.set_size;
    start_size = old_set.start_size;
    forTrits = old_set.forTrits;
}
Tritset::Tritset(Tritset &&old_set) : set_size(old_set.set_size), start_size(old_set.start_size), forTrits(old_set.forTrits){
    old_set.set_size = 0;
    old_set.start_size = 0;
    old_set.forTrits.resize(0);
}
size_t Tritset::capacity(){
    return forTrits.size();
}

void Tritset::add (size_t amount) {
    for (size_t i = 0; i < amount; ++i){
        int new_uint = 2;
        unsigned int ins_vec = 0b10;
        while (new_uint != 0)
        {
            ins_vec |= 0b10;
            if (new_uint == sizeof(unsigned int) * 8)
            {
                forTrits.push_back(ins_vec);
                break;
            }
            ins_vec <<= 2;
            new_uint += 2;
        }
    }
}

Tritset_proxy Tritset::operator[](const size_t number) {
    return Tritset_proxy(number, *this);
}

size_t Tritset::length() {
    size_t count = forTrits.size() * sizeof(unsigned int) * 4 - 1;
    //std::cout << forTrits.size() << " ";
    unsigned int number = count % (sizeof(unsigned int) * 4);
    unsigned int  Tritcontainer = (forTrits[forTrits.size() - 1]);
    unsigned int comparable_var = ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b11 ? True : \
                ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b00 ? False : Unknown;
    while (comparable_var == Unknown && count > 0) {
        --count;
        number = count % (sizeof(unsigned int) * 4);
        Tritcontainer = (forTrits[count / (sizeof(unsigned int) * 4)]);
        comparable_var = ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b11 ? True : \
                ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b00 ? False : Unknown;
    }
    if (count == 0 && comparable_var == Unknown)
        return 0;
    return count + 1;
}

size_t Tritset::cardinality(Trit value) {
    size_t count = 0;
    for (size_t i = 0; i < this->length(); ++i)
    {
        unsigned int number = i % (sizeof(unsigned int) * 4);
        unsigned int  Tritcontainer = (forTrits[i / (sizeof(unsigned int) * 4)]);
        unsigned int comparable_var = ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b11 ? \
        True : ((Tritcontainer >> (sizeof(unsigned int) * 8 - number * 2 - 2)) & 0b11) == 0b00 ? False : Unknown;
        if (comparable_var == value)
            count++;
    }
    return count;
}

std::unordered_map<Trit, int, std::hash<int>> Tritset::cardinality() {
    std::unordered_map<Trit, int, std::hash<int>> first;
    first[True] = cardinality(True);
    first[Unknown] = cardinality(Unknown);
    first[False] = cardinality(False);
    return first;
}

void Tritset::operator = (Tritset *operand) {
    forTrits = operand->forTrits;
    set_size = operand->set_size;
    start_size = operand->start_size;
    delete[](operand);
}

Tritset * Tritset::operator& (Tritset &operand) {
    size_t max = __max(set_size, operand.set_size);
    Tritset *a = new Tritset[1] {max};
    for (size_t i = 0; i < max; ++i)
    {
        Tritset_proxy first = operand[i];
        Tritset_proxy second = Tritset_proxy(i, *this);
        (*a)[i] = (first & second);
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
        Tritset_proxy second = Tritset_proxy(i, *this);
        (*a)[i] = (first | second);
    }
    return a;
}
Tritset* Tritset::operator!() {
    Tritset *a = new Tritset[1] {forTrits.size() * sizeof(unsigned int) * 4};
    for (size_t i = 0; i < forTrits.size() * sizeof(unsigned int) * 4; ++i)
    {
        Tritset_proxy first = Tritset_proxy(i, *this);
        (*a)[i] = (!first);
    }
    return a;
}
void size_change(size_t new_size, Tritset &base) {
    size_t count = new_size / (sizeof(unsigned int) * 4);
    if (new_size % (sizeof(unsigned int) * 4) > 0)
    {
        count++;
    }
    if (new_size > (base.set_size))
    {
        base.set_size = new_size;
        base.add(count - base.capacity());
    }
    else
    {
        base.set_size = new_size;
        base.forTrits.resize(count);
    }
}
void Tritset::trim (size_t lastIndex) {
    if (lastIndex < set_size)
    {
        size_change(lastIndex, *this);
        for (size_t i = lastIndex; i < lastIndex - (lastIndex % (sizeof(unsigned int) * 4)) + sizeof(unsigned int) * 4; ++i) {
            (*this)[i] = Unknown;
        }
    }
}
void Tritset::shrink() {
    if (length() > start_size)
    {
        trim(length());
    }
    else
        trim(start_size);
}
