#ifndef PARCIAL2_CASE_H
#define PARCIAL2_CASE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Cases {
private:
    int id_Cases;
    int edad;
    string aniosOmeses;
    string CUI;
    string dateCUI;
    string isDeceased;
    int idProvincia;
    string provincia;
    string clasificacion;

public:
    
    Cases();

    Cases(string line);

    void processLine(string line);

    void insertCUI(string cui);

    void insertIDCases(int id);

    void insertAge(int age);
    
    void insertDateCUI(string date);

    void inserTAniosOMeses(string anio_meses);

    void insertDeseaced(string status);

    void insertIdProvincia(int idprov);

    void insertClasificacion(string clasifi);

    void insertProvincia(string Prov);

    int IdCases();

    int getAge();

    int Provincia_Id();

    string getAniosOMeses();

    string getIsDeceased();

    string getClasificacion();
    
    string Cui();
    
    string Date_CUI();
    
    string Provincia();
    
    friend ostream &operator<<(ostream &os, const Cases &cases);
    
    bool operator<(const Cases &rhs) const;

    bool operator>(const Cases &rhs) const;

    bool operator<=(const Cases &rhs) const;

    bool operator>=(const Cases &rhs) const;
};

Cases::Cases() {
    id_Cases = 0;
    edad = 0;
    aniosOmeses = "Anios";
    CUI = "NO";
    dateCUI = "2000-01-01";
    isDeceased = "NO-FALLECIDO";
    idProvincia = 0;
    provincia = "UNDEFINED"; 
    clasificacion = "N/A"; //caso descartado / caso confirmado
}

Cases::Cases(string line){
    processLine(line);
}

void Cases::processLine(string line){
    stringstream s(line);
    string word;
    for(int columns = 0; getline(s, word, ','); columns++){
        if(word.size() <=0){
            if(columns == 7){
                word="SinProvincia";
            } else if (columns == 2 || columns == 0 || columns ==17){
                word = "404"; //not found
            } else {
                word = "UNDEFINED";
            }
        } else {
            word=word.substr(1, word.size()-2);
        }
        switch (columns){
            case 0: //ID
                id_Cases = (stoi(word));
                break;
            case 2://EDAD
                edad= (stoi(word));
                break;
            case 3://ANIOS O MESES
                aniosOmeses = (word);
                break;
            case 5://PROVINCIA
                provincia = (word);
                break;
            case 12://CUI
                CUI = (word);
                break;
            case 13://FECHA DE CUI
                dateCUI = (word);
                break;
            case 14://FALLECIO?
                isDeceased= (word);
                break;
            case 21://ID PROVINCIA
                idProvincia = (stoi(word));
                break;
            case 20://CLASIFICACION
                clasificacion = (word);
                break;
            default://EN CASO DE QUE NO SE MANDE NINGUNA OPCION
                break;
        }
    }
}
void Cases::insertCUI(string cui) {
    CUI = cui;
}
void Cases::insertIDCases(int id){
    id_Cases=id;
}    
void Cases::insertAge(int age){
    edad=age;
}
void Cases::insertDateCUI(string date) {
    dateCUI = date;
}
void Cases::inserTAniosOMeses(string anio_meses){
    aniosOmeses=anio_meses;
}
void Cases::insertDeseaced(string status){
    isDeceased=status;
}
void Cases::insertIdProvincia(int idprov){
    idProvincia=idprov;
}
void Cases::insertClasificacion(string clasifi){
    clasificacion=clasifi;
}
void Cases::insertProvincia(string Prov){
    provincia=Prov;
}
int Cases::IdCases(){
    return id_Cases;
}
int Cases::getAge(){
    return edad;
}
int Cases::Provincia_Id(){
    return idProvincia;
}
string Cases::getAniosOMeses() {
    return aniosOmeses;
}
string Cases::getIsDeceased(){
    return isDeceased;
}
string Cases::getClasificacion() {
    return clasificacion;
}    
string Cases::Cui() {
    return CUI;
}    
string Cases::Date_CUI() {
    return dateCUI;
}   
string Cases::Provincia(){
    return provincia;
}
ostream &operator<<(ostream &os, const Cases &cases) {
    os << "Id_Casos:" << cases.id_Cases << " Edad:" << cases.edad << " Anios/Meses:" << cases.aniosOmeses << " CUI:"
       << cases.CUI << " FechaCUI:" << cases.dateCUI << " Fallecio:" << cases.isDeceased << " IdProvincia:"
       << cases.idProvincia<< " Provincia:"
       << cases.provincia << " Clasificacion:" << cases.clasificacion;
    return os;
}//Muestra los datos de las columnas que se encuentran a la derecha del dato de referencia
bool Cases::operator<(const Cases &rhs) const {
    return dateCUI < rhs.dateCUI;
}
bool Cases::operator>(const Cases &rhs) const {
    return dateCUI > rhs.dateCUI;
}
bool Cases::operator<=(const Cases &rhs) const {
    return !(rhs < *this);
}
bool Cases::operator>=(const Cases &rhs) const {
    return !(*this < rhs);
}//rhs significa terminos indeendientes a las restriscciones
#endif // PARCIAL2_CASE_H