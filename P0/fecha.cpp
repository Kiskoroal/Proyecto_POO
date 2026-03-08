#include <ctime>
#include <cstdio> //Para hacer uso de sscanf
#include <cmath>    //Para hacer uso de log y pow
#include <utility>  //Para usar std::swap
#include "./fecha.hpp"

//Metodos privados

bool Fecha::descomponerFecha(const char* fechaFormateada, int &dia, int &mes , int &año) 
{
            bool correcto = std::sscanf(fechaFormateada, "%d/%d/%d", &dia, &mes, &año) == 3;
            if(correcto && año > 0) 
            {
                int cifras = log10(año) + 1;
                if (cifras > 4) 
                    año /= pow(10, cifras - 4);
            }
            return correcto;
}

void Fecha::validarFecha() const  
{
    if(año_ > Fecha::AñoMaximo || año_ < Fecha::AñoMinimo) 
    {
        throw Fecha::Invalida("Año invalido. \n");
    } 
    else if (mes_ < 1 || mes_ > 12) 
    {   
        throw Fecha::Invalida("Mes invalido. \n");
    }

    std::tm tm = {};

    tm.tm_mday = dia_;
    tm.tm_mon = mes_ - 1;
    tm.tm_year = año_ - 1900;

    std::mktime(&tm); //Normalizamos la fecha tm 

    if(dia_ != tm.tm_mday || mes_ != tm.tm_mon + 1 || año_ != tm.tm_year + 1900) {
        throw Fecha::Invalida("La fecha introducida no existe. \n");
    }
}

//Funciones públicas
Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), año_(a)
{    
    std::time_t tiempo_actual = std::time(nullptr);
    std::tm* tiempo_desglosado = std::localtime(&tiempo_actual);
    if(d == 0) { dia_ = tiempo_desglosado->tm_mday; }
    if(m == 0) { mes_ = tiempo_desglosado->tm_mon + 1; }
    if(a == 0) { año_ = tiempo_desglosado->tm_year + 1900; }
    validarFecha();
}

//Constructor de copia
Fecha::Fecha(const Fecha& A) : Fecha(A.dia_, A.mes_, A.año_) {}

//Constructor de conversión de cadena de bajo nivel (dd/mm/aa)
Fecha::Fecha(const char* fecha) 
{
    int d, m, a;

    if(!descomponerFecha(fecha, d, m, a)) 
    {
        throw Fecha::Invalida("No se ha pasado el formato correcto de cadena. \n");
    }

    Fecha fechaNueva(d, m, a);

    dia_ = fechaNueva.dia();
    mes_ = fechaNueva.mes();
    año_ = fechaNueva.año();
}

//Operador de asignación

Fecha& Fecha::operator =(const Fecha& A) 
{
    Fecha copia(A);

    std::swap(dia_, copia.dia_);
    std::swap(mes_, copia.mes_);
    std::swap(año_, copia.año_);

    return *this;
}

bool operator ==(const Fecha& A, const Fecha& B) 
{
    return (A.dia_ == B.dia_) && (A.mes_ == B.mes_) && (A.año_ == B.año_);
}

bool operator >(const Fecha& A, const Fecha& B) 
{
    if(A.año_ != B.año_) 
    {
        return A.año_ > B.año_;
    }
    else if(A.mes_ != B.mes_) 
    {
        return A.mes_ > B.mes_;
    }
    else 
    {
        return A.dia_ > B.dia_;
    }
}

bool operator <(const Fecha& A, const Fecha& B) 
{
    return !(A > B) && !(A == B);
}

bool operator <=(const Fecha& A, const Fecha& B) 
{
    return !(A > B);
}

bool operator >=(const Fecha& A, const Fecha& B) 
{
    return !(A < B);
}

bool operator !=(const Fecha& A, const Fecha& B) 
{
    return !(A == B);
}