#ifndef PARCIAL2_PROVINCE_H
#define PARCIAL2_PROVINCE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "case.h"
#include "Lista.h"

using namespace std;

class Province {
private:
        string NameProv;
        long int contador;
public:
        Province(){
            NameProv="N/A";
            contador=0;
        }
        Province(const string &prov,int cont):NameProv(prov) {
            //NameProv=prov;
            contador=cont;
        }
        const string &getname() const{
            return NameProv;
        }
        void setName(const string &prov){
            NameProv=prov;
        }
        void AumentarContador(){
            contador++;
        }
        bool operator==(const Province &rhs) const {
        return NameProv == rhs.NameProv ;
        }
        bool operator!=(const Province &rhs) const {
            return !(rhs == *this);
        }
        bool operator<(const Province &rhs) const {
            return contador < rhs.contador;
        }
        bool operator>(const Province &rhs) const {
            return contador > rhs.contador;
        }
        bool operator<=(const Province &rhs) const {
            return !(rhs < *this);
        }
        bool operator>=(const Province &rhs) const {
            return !(*this < rhs);
        }//rhs significa terminos indeendientes a las restriscciones
        friend ostream &operator<<(ostream &os, const Province &province) {
        os << "Provincia: |" << province.NameProv << "|, Numero de ocurrencias: " << province.contador;
        return os;
        }
};

#endif //PARCIAL2_PROVINCE_H