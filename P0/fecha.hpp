#ifndef __FECHA__HPP
#define __FECHA__HPP

class Fecha 
{
    public:
        //Fecha dada dd/mm/AA 
        explicit Fecha(int d = 0, int m = 0, int a = 0);
        //Constructor fecha
        Fecha(const Fecha& A);
        inline int dia() const { return dia_; };
        inline int mes() const { return mes_; };
        inline int año() const { return año_; };
    private:
        int dia_, mes_, año_;
};

#endif //__FECHA__HPP