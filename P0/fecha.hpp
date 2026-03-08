#ifndef __FECHA__HPP
#define __FECHA__HPP

class Fecha 
{
    public:
        
        //Fecha dada dd/mm/AA 
        explicit Fecha(int d = 0, int m = 0, int a = 0);
        
        //Constructor de copia fecha
        Fecha(const Fecha& A);
        
        //Constructor de conversion a partir de cadena de bajo nivel (dd/mm/aa)
        Fecha(const char* fecha);

        //Funciones observadoras

        inline int dia() const { return dia_; };
        inline int mes() const { return mes_; };
        inline int año() const { return año_; };

        //Miembros de la clase

        static const int AñoMinimo = 1902, AñoMaximo = 2037;
        
        //Sobrecarga de operadores
        Fecha& operator =(const Fecha& A);

        friend bool operator ==(const Fecha& A, const Fecha& B);
        friend bool operator >(const Fecha& A, const Fecha& B);
        friend bool operator <(const Fecha& A, const Fecha& B);
        friend bool operator <=(const Fecha& A, const Fecha& B);
        friend bool operator >=(const Fecha& A, const Fecha& B);
        friend bool operator !=(const Fecha& A, const Fecha& B);

        class Invalida 
        {
            public :
                Invalida(const char* e) : error{e} {}
                inline const char* por_que() const { return error; }
            private :
                const char* error; 
        };


    private:
        int dia_, mes_, año_;

        static bool descomponerFecha(const char* fechaFormateada, int &dia, int &mes , int &año);

        void validarFecha() const;
};

#endif //__FECHA__HPP