#ifndef __CADENA__HPP
#define __CADENA__HPP

#include <cstddef>

class Cadena 
{
    public: 
        inline size_t length() const { return tam_; }
        explicit Cadena(size_t  tam = 0, char relleno = vacia);
    private:
        static char vacia;
        size_t tam_;
        char* s_;
};

#endif //__CADENA__HPP