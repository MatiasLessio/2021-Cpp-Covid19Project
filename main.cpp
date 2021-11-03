#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <ctime>
#include <stdlib.h>
#include "headers/case.h"
#include "headers/Lista.h"
//#include "headers/HashMap.h"
#include "headers/Province.h"
#include "headers/ArbolBinarioAVL.h"
#include <locale.h>

using namespace std;

void stats(string path);//Funcion que sirve para la consigna de los puntos para -estad

void Quick_Sort_Cases(Cases arr[], int first, int last);

void Quick_Sort_Province(Province arr[], int first, int last);

void Quick_Sort_Province_Age(Cases arr[], int first, int last);

void Cases_CUI (string, string date);//Funcion que sirve para la consigna de los puntos para -casos_cui[fecha]

void P_Cases(string, int);//Funcion que sirve para la consigna de los puntos para -p_casos[n]

void P_Death(string, int);//Funcion que sirve para la consigna de los puntos para -p_muertes[n]

int stringAinteger(string stringDate);

void Cases_Age(string path, string age);

int main(int argc, char **argv)
{
    clock_t begin;
    begin = clock();
    setlocale(LC_ALL, "spanish");
    string date = "2020-01-01";
    string path = argv[argc - 1];
    int TotalProv = 0;
    for(int i=1; i< argc -1 ; i++){
        string argAux=argv[i];
        if(argAux == "-estad"){
            stats(path);
        }else{
        if (argAux == "-casos_cui") {
            if (argv[i + 1][0] >= 48 && argv[i + 1][0] <=57) {
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
        }else{
            if(argAux== "-casos_edad")
            {
            string age;
            if(argv[i + 1][0] >=48 && argv[i + 1][0] <=57){
                age=argv[i + 1];
            }else{
                age="-1";
            }
            Cases_Age(path, age);
            }
        }
        }
    }
    }
    }    
    cout<<"Tarea finalizada."<<endl;
    clock_t end = clock ();

    double elapsed_secs = static_cast<double>(end - begin ) / CLOCKS_PER_SEC;

    cout<< "Tiempo empleado: "<< elapsed_secs<<"\n"<<endl;
    cout<<"-----------------------------------------------------"<<endl;
    return 0;  
}

int stringAinteger(string stringDate)
{
    string intDate;
    int num=stringDate.size(), j=0;
    for(int i=0; i < num ; i++){
         int aux = stringDate[i];
        if(aux >= 48 && aux <=57){
            intDate += stringDate[i];
            j++;
        }
    }
    return stoi(intDate);
}

void stats(string path)
{
    cout<<"--------------------------"<<endl;
    cout<<"USTED EJECUTO: ESTADISTICAS"<<endl;
    cout<<"--------------------------"<<endl;
    fstream file;
    string line;
    Cases cases;
    long double numCases=0, numInfected=0, numDeceased=0;
    
    
    int ageConfirmed[10]={0,0,0,0,0,0,0,0,0,0}; //0-9/10-19/20-29/30-39/40-49/50-59/60-69/70-79/80-89/90-99
    int ageDeceased[10]={0,0,0,0,0,0,0,0,0,0}; //0-9/10-19/20-29/30-39/40-49/50-59/60-69/70-79/80-89/90-99
    file.open(path, ios::in);
    if(file.fail()){
        cout<<"No pudo abrir el archivo csv."<<endl;
        return;
    } else {
        
        getline(file, line);
        while(getline(file, line)){
            cases.processLine(line);
            numCases++;
            if(cases.getClasificacion()== "Confirmado"){
                numInfected++;
                if(cases.getAniosOMeses() == "Meses"){
                    ageConfirmed[0]++;
                } else {
                    ageConfirmed[cases.getAge() / 10]++;
                }
            } else if (cases.getIsDeceased()== "SI"){
                numDeceased++;
                if(cases.getAniosOMeses()== "Meses"){
                    ageDeceased[0]++;
                } else {
                    ageDeceased[cases.getAge()/10]++;
                }
            }
        }
    }
    float pDeceased = ((numDeceased * 100) / numInfected);//calculamos el porcentaje de muertos
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
    cout<<"-------------------------------------"<<endl;
}

void Quick_Sort_Cases(Cases arr[], int first, int last)
{
  int i, j, middle;
  Cases pivot, aux;

  middle = (first + last) / 2;
  pivot = arr[middle];
  i = first;
  j = last;

  do {
    while (stringAinteger(arr[i].Date_CUI()) < stringAinteger(pivot.Date_CUI())){
        i++;
    }
    
    while (stringAinteger(arr[j].Date_CUI()) > stringAinteger(pivot.Date_CUI())){
        j--;
    }
    if (i <= j) {
      aux = arr[i];
      arr[i] = arr[j];
      arr[j] = aux;
      i++;
      j--;
    }
  } while (i <= j);   
  if (j > first)
    Quick_Sort_Cases(arr, first, j);
  if (i < last)
    Quick_Sort_Cases(arr, i, last);
    
}

void Cases_CUI (string path, string date)
{
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"USTED EJECUTO: FECHAS DE LOS CASOS EN CUIDADOS INTENSIVOS"<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    
    vector<string> row;
    string line, word;
    ArbolBinarioAVL <vector<string>> arbol;
    int num=0;
    fstream file;
    file.open(path,ios::in);
    if(file.fail())
    {
        cout<<"No se ha podido Abrir el archivo cvs"<<endl;
    }else
    {
        while(getline(file,line))
        {
            row.clear();
            stringstream s(line);
            while (getline(s, word, ',')){
                if (word.size() > 0) { 
                    word = word.substr(1, word.size() - 2);
                } else{
                    word= "NA";
                }
                row.push_back(word);
            }
            if ( row[12].compare("SI") == 0 && stringAinteger(row[13]) > stringAinteger(date) ){
                arbol.put(row);
                num++;
            }
        }
        
        arbol.inorder();
        cout<<"Cantidad de casos en Cuidados intensivos-> "<<num<<endl;
        
    }
    cout<<"-------------------------------------"<<endl;
}

void P_Cases(string path, int NumProvince)
{
    cout<<"-------------------------------------"<<endl;
    cout<<"USTED EJECUTO: CONTAGIOS POR PROVINCIA"<<endl;
    cout<<"-------------------------------------"<<endl;
    const string ListProvince[] = {"CABA", "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Córdoba", "Corrientes",
                                      "Entre Ríos", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones",
                                      "Neuquén", "Río Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe",
                                      "Santiago del Estero", "Tierra del Fuego", "Tucumán"};
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
   }
            Quick_Sort_Province(ProvinciaContagiado, 0, 23);
            cout <<"Casos Confirmados por Provincia:"<< endl;
            cout <<"--------------------------------"<<endl;
            for (int i = 0; i < NumProvince; i++) {
            cout << ProvinciaContagiado[i] << endl;
        }
    cout<<"-------------------------------------"<<endl;
}

void P_Death(string path, int NumProvince)
{
    cout<<"-------------------------------------"<<endl;
    cout<<"USTED EJECUTO: MUERTES POR PROVINCIA"<<endl;
    cout<<"-------------------------------------"<<endl;
    const string ListProvince[] = {"CABA", "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Córdoba", "Corrientes",
                                      "Entre Ríos", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones",
                                      "Neuquén", "Río Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe",
                                      "Santiago del Estero", "Tierra del Fuego", "Tucumán"};
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
cout<<"-------------------------------------"<<endl;
}

void Quick_Sort_Province(Province arr[], int first, int last)
{
    int i, j, medio;
    Province pivot, aux;
    medio=(first+last)/2;
    pivot= arr[medio];
    i=first;
    j=last;
    do
    {
        while(arr[i]>pivot) i++;
        while(arr[j]<pivot) j--;
        if(i<=j)
        {
            aux=arr[j];
            arr[j]=arr[i];
            arr[i]=aux;
            i++;
            j--;
        }
    }
    while(i<=j);
    if(j>first) Quick_Sort_Province(arr, first, j);
    if(i<last) Quick_Sort_Province(arr, i, last);
}

void Quick_Sort_Province_Age(Cases arr[], int first, int last)
{
    int i, j, medio;
    Cases pivot, aux;
    medio=(first+last)/2;
    pivot= arr[medio];
    i=first;
    j=last;
    do
    {
        while(arr[i].Provincia_Id()<pivot.Provincia_Id()) i++;
        while(arr[j].Provincia_Id()>pivot.Provincia_Id()) j--;
        if(i<=j)
        {
            aux=arr[i];
            arr[i]=arr[j];
            arr[j]=aux;
            i++;
            j--;
        }
    }
    while(i<=j);
    if(j>first) Quick_Sort_Province_Age(arr, first, j);
    if(i<last) Quick_Sort_Province_Age(arr, i, last);
}

void Cases_Age(string path, string age) 
{
    cout<<"----------------------------"<<endl;
    cout<<"USTED EJECUTO: CASOS POR EDAD"<<endl;
    cout<<"----------------------------"<<endl;
    if(stoi(age)==-1){
        cout<<"NO SE INGRESO UNA EDAD\nPara ejecutar esta funcion debe ingresar una edad como parametro."<<endl;
        cout<<"-------------------------------------"<<endl;
        return;
    }
    Cases cases;
    fstream file;
    file.open(path, ios::in);
    Lista<Cases> Listita;
    long int num=0;
    if (file.fail()) {
        cout << "No se ha podido abrir el archivo csv" << endl;
    } else {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            cases.processLine(line);
            if (cases.getAniosOMeses() == "Años" &&  cases.getClasificacion() == "Confirmado") {
                if(cases.getAge()==stoi(age) && stoi(age)!=-1){
                    Listita.insertarPrimero(cases);
                    num++;
                }
            }
        }
        Cases ArrayCases[num];
        for (int i = 0; i < num; i++) 
        {
            ArrayCases[i] = (Listita.getDato(i));
        }
        Quick_Sort_Province_Age(ArrayCases, 0, num-1);
        cout<<"-----------------------------------------------------"<<endl;
        for (int i = 0; i < num; i++) {
            cout<<ArrayCases[i]<<endl;
                
        }
        cout<<"-----------------------------------------------------"<<endl;
        cout<<"Un total de "<<num<<" casos confirmados con la edad de "<<age<<"."<<endl;
    }
    cout<<"-----------------------------------------------------"<<endl;
}