#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "headers/case.h"
#include "headers/Lista.h"

using namespace std;

void stats(string path);

void Quick_Sort_Cases(Cases x[],int inicio,int final);

void Cases_CUI (string, string date);

int main(int argc, char **argv){
    string path = argv[argc - 1];
    for(int i=1; i< argc -1 ; i++){
        string argAux=argv[i];
        if(argAux == "-estad"){
            stats(path);
        }
    }
    cout<<"Tarea finalizada."<<endl;
}  

void stats(string path){
    cout<<"----------------------------------------------"<<endl;
    cout<<"USTED EJECUTO ESTADISTICAS"<<endl;
    cout<<"----------------------------------------------"<<endl;
    fstream file;
    float numCases=0, numInfected=0, numDeceased=0;
    file.open(path, ios::in);
    Cases cases;
    int ageConfirmed[10]; //0-9/10-19/20-29/30-39/40-49/50-59/60-69/70-79/80-89/90-99
    int ageDeceased[10]; //0-9/10-19/20-29/30-39/40-49/50-59/60-69/70-79/80-89/90-99
    for (int i = 0; i<10; i++){
        ageConfirmed[i]=0;
        ageDeceased[i]=0;
    }
    if(file.fail()){
        cout<<"No pudo abrir el archivo csv."<<endl;
        return;
    } else {
        string line;
        getline(file, line);
        while(getline(file, line)){
            cases.processLine(line);
            numCases++;
            if(cases.getClasificacion()=="Confirmado"){
                numInfected++;
                if(cases.getAniosOMeses() == "Meses"){
                    ageConfirmed[0]++;
                } else {
                    ageConfirmed[cases.getAge() / 10]++;
                }
            } else if (cases.getIsDeceased()== "SI"){
                numDeceased++;
                if(cases.getAniosOMeses()=="Meses"){
                    ageDeceased[0]++;
                } else {
                    ageDeceased[cases.getAge()/10]++;
                }
            }
        }
    }
    float pDeceased = ((numDeceased * 100) / numCases);
    float pInfected = ((numInfected * 100) / numCases);
    cout<< "Cantidad de casos estudiados, (muestra), -> "<<numCases<<endl;
    cout<< "Cantidad total de infectados-> "<<numInfected<<endl;
    cout<< "Cantidad de fallecidos-> "<<numDeceased<<endl;
    cout<< "Porcentaje de Infectados-> %"<<pInfected<<endl;
    cout<< "Porcentaje de fallecidos-> %"<<pDeceased<<endl;
    cout<<"----------------------------------------------"<<endl;
    cout<<"Contagiados por rango de edad."<<endl;
    for (int i = 0; i < 10; i++) {
        cout << "Entre " << i * 10 << " y " << (i * 10) + 9 << " anios es: " << ageConfirmed[i] << endl;
    }
    cout<<"----------------------------------------------"<<endl;
    cout<<"Fallecidos por rango de edad."<<endl;
    for (int i = 0; i < 10; i++) {
        cout << "Entre " << i * 10 << " y " << (i * 10) + 9 << " anios es: " << ageDeceased[i] << endl;
    }
}
void Quick_Sort_Cases(Cases x[],int inicio,int final){
    int i,j,medio;
    Cases pivot, aux;
    medio=(inicio+final)/2;
    pivot= x[medio];
    i=inicio;
    j=final;
    do
    {
        while(x[i]<pivot) i++;
        while(x[j]>pivot) j--;
        if(i<=j)
        {
            aux=x[i];
            x[i]=x[j];
            x[j]=aux;
            i++;
            j--;
        }
    }
    while(i<=j);
    if(j>inicio) Quick_Sort_Cases(x,inicio,j);
    if(i<final) Quick_Sort_Cases(x,i,final)
}

void Cases_CUI (string path, string date)
{
    Lista <Cases> ListCUI;
    Cases cases;
    fstream file;
    file.open(path,ios::in);
    if(file.fail())
    {
        cout<<"No se ha podido Abrir el archivo cvs"<<endl;
    }else
    {
        string line;
        getline(file,line);
        while(getline(file,line))
        {
            cases.processLine(line);
            if(cases.Cui()=="SI" && cases.Date_CUI()>date)
            {
                ListCUI.insertarPrimero(cases);
            }
        }
        Cases ArrayCases[ListCUI.getTamanio()];
        for (int i = 0; i < ListCUI.getTamanio(); i++) 
        {
            ArrayCases[i] = ListCUI.getDato(i);
        }
        cout <<"Los Casos mayores a " << date << " de forma ordenada son: " << endl;
        cout<<"-----------------------------------------------------------"<<endl;
        for (int i = 0; i < ListCUI.getTamanio(); i++) 
        {
            if (ArrayCases[i] > date)
            {
                cout << ArrayCases[i] << endl;
            }
        }
    }
}