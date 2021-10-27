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

    string getClasificacion();

    int getAge();

    string getAniosOMeses();

    string getIsDeceased();

    void insertCUI(string cui);
    
    string Cui();
    
    void insertDateCUI(string date);
    
    string Date_CUI();
};

Cases::Cases() {
    id_Cases = 0;
    edad = 0;
    aniosOmeses = "Anios";
    CUI = "NO-CUI";
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
            case 7://PROVINCIA
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
            case 17://ID PROVINCIA
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

string Cases::getClasificacion() {
    return clasificacion;
}
int Cases::getAge(){
    return edad;
}
string Cases::getAniosOMeses() {
    return aniosOmeses;
}
string Cases::getIsDeceased(){
    return isDeceased;
}
void Cases::insertCUI(string cui) {
    CUI = cui;
}
string Cases::Cui() {
    return CUI;
}
string Cases::Date_CUI() {
    return dateCUI;
}
void Cases::insertDateCUI(string date) {
    dateCUI = date;
}
#endif // PARCIAL2_CASE_H