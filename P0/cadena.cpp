#include "./cadena.hpp"
#include <stdexcept>

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
Cadena::Cadena(const Cadena& A) : Cadena(A.s_) {}

Cadena::~Cadena() 
{
    if(s_ != &vacia) //Solo eliminamos en caso de haber reservado
    {
        delete [] s_;
    }
}

//Métodos propios

Cadena Cadena::substr(size_t indice, size_t desplazamiento) const 
{

    char *subCadena;
    if(indice >= tam_ || indice + desplazamiento > tam_) 
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