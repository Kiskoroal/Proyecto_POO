#include "./cadena.hpp"
#include <stdexcept>
#include <utility>

char Cadena::vacia{'\0'};

//Constructores

Cadena::Cadena(size_t tam, char relleno) : tam_{tam}, s_{tam_ > 0 ? new char[tam_ + 1] : &vacia}
{
    if(tam > 0 && relleno == vacia) {   //En caso de pasar un único parametro cambiamos caracter a rellenar por ' '
        relleno = ' ';
    }

    for(size_t i = 0; i < tam; i++) 
    {
        s_[i] = relleno;
    }

    if(tam > 0) 
        s_[tam] = vacia; //Añadimos caracter terminador '\0'
}

//Constructor de conversión
Cadena::Cadena(const char* cadenaCopia)
{
    if(cadenaCopia != nullptr) {
        size_t n = strlen(cadenaCopia);
        s_ = new char[n+1];
        strcpy(s_, cadenaCopia);
        tam_ = n;
    } else 
    {
        s_ = &vacia;
        tam_ = 0;
    }
}

//Constructor de copia
Cadena::Cadena(const Cadena& A) : tam_{A.tam_}, s_{tam_ > 0 ? new char[tam_ + 1] : &vacia}
{
    if(tam_ > 0) 
    {
        strcpy(s_, A.s_);
    }
}

Cadena::~Cadena() 
{
    if(s_ != &vacia) 
    {
        delete [] s_;
    }
}

Cadena& Cadena::operator =(const Cadena& A) 
{
    Cadena copia(A);

    std::swap(copia.s_, s_);
    std::swap(copia.tam_, tam_);

    return *this;
}

Cadena& Cadena::operator =(const char* A)
{
    Cadena aPartirDeBajoNivel(A);

    *this = aPartirDeBajoNivel;

    return *this;
}

//Métodos propios

Cadena Cadena::substr(size_t indice, size_t desplazamiento) const 
{

    char *subCadena;
    if(indice >= tam_ || desplazamiento > tam_ - indice) 
    {
        throw std::out_of_range("Su subcadena se sale de rango. \n");
    }

    subCadena = new char[desplazamiento+1]; //+1 para caracter terminador
    
    for(size_t i = indice, j = 0; j < desplazamiento; i++, j++) 
    {
            subCadena[j] = s_[i];
    }

    subCadena[desplazamiento] = vacia;

    Cadena m(subCadena);
    delete[] subCadena;
    return m;
}

//Operadores sobrecargados

Cadena& Cadena::operator +=(const Cadena& A) 
{
    size_t nuevo_tam = tam_ + A.tam_;
    char* nuevo = (nuevo_tam > 0) ? new char[nuevo_tam + 1] : &vacia;

    if(nuevo_tam > 0)
    {
        std::strcpy(nuevo, s_);
        std::strcat(nuevo, A.s_);
    }

    if(s_ != &vacia)
        delete[] s_;

    s_ = nuevo;
    tam_ = nuevo_tam;

    return *this;
}

Cadena operator +(const Cadena& A, const Cadena& B) 
{
    Cadena resultado(A);

    return resultado += B;
}

//Operadores logicos

bool operator ==(const Cadena& A, const Cadena& B) 
{ 
    return strcmp((const char*)A, (const char*)B) == 0; 
}
bool operator !=(const Cadena& A, const Cadena& B) 
{ 
    return !(A == B); 
};

bool operator <(const Cadena& A, const Cadena& B)  
{ 
    return strcmp((const char*)A, (const char*)B) < 0; 
}
bool operator >(const Cadena& A, const Cadena& B)  
{ 
    return !(A < B) && (A != B); 
}
bool operator <=(const Cadena& A, const Cadena& B) 
{ 
    return !(A > B); 
}
bool operator >=(const Cadena& A, const Cadena& B) 
{ 
    return !(A < B); 
}