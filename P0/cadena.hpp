#ifndef __CADENA__HPP
#define __CADENA__HPP

#include <cstddef>
#include <cstring>
#include <stdexcept>

class Cadena 
{
    public: 
        //Constructores

        explicit Cadena(size_t  tam = 0, char relleno = vacia);
        
        //Constructor a partir de cadena de bajo nivel
        Cadena(const char* cadenaCopia);

        //Constructor de copia
        Cadena(const Cadena& A);
        
        //Observadoras
        inline size_t length() const { return tam_; }

        //Métodos propios
        inline const char& at(size_t indice) const 
        {  
            if(indice >= 0 && indice < tam_) 
            {
                return s_[indice];
            }
            else 
            {
                throw std::out_of_range("Fuera de rango. Rango válido [0, length() - 1]");                
            }
        }

        inline char& at(size_t indice) 
        {  
            if(indice >= 0 && indice < tam_) 
            {
                return s_[indice];
            }
            else 
            {
                throw std::out_of_range("Fuera de rango. Rango válido [0, length() - 1]");                
            }
        }

        Cadena substr(size_t indice, size_t desplazamiento) const;

        //Operadores sobrecargados []
        inline const char& operator [](size_t indice) const { return s_[indice]; }
        inline char& operator [](size_t indice) { return s_[indice]; }

        //Operadores lógicos
        inline friend bool operator ==(const Cadena& A, const Cadena& B) { return strcmp(A.s_, B.s_) == 0; }
        inline friend bool operator !=(const Cadena& A, const Cadena& B) { return !(A == B); };
        inline friend bool operator <(const Cadena& A, const Cadena& B)  { return strcmp(A.s_, B.s_) < 0; }
        inline friend bool operator >(const Cadena& A, const Cadena& B)  { return !(A < B) && (A != B); }
        inline friend bool operator <=(const Cadena& A, const Cadena& B) { return !(A > B); }
        inline friend bool operator >=(const Cadena& A, const Cadena& B) { return !(A < B); }

        ~Cadena();
    private:
        static char vacia;
        size_t tam_;
        char* s_;
};

#endif //__CADENA__HPP