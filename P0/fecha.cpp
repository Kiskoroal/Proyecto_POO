#include <ctime>
<<<<<<< HEAD
#include "./fecha.hpp"

//Funciones públicas
Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), año_(a)
=======
#include <cstdio> //Para hacer uso de sscanf
#include <cmath>    //Para hacer uso de log y pow
#include "./fecha.hpp"

//Metodos privados

bool Fecha::descomponerFecha(const char* fechaFormateada, int &dia, int &mes , int &año) 
{
            bool correcto = sscanf(fechaFormateada, "%d/%d/%d", &dia, &mes, &año) == 3;
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
Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), año_(a), actual(false)
>>>>>>> desarrollo
{    
    std::time_t tiempo_actual = std::time(nullptr);
    std::tm* tiempo_desglosado = std::localtime(&tiempo_actual);
    if(d == 0) { dia_ = tiempo_desglosado->tm_mday; }
<<<<<<< HEAD
    if(m == 0) { mes_ = tiempo_desglosado->tm_mon; }
    if(a == 0) { a = tiempo_desglosado->tm_year; }
=======
    if(m == 0) { mes_ = tiempo_desglosado->tm_mon + 1; }
    if(a == 0) { año_ = tiempo_desglosado->tm_year + 1900; }
    validarFecha();
}

//Constructor de conversión de cadena de bajo nivel (dd/mm/aa)
Fecha::Fecha(const char* fecha) : actual(false)
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

bool operator ==(const Fecha& A, const Fecha& B) 
{
    return (A.dia_ == B.dia_) && (A.mes_ == B.mes_) && (A.año_ == B.año_);
}

bool operator <(const Fecha& A, const Fecha& B) 
{
    if(A.año_ != B.año_) 
    {
        return A.año_ < B.año_;
    }
    else if(A.mes_ != B.mes_) 
    {
        return A.mes_ < B.mes_;
    }
    else 
    {
        return A.dia_ < B.dia_;
    }
}

bool operator >(const Fecha& A, const Fecha& B) 
{
    return (A != B) && !(A < B);
}

bool operator <=(const Fecha& A, const Fecha& B) 
{
    return A < B || A == B;
}

bool operator >=(const Fecha& A, const Fecha& B) 
{
    return !(A < B);
}

bool operator !=(const Fecha& A, const Fecha& B) 
{
    return !(A == B);
}

Fecha Fecha::operator +(int i) const
{
    Fecha copia;

    copia = *this;

    copia += i;
    return copia;
}

Fecha Fecha::operator -(int i) const
{
    Fecha copia;

    copia = *this;

    copia += -i;

    return copia;
}

Fecha& Fecha::operator +=(int i) 
{
    std::tm fechaNormalizada = {};

    fechaNormalizada.tm_mday = dia_ + i;
    fechaNormalizada.tm_mon = mes_ - 1;
    fechaNormalizada.tm_year = año_ - 1900;

    std::mktime(&fechaNormalizada);

    dia_ = fechaNormalizada.tm_mday;
    mes_ = fechaNormalizada.tm_mon + 1;
    año_ = fechaNormalizada.tm_year + 1900;
    actual = false;

    validarFecha();


    return *this;
}

Fecha& Fecha::operator -=(int i) 
{
    return *this += -i;
}

Fecha& Fecha::operator ++() 
{

    return *this += 1;
}

Fecha Fecha::operator ++(int i) 
{
    Fecha copia(*this);
    *this += 1;

    return copia;
}

Fecha& Fecha::operator --() 
{
    return *this += -1;
}

Fecha Fecha::operator --(int i) 
{
    Fecha copia(*this);
    *this += -1;

    return copia;
}

Fecha::operator const char*() const 
{
    if(!actual) 
    {

        std::tm horaThis = {};

        horaThis.tm_mday = dia_;
        horaThis.tm_mon  = mes_ - 1;
        horaThis.tm_year = año_ - 1900;

        std::mktime(&horaThis); //Normalizamos para obtener todos los datos de esa fecha

        static const char* dias[] = {
            "domingo", "lunes", "martes", "miércoles",
            "jueves", "viernes", "sábado"
        };

        static const char* meses[] = {
            "", "enero", "febrero", "marzo", "abril", "mayo", "junio",
            "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"
        };

        std::snprintf(crep, sizeof(crep), "%s %d de %s de %d", dias[horaThis.tm_wday], dia_, meses[mes_], año_);
    }
    
    return crep;
>>>>>>> desarrollo
}