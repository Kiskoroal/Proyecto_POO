#include "./cadena.hpp"

Cadena::Cadena(size_t tam, char relleno) : tam_{tam}, s_{ new char[tam] }
{
    if(tam > 0 && relleno == vacia) {   //En caso de pasar un único parametro cambiamos caracter a rellenar por ' '
        relleno = ' ';
    }

    for(size_t i = 0; i < tam; i++) 
    {
        s_[i] = relleno;
    }
}