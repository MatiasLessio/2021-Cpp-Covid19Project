#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "headers/case.h"
#include "headers/Lista.h"
#include "headers/HashMap.h"

using namespace std;

void stats(string path);//Funcion que sirve para la consigna de los puntos para -estad

void Quick_Sort_Cases(Cases x[],int inicio,int final);

void Cases_CUI (string, string date);//Funcion que sirve para la consigna de los puntos para -casos_cui[fecha]

int main(int argc, char **argv){
<<<<<<< Updated upstream
    cout<<(256*10)%10<<endl;
    string date = "2020-01-01";
=======
    string date = "2019-01-01";
>>>>>>> Stashed changes
    string path = argv[argc - 1];
    string datenum = "";
    for(int i=1; i< argc -1 ; i++){
        string argAux=argv[i];
        if(argAux == "-estad"){
            stats(path);
        }else{
        if (argAux == "-casos_cui") {
            if (argv[i + 1][0] == '[') {
            // Se Revisa si el argumento siguiente a -casos_cui es una fecha, solo funciona para fechas>=2000
                date = argv[i + 1];
                i++;
                cout<<"date: "<<date<<endl;
            }
            Cases_CUI(path, date);
        }
        }
    }
    cout<<"Tarea finalizada."<<endl;
}
  

void stats(string path){
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

void Quick_Sort_Cases(Cases arr[], int first, int last){
  int i, j, middle;
  Cases pivot, aux;
  middle = (first + last) / 2;
  pivot = arr[middle];
  i = first;
  j = last;

<<<<<<< Updated upstream
void Quick_Sort_Cases(Cases x[],int inicio,int final){
    
    int i,j,medio;
    Cases pivot, aux;
    medio=(inicio+final)/2;
    pivot= x[medio];
    i=inicio;
    j=final;
    do
    {
        cout<<"Se ejecuta el quicksort"<<endl;
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
=======
  do {
    cout<<"ORDENANDO"<<endl;
    while (arr[i] < pivot)
      i++;
    while (arr[j] > pivot)
      j--;

    if (i <= j) {
      aux = arr[i];
      arr[i] = arr[j];
      arr[j] = aux;
      i++;
      j--;
>>>>>>> Stashed changes
    }
  } while (i <= j);

  if (j > first){
    Quick_Sort_Cases(arr, first, j);
  }
    
  if (i < last){
    Quick_Sort_Cases(arr, i, last);
  }
    
}

void Cases_CUI (string path, string date)
{
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"USTED EJECUTO FECHAS DE LOS CASOS EN CUIDADOS INTENSIVOS"<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    Lista <Cases> ListCUI;
    Lista <Cases> ListDatesCUI;
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
            if(cases.Cui()=="SI" && cases.Date_CUI()>date) {
                ListCUI.insertarPrimero(cases);
                ListDatesCUI.insertarPrimero(cases.Date_CUI());
            } 
        }
        Cases ArrayCases[ListCUI.getTamanio()];
        if(ListCUI.getTamanio()>0)
        {
            for (int i = 0; i < ListCUI.getTamanio(); i++) 
            {
                ArrayCases[i] = ListDatesCUI.getDato(i);
            }
<<<<<<< Updated upstream
            cout<<"Antes del quicksort"<<endl;
            Quick_Sort_Cases(ArrayCases, 0, ListCUI.getTamanio());
=======
            cout<<"La cantidad de casos en CUIDADOS INTENSIVOS es-> "<<ListCUI.getTamanio()<<endl;
            cout<<"antes del quicksort"<<endl;
            //Quick_Sort_Cases(ArrayCases, 0, ListCUI.getTamanio());
>>>>>>> Stashed changes
            cout<<"despues del quicksort"<<endl;
            cout<<"-----------------------------------------------------"<<endl;
            cout<<"Los Casos mayores a "<<date<<" de forma ordenada son:"<<endl;
            for (int i = 0; i < ListCUI.getTamanio(); i++) {

                if (ArrayCases[i] > date) {
                    cout << ArrayCases[i] << endl;
                }
            }
        }else
        {
            cout<<"Desde la fecha "<<date<<" no se han detectado Casos en Cuidados Intensivos"<<endl;
        }
    }
}

