#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "headers/case.h"
#include "headers/Lista.h"
#include "headers/HashMap.h"
#include "headers/Province.h"

using namespace std;

void stats(string path);//Funcion que sirve para la consigna de los puntos para -estad

void Quick_Sort_Cases(Cases arr[], int first, int last);

void Quick_Sort_Province(Province arr[], int first, int last);

void Cases_CUI (string, string date);//Funcion que sirve para la consigna de los puntos para -casos_cui[fecha]

void P_Cases(string, int);//Funcion que sirve para la consigna de los puntos para -p_casos[n]

void P_Death(string, int);//Funcion que sirve para la consigna de los puntos para -p_muertes[n]

int stringAinteger(string stringDate);

int main(int argc, char **argv){
    cout<<(256*10)%10<<endl;
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
            // Se Revisa si el argumento siguiente a -casos_cui es una fecha, solo funciona para fechas>=2000
                date = argv[i + 1];
                i++;
            }
            cout<<stringAinteger(date)<<endl;
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
    }    
    cout<<"Tarea finalizada."<<endl;
    return 0;  
}

int stringAinteger(string stringDate){
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

void Quick_Sort_Cases(Cases arr[], int first, int last){
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
    cout<<"USTED EJECUTO FECHAS DE LOS CASOS EN CUIDADOS INTENSIVOS"<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    Cases cases;
    Lista <int> ListDatesCUI;
    Lista <Cases> ListCUI;

    
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
            if(cases.Cui()=="SI" && stringAinteger(cases.Date_CUI()) > stringAinteger(date)) {
                ListCUI.insertarPrimero(cases);
                ListDatesCUI.insertarPrimero(stringAinteger(cases.Date_CUI()));
            } 
        }
        int num=ListCUI.getTamanio();
        Cases ArrayCases[num];
        if(num>0)
        {
            for (int i = 0; i < num; i++) 
            {
                ArrayCases[i] = (ListCUI.getDato(i));
            }
            Quick_Sort_Cases(ArrayCases, 0, num-1);
            cout<<"-----------------------------------------------------"<<endl;
            cout<<"Los Casos mayores a "<<date<<" ordenados de mayor a menor son:"<<endl;
            for (int i = 0; i < num; i++) {
                if (stringAinteger(ArrayCases[i].Date_CUI()) > stringAinteger(date)) {
                    cout << ArrayCases[i] << endl;
                }
            }
        }else
        {
            cout<<"Desde la fecha "<<date<<" no se han detectado Casos en Cuidados Intensivos"<<endl;
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
