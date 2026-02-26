#include <ctime>
#include "./fecha.hpp"

//Funciones públicas
Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), año_(a)
{    
    std::time_t tiempo_actual = std::time(nullptr);
    std::tm* tiempo_desglosado = std::localtime(&tiempo_actual);
    if(d == 0) { dia_ = tiempo_desglosado->tm_mday; }
    if(m == 0) { mes_ = tiempo_desglosado->tm_mon; }
    if(a == 0) { a = tiempo_desglosado->tm_year; }
}