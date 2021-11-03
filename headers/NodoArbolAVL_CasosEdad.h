#ifndef U05_ARBOL_ARBOL_NodoArbolAVL_CasosEdad_H_
#define U05_ARBOL_ARBOL_NodoArbolAVL_CasosEdad_H_

#include <string.h>
#include "./case.h"

using namespace std;

template <class T>
class NodoArbolAVL_CasosEdad
{
private:
  vector<string> data;
  NodoArbolAVL_CasosEdad *left, *right;
  int height;


public:
  NodoArbolAVL_CasosEdad()
  {
    left = nullptr;
    right = nullptr;
    height=1;
  }

  NodoArbolAVL_CasosEdad(T d)
  {
    data = d;
    left = nullptr;
    right = nullptr;
    height = 1;
  }

  T getData() const {
    return data;
  }

  void setData(T d)
  {
    this->data = d;
  }

  int getClave(){
    return stoi(data[17]);
  }

  NodoArbolAVL_CasosEdad *getRight() const{
  
    return right;
  }

  void setRight(NodoArbolAVL_CasosEdad *r){
  
    this->right = r;
  }
  NodoArbolAVL_CasosEdad *getLeft() const{
  
    return left;
  }

  void setLeft(NodoArbolAVL_CasosEdad *l){
  
    this->left = l;
  }

  int getHeight(){
    return height;
  }

  void setHeight(int h){
    height = h;
  }


  void print(){
         
    int colsOfInterest[] = {0, 2, 7, 14, 17, 20}; //columnas importantes 
    int nColumns = sizeof(colsOfInterest) / sizeof(colsOfInterest[0]);
    
    for (int i = 0; i < nColumns; i++){
      cout << data[colsOfInterest[i]] << "\t";
    }
    cout << endl;
  }


};



#endif // U05_ARBOL_ARBOL_NodoArbolAVL_CasosEdad_H_
