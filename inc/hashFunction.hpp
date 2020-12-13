#include <stddef.h>
#include <tuple>

struct MyKey
{
    std::size_t first, last;

    MyKey(std::size_t f, std::size_t l) : first(f), last(l) {}

    bool operator==(const MyKey &p) const
    {
        return first == p.first && last == p.last;
    }
};

class MyHashFunction
{
public:
    /* Pairing function 
    https://en.wikipedia.org/wiki/Pairing_function
    */
    size_t operator()(const MyKey &p) const
    {
        return 0.5 * (p.first + p.last) * (p.first + p.last + 1) + p.last;
    }
};