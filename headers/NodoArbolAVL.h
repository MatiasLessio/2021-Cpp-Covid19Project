#ifndef U05_ARBOL_ARBOL_NODOARBOLAVL_H_
#define U05_ARBOL_ARBOL_NODOARBOLAVL_H_

#include <string.h>
#include "./case.h"

using namespace std;

template <class T>
class NodoArbolAVL
{
private:
  T data;
  NodoArbolAVL *left, *right;
  int height;

  int stringAinteger(string stringDate);

public:
  NodoArbolAVL()
  {
    left = nullptr;
    right = nullptr;
    height=1;
  }

  NodoArbolAVL(T d)
  {
    data = d;
    left = nullptr;
    right = nullptr;
    height = 1;
  }

  T getData() const
  {
    return data;
  }

  void setData(T d)
  {
    this->data = d;
  }

  int getClave(){
    return stringAinteger(data[13]);
  }

  NodoArbolAVL *getRight() const
  {
    return right;
  }

  void setRight(NodoArbolAVL *r)
  {
    this->right = r;
  }
  NodoArbolAVL *getLeft() const
  {
    return left;
  }

  void setLeft(NodoArbolAVL *l)
  {
    this->left = l;
  }

  int getHeight(){
    return height;
  }

  void setHeight(int h){
    height = h;
  }

  void print() {
    int colsOfInterest[] = {0, 2, 3, 5, 7, 12, 13, 14, 17, 21, 20};
    int nColumns = sizeof(colsOfInterest) / sizeof(colsOfInterest[0]);
    for (int i = 0; i < nColumns; i++){
      switch(colsOfInterest[i]){
        case 0:
          cout<<"IdCaso->"<<data[colsOfInterest[i]]<<" ";
          break;
        case 2:
          cout<<"Edad->"<<data[colsOfInterest[i]]<<" ";
          break;
        case 3:
          cout<<"Anios/Meses->"<<data[colsOfInterest[i]]<<" ";
          break;
        case 5:
          cout<<"Provincia->"<<data[colsOfInterest[i]]<<" ";
          break;
        case 12:
          cout<<"CUI->"<<data[colsOfInterest[i]]<<" ";
          break;
        case 13:
          cout<<"FechaCUI->"<<data[colsOfInterest[i]]<<" ";
          break;
        case 14:
          cout<<"Fallecio->"<<data[colsOfInterest[i]]<<" ";
          break;
        case 21:
          cout<<"IdProvincia->"<<data[colsOfInterest[i]]<<" ";
          break;
        case 20:
          cout<<"Clasificacion->"<<data[colsOfInterest[i]];
          break;
        default:
          break;
      }
    }
    cout << endl;
  }

};

template<class T> 
int NodoArbolAVL<T>::stringAinteger(string stringDate) {
    string intDate;
    int num=stringDate.size();
    for(int i=0; i < num ; i++){
         int aux = stringDate[i];
        if(aux >= 48 && aux <=57){
            intDate  += stringDate[i];
        }
    }
    return stoi(intDate);
}


#endif // U05_ARBOL_ARBOL_NODOARBOLAVL_H_
