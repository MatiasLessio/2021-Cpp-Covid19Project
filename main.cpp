#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "headers/case.h"
#include "headers/Lista.h"
#include "headers/HashMap.h"
#include "headers/Province.h"
#include <time.h>
#include <stdio.h>
#include <dos.h>

using namespace std;

void stats(string path);

void Quick_Sort_Cases(Cases x[],int inicio,int final);

void Quick_Sort_Province(Province[], int inicio, int final);

void Cases_CUI (string, string date);//Funcion que sirve para la consigna de los puntos para -casos_cui[fecha]

void P_Cases(string, int);//Funcion que sirve para la consigna de los puntos para -p_casos[n]

void P_Death(string, int);//Funcion que sirve para la consigna de los puntos para -p_muertes[n]

int main(int argc, char **argv){
    string date = "2020-01-01";
    string path = argv[argc - 1];
    int TotalProv = 0;
    //clock_t start, end;
    //start = clock();
    for(int i=1; i< argc -1 ; i++){
        string argAux=argv[i];
        if(argAux == "-estad"){
            stats(path);
        }else{
        if (argAux == "-casos_cui") 
        {
            if (argv[i + 1][0] == '2') 
            { // Se Revisasi si el argumento siguiente a -casos_cui es una fecha, solo funciona para fechas>=2000
                date = argv[i + 1];
                i++;
            }
            Cases_CUI(path, date);
        }else{
             if (argAux == "-p_casos")
             {
                try {
                    TotalProv = stoi(argv[i + 1]);
                    i++;
                }
                catch (...) {
                    TotalProv = 24;
                }
            P_Cases(path, TotalProv);
        }else{
             if (argAux == "-p_muertes")
             {
                try {
                    TotalProv = stoi(argv[i + 1]);
                    i++;
                }
                catch (...) {
                    TotalProv = 24;
                }
            P_Death(path, TotalProv);
        }
    }
    }
    }    
    //end = clock();
    //printf("The time was: %f\n", (end - start) / CLK_TCK);
}    
    cout<<"Tarea finalizada."<<endl;
    return 0;  
}

void stats(string path)
{
    cout<<"--------------------------"<<endl;
    cout<<"USTED EJECUTO ESTADISTICAS"<<endl;
    cout<<"--------------------------"<<endl;
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
    float pDeceased = ((numDeceased * 100) / numCases);//calculamos el porcentaje de muertos
    float pInfected = ((numInfected * 100) / numCases);//calculamos el porcentaje de infectados
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

void Quick_Sort_Province(Province x[], int inicio, int final)
{
    int i,j,medio;
    Province pivot, aux;
    medio=(inicio+final)/2;
    pivot= x[medio];
    i=inicio;
    j=final;
    do
    {
        while(x[i]>pivot) i++;
        while(x[j]<pivot) j--;
        if(i<=j)
        {
            aux=x[j];
            x[j]=x[i];
            x[i]=aux;
            i++;
            j--;
        }
    }
    while(i<=j);
    if(j>inicio) Quick_Sort_Province(x,inicio,j);
    if(i<final) Quick_Sort_Province(x,i,final);
}

void Quick_Sort_Cases(Cases x[],int inicio,int final)
{
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
    if(i<final) Quick_Sort_Cases(x,i,final);
}

void Cases_CUI (string path, string date)
{
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"USTED EJECUTO FECHAS DE LOS CASOS EN CUIDADOS INTENSIVOS"<<endl;
    cout<<"--------------------------------------------------------"<<endl;
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
        if(ListCUI.getTamanio()>0)
        {
            for (int i = 0; i < ListCUI.getTamanio(); i++) 
            {
                ArrayCases[i] = ListCUI.getDato(i);
            }
            Quick_Sort_Cases(ArrayCases, 0, ListCUI.getTamanio());
            cout<<"-----------------------------------------------------"<<endl;
            cout<<"Los Casos mayores a "<<date<<" de forma ordenada son:"<<endl;
            for (int i = 0; i < ListCUI.getTamanio(); i++) 
            {
                if (ArrayCases[i] > date)
                {
                    cout << ArrayCases[i] << endl;
                }
            }
        }else
        {
            cout<<"En esta muestra no se han detectado Casos en Cuidados Intensivos"<<endl;
        }
    }
}

void P_Cases(string path, int NumProvince)
{
    cout<<"-------------------------------------"<<endl;
    cout<<"USTED EJECUTO CONTAGIOS POR PROVINCIA"<<endl;
    cout<<"-------------------------------------"<<endl;
    const string ListProvince[] = {"CABA", "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Cordoba", "Corrientes",
                                      "Entre Rios", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones",
                                      "Neuquen", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe",
                                      "Santiago del Estero", "Tierra del Fuego", "Tucuman"};
    Province ProvinciaContagiado[24];
    for (int i = 0; i < 24; i++) {
        ProvinciaContagiado[i] = Province(ListProvince[i], 0);
    }
    fstream file;
    file.open(path, ios::in);
    Cases cases;
    if (file.fail()) {
        cout << "No se ha podido abrir el archivo csv" << endl;
    } else {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            cases.processLine(line);
            if (cases.getClasificacion() == "Confirmado") {
                for (int k = 0; k < 24; k++) {
                    if (cases.Provincia() == ProvinciaContagiado[k].getname()) {
                        ProvinciaContagiado[k].AumentarContador();
                        break;
                    }
                }
            } 
        }
    Quick_Sort_Province(ProvinciaContagiado, 0, 23);
    cout <<"Casos Confirmados por Provincia:"<< endl;
    cout <<"--------------------------------"<<endl;
    for (int i = 0; i < NumProvince; i++) {
    cout << ProvinciaContagiado[i] << endl;
   }
}  
}

void P_Death(string path, int NumProvince)
{
    cout<<"-------------------------------------"<<endl;
    cout<<"USTED EJECUTO MUERTES POR PROVINCIA"<<endl;
    cout<<"-------------------------------------"<<endl;
    const string ListProvince[] = {"CABA", "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Cordoba", "Corrientes",
                                      "Entre Rios", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones",
                                      "Neuquen", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe",
                                      "Santiago del Estero", "Tierra del Fuego", "Tucuman"};
    Province ProvinciaFallecidos[24];
    for (int i = 0; i < 24; i++) {
        ProvinciaFallecidos[i] = Province(ListProvince[i], 0);
    }
    fstream file;
    file.open(path, ios::in);
    Cases cases;
    if (file.fail()) {
        cout << "No se ha podido abrir el archivo csv" << endl;
    } else {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            cases.processLine(line);
            if (cases.getIsDeceased() == "SI") {
                for (int k = 0; k < 24; k++) {
                    if (cases.Provincia() == ProvinciaFallecidos[k].getname()) {
                        ProvinciaFallecidos[k].AumentarContador();
                        break;
                    }
                }
            } 
        }
        Quick_Sort_Province(ProvinciaFallecidos, 0, 23);
        cout <<"Casos Fallecidos por Provincia:"<< endl;
        cout <<"--------------------------------"<<endl;
        for (int i = 0; i < NumProvince; i++) {
            cout << ProvinciaFallecidos[i] << endl;
       }
    }
}
